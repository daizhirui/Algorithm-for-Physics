#include <iostream>
#include <vector>
#include "Eigen/Dense"
#include "terminal_IO.h"
using namespace Eigen;

class StructComp
{
  private:
    Matrix<double, Dynamic, 3> struct_plus;  // molecules_1 + molecules_2
    Matrix<double, Dynamic, 3> struct_minus; // molecules_2 - molecules_1
    Matrix4d diff_mat;
    SelfAdjointEigenSolver<Matrix4d> solver;

  public:
    int atom_num;                       // number of atoms in a molecules
    Matrix<double, Dynamic, 3> struct1; // molecules_1
    Matrix<double, Dynamic, 3> struct2; // molecules_2
    Matrix<double, 1, 3> center1;       // center of struct1
    Matrix<double, 1, 3> center2;       // center of struct2
    Matrix4d eigen_vectors;             // eigen_vectors
    Vector4d eigen_values;              // eigen_values
    Vector4d rms;                       // root mean square distance of atoms
    Vector4d spin_angle;                // the angle to rotate of a manipulation
    Matrix<double, 3, 4> spin_pivot;    // the pivot of a rotation
    // Construct Function
    StructComp(ParamBox &);                 // post by ParamBox
    StructComp(Matrix<double, Dynamic, 3>); // post by Matrix
    void move_center();                     // Adjust the position of the center
    void update_matrix();                   // update all the matrices
    // Calculation Function
    void cal_eigenvectors();
    void cal_eigenvalues();
    void cal_rms();
    void cal_spinparam();
    void cal_all();
    static double cal_triangle_area(const Matrix3d &);
    Matrix<double, 6, 3> max_triangle();
    void rotate_struct1(Vector4d vect);
    void pair();
    double strict_rms(Vector4d);
};
