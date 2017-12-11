#include <iostream>
#include <cmath>
#include <map>
#include "StructComp.h"
#include "Combination/Combination.h"
#ifdef __linux__
#include <stdlib.h>
#endif

#define X_P(ROW_NUM) struct_plus.block(0, 0, ROW_NUM, 1).array()
#define Y_P(ROW_NUM) struct_plus.block(0, 1, ROW_NUM, 1).array()
#define Z_P(ROW_NUM) struct_plus.block(0, 2, ROW_NUM, 1).array()
#define X_M(ROW_NUM) struct_minus.block(0, 0, ROW_NUM, 1).array()
#define Y_M(ROW_NUM) struct_minus.block(0, 1, ROW_NUM, 1).array()
#define Z_M(ROW_NUM) struct_minus.block(0, 2, ROW_NUM, 1).array()

StructComp::StructComp(ParamBox &v) : solver(diff_mat)
{
    if (v.buffer1.size() == v.buffer2.size()) // check if two molecules have the same number of atoms
    {
        if (int lack = v.buffer1.size() % 3) // check if every atom has completed position information
        {
            std::cerr << "The data of atoms' position is uncompleted!" << std::endl
                      << "Maybe lack " << lack << " coefficient(s)" << std::endl;
        }
        else // check all pass, start to process the data
        {
            int col, row;                       // matrix coefficient index
            int buffer_size = v.buffer1.size(); // the size of buffer[0] or buffer[1]

            atom_num = buffer_size / 3;       // update atom_num
            struct1.resize(atom_num, 3);      // resize struct1
            struct2.resize(atom_num, 3);      // resize struct2
            struct_plus.resize(atom_num, 3);  // resize struct_plus
            struct_minus.resize(atom_num, 3); // resize struct_minus

            for (int i = 0; i < buffer_size; i++) // store the data of atoms' position
            {
                row = i / 3;
                col = i % 3;
                struct1(row, col) = v.buffer1[i]; // molecules_1
                struct2(row, col) = v.buffer2[i]; // molecules_2
            }
            move_center();
            update_matrix();
        }
    }
    else
    {
        std::cerr << "Two molecules have different number of atoms!" << std::endl;
        exit(-1);
    }
}

StructComp::StructComp(Matrix<double, Dynamic, 3> buffer) : solver(diff_mat)
{
    int size = (buffer.size() / 3);
    if (size % 2)
    {
        std::cerr << "Two molecules have different number of atoms!" << std::endl;
        exit(-1);
    }
    else
    {
        size /= 2;
        atom_num = size; // update atom_num
        struct1 = buffer.block(0, 0, size, 3);
        struct2 = buffer.block(size, 0, size, 3);
        struct_plus.resize(atom_num, 3);
        struct_minus.resize(atom_num, 3);
        update_matrix();
    }
}

void StructComp::move_center()
{
    // calculate the center of struct1 and struct2
    center1 = struct1.colwise().sum() / atom_num; // center of struct1
    center2 = struct2.colwise().sum() / atom_num; // center of struct2
    // move struct1 and struct2's centers to (0, 0, 0)
    struct1 = struct1.rowwise() - center1; // move the struct1
    struct2 = struct2.rowwise() - center2; // move the struct2
}

void StructComp::update_matrix()
{
    // calculate struct_plus: x_p = x' + x
    struct_plus = (struct1.array() + struct2.array()).matrix();
    // calculate struct_minus: x_m = x' - x
    struct_minus = (struct2.array() - struct1.array()).matrix();
    // calculate diff_mat
    diff_mat(0, 0) = (X_M(atom_num).square() + Y_M(atom_num).square() + Z_M(atom_num).square()).sum();
    diff_mat(0, 1) = diff_mat(1, 0) = (Y_P(atom_num) * Z_M(atom_num)).sum() - (Y_M(atom_num) * Z_P(atom_num)).sum();
    diff_mat(0, 2) = diff_mat(2, 0) = (X_M(atom_num) * Z_P(atom_num)).sum() - (X_P(atom_num) * Z_M(atom_num)).sum();
    diff_mat(0, 3) = diff_mat(3, 0) = (X_P(atom_num) * Y_M(atom_num)).sum() - (X_M(atom_num) * Y_P(atom_num)).sum();
    diff_mat(1, 1) = (Y_P(atom_num).square() + Z_P(atom_num).square() + X_M(atom_num).square()).sum();
    diff_mat(1, 2) = diff_mat(2, 1) = (X_M(atom_num) * Y_M(atom_num)).sum() - (X_P(atom_num) * Y_P(atom_num)).sum();
    diff_mat(1, 3) = diff_mat(3, 1) = (X_M(atom_num) * Z_M(atom_num)).sum() - (X_P(atom_num) * Z_P(atom_num)).sum();
    diff_mat(2, 2) = (X_P(atom_num).square() + Z_P(atom_num).square() + Y_M(atom_num).square()).sum();
    diff_mat(2, 3) = diff_mat(3, 2) = (Y_M(atom_num) * Z_M(atom_num)).sum() - (Y_P(atom_num) * Z_P(atom_num)).sum();
    diff_mat(3, 3) = (X_P(atom_num).square() + Y_P(atom_num).square() + Z_M(atom_num).square()).sum();
    SelfAdjointEigenSolver<Matrix4d> new_solver(diff_mat);
    solver = new_solver;
}

void StructComp::cal_eigenvalues()
{
    // calculate eigenvalues
    eigen_values = solver.eigenvalues();
}

void StructComp::cal_eigenvectors()
{
    // calculate eigenvectors
    eigen_vectors = solver.eigenvectors();
}

void StructComp::cal_rms()
{
    // calculate rms
    rms = (eigen_values / atom_num).array().sqrt();
}

void StructComp::cal_spinparam()
{
    // calculate spin_angle: half the angle
    spin_angle = eigen_vectors.block(0, 0, 1, 4).transpose().array().acos();
    // calculate spin_pivot
    for (int i = 0; i < 4; i++)
    {
        spin_pivot.col(i) = eigen_vectors.block(1, i, 3, 1) / sin(spin_angle(i));
    }
    spin_angle *= 2;
}

void StructComp::cal_all()
{
    cal_eigenvalues();
    cal_eigenvectors();
    cal_rms();
    cal_spinparam();
}

double StructComp::cal_triangle_area(const Matrix3d &points)
{
    double d1 = (points.row(0).array() - points.row(1).array()).matrix().norm();
    double d2 = (points.row(0).array() - points.row(2).array()).matrix().norm();
    double d3 = (points.row(1).array() - points.row(2).array()).matrix().norm();
    double p = (d1 + d2 + d3) / 2.0;
    return std::sqrt(p * (p - d1) * (p - d2) * (p - d3));
}
// find the max triangle in molecules
Matrix<double, 6, 3> StructComp::max_triangle()
{
    Combination combination_generator(atom_num, 3); // to generate all combinations
    std::vector<int> combination;                   // to store the combination
    double area = 0.0;
    double temp_area = 0.0;
    Matrix<double, 6, 3> result;
    Matrix3d temp_points;
    for (int i = 0; i < 2; i++)
    {
        while ((combination = combination_generator.pop()).size())
        {
            for (int j = 0; j < 3; j++)
                if (i)
                    temp_points.row(j) = struct2.row(combination[j]);
                else
                    temp_points.row(j) = struct1.row(combination[j]);
            temp_area = cal_triangle_area(temp_points);
            if (temp_area > area)
            {
                area = temp_area;
                result.block(i * 3, 0, 3, 3) = temp_points;
            }
        }
        combination_generator.restart();
        area = 0.0;
    }
    return result;
}

#define mysquare(A) (A) * (A)
void StructComp::rotate_struct1(Vector4d vect)
{
    Matrix3d mat;
    using std::pow;
    mat(0, 0) = mysquare(vect(0)) + mysquare(vect(1)) - mysquare(vect(2)) - mysquare(vect(3));
    mat(0, 1) = 2 * (vect(1) * vect(2) + vect(0) * vect(3));
    mat(0, 2) = 2 * (vect(1) * vect(3) - vect(0) * vect(2));
    mat(1, 0) = 2 * (vect(1) * vect(2) - vect(0) * vect(3));
    mat(1, 1) = mysquare(vect(0)) + mysquare(vect(2)) - mysquare(vect(1)) - mysquare(vect(3));
    mat(1, 2) = 2 * (vect(2) * vect(3) + vect(0) * vect(1));
    mat(2, 0) = 2 * (vect(1) * vect(3) + vect(0) * vect(2));
    mat(2, 1) = 2 * (vect(2) * vect(3) - vect(0) * vect(1));
    mat(2, 2) = pow(vect(0), 2) + pow(vect(3), 2) - pow(vect(1), 2) - pow(vect(2), 2);
    Vector3d temp;
    for (int i = 0; i < atom_num; i++)
    {
        temp = mat * struct1.row(i).transpose();
        struct1.row(i) = temp.transpose();
    }
}

void StructComp::pair()
{
    Matrix<int, Dynamic, 1> pair_list;
    Matrix<int, Dynamic, 1> pair_status;
    pair_list.resize(atom_num);
    pair_status.resize(atom_num);
    for (int i = 0; i < atom_num; i++)
    {
        pair_list[i] = 0;
        pair_status[i] = 0;
    }
    std::map<int, double> distance;
    double dist = 0.0;
    int index = 0;
    for (int i = 0; i < atom_num; i++)
    {
        // calculate the distance from point[i] in struct1 to point[j] not paired in struct2
        for (int j = 0; j < atom_num; j++)
            if (!pair_status(j)) // not paired
                distance[j] = (struct1.row(i) - struct2.row(j)).norm();
        // find out the minimumn distance and its index
        index = distance.begin()->first; // init index
        dist = distance.begin()->second; // init dist
        for (auto n : distance)
            if (n.second < dist)
            {
                dist = n.second;
                index = n.first;
            }
        // record the pair result
        pair_status[index] = 1;
        pair_list[i] = index;
        distance.clear();
    }
    // make the pair result come into effect
    Matrix<double, Dynamic, 3> temp = struct2;
    for (int i = 0; i < atom_num; i++)
        struct2.row(i) = temp.row(pair_list[i]);
}

double StructComp::strict_rms(Vector4d q)
{
    double result = 0.0;
    double q1, q2, q3, q4;
    q1 = q(0);
    q2 = q(1);
    q3 = q(2);
    q4 = q(3);
    for (int i = 0; i < atom_num; i++)
    {
        result += mysquare(q2 * struct_minus(i, 0) + q3 * struct_minus(i, 1) + q4 * struct_minus(i, 2));
        result += mysquare(q1 * struct_minus(i, 0) + q3 * struct_plus(i, 2) - q4 * struct_plus(i, 1));
        result += mysquare(q1 * struct_minus(i, 1) + q4 * struct_plus(i, 0) - q2 * struct_plus(i, 2));
        result += mysquare(q1 * struct_minus(i, 2) + q2 * struct_plus(i, 1) - q3 * struct_plus(i, 0));
    }
    return std::sqrt(result / atom_num);
}