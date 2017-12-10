#include <iostream>
#include <vector>
#include <fstream>
#include "StructComp.h"
#include "Permutation/Permutation.h"
using namespace std;
int main(int argc, char *argv[])
{
    ParamBox v;
    v.in_filename = "molecule.json";
    v.out_filename = "result";
    v.auto_pair = false;
    process_param(argc, argv, v);
    json_in(v);

    StructComp comp(v);
    Matrix<double, 6, 3> points = comp.max_triangle();
    StructComp quick_comp(points);

    if (v.auto_pair)
    {
        Permutation permutation_generator(3, 3);
        vector<int> perm;
        vector<int> best_perm;
        int index;
        quick_comp.cal_all();
        double min_eigenvalue = quick_comp.eigen_values.minCoeff(&index);
        Vector4d    best_eigenvector = quick_comp.eigen_vectors.col(index);
        while ((perm = permutation_generator.pop()).size())
        {
            for (int i = 0; i < 3; i++)
                quick_comp.struct2.row(i) = points.row(3 + perm[i]);
            quick_comp.update_matrix();
            quick_comp.cal_eigenvalues();
            double temp_min_eigenvalue = quick_comp.eigen_values.minCoeff(&index);
            if (temp_min_eigenvalue < min_eigenvalue)
            {
                min_eigenvalue = temp_min_eigenvalue;
                quick_comp.cal_eigenvectors();
                best_eigenvector = quick_comp.eigen_vectors.col(index);
            }
        }
        comp.rotate_struct1(best_eigenvector);
        comp.pair();
    }

    comp.update_matrix();
    comp.cal_all();

    ofstream ofs;
    ofs.open(v.out_filename + ".txt", ios::out);
    if (!ofs.is_open())
    {
        cout << "Fail to create the file stream!" << endl;
        exit(-1);
    }
    else
    {
        ofs << "Molecule data file = " << v.in_filename << endl
            << "         Auto pair = " << (v.auto_pair ? "ON" : "OFF") << endl;
        if(v.auto_pair)
        {
            ofs << "Pair Result:" << endl
                << "Molecule1: " << endl
                << quick_comp.struct1 << endl
                << "Molecule2: " << endl
                << quick_comp.struct2 << endl;
        }
        ofs << "-----------------------------------------------" << endl
            << "The structure of molecule1:" << endl
            << comp.struct1 << endl
            << "-----------------------------------------------" << endl
            << "The structure of molecule2:" << endl
            << comp.struct2 << endl
            << "-----------------------------------------------" << endl
            << "R.M.S = " << endl
            << comp.rms << endl
            << "-----------------------------------------------" << endl
            << "Eigen Values = " << endl
            << comp.eigen_values << endl
            << "-----------------------------------------------" << endl
            << "Eigen Vectors = " << endl
            << comp.eigen_vectors << endl
            << "-----------------------------------------------" << endl;
    }

    cout << "The structure of molecule1, struct1 = " << endl
         << comp.struct1 << endl
         << endl
         << "The structure of molecule2, struct2 = " << endl
         << comp.struct2 << endl
         << endl
         << "rms = " << endl
         << comp.rms << endl
         << endl
         << "strict rms = " << endl
         << comp.strict_rms(comp.eigen_vectors.col(0)) << endl
         << comp.strict_rms(comp.eigen_vectors.col(1)) << endl
         << comp.strict_rms(comp.eigen_vectors.col(2)) << endl
         << comp.strict_rms(comp.eigen_vectors.col(3)) << endl
         << endl
         << "eigen_values = " << endl
         << comp.eigen_values << endl
         << endl
         << "eigen_vectors = " << endl
         << comp.eigen_vectors << endl
         << endl;
    int index;
    comp.eigen_values.minCoeff(&index);
    comp.rotate_struct1(comp.eigen_vectors.col(index));
    cout << "Select the rotation of minimum rms" << endl
         << "After rotation, struct1 = " << endl
         << comp.struct1 << endl
         << endl;
    ofs << "After the rotation, the structure of molecule1:" << endl
        << comp.struct1 << endl;
    return 0;
}
