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

    if (v.auto_pair)
    {
        Matrix<double, 6, 3> points = comp.max_triangle();
        StructComp quick_comp(points);
        Permutation permutation_generator(3, 3);
        vector<int> perm;
        vector<int> best_perm;
        double min_eigenvalue = 0;
        Vector4d best_eigenvector;
        while ((perm = permutation_generator.pop()).size())
        {
            for (int i = 0; i < 3; i++)
                quick_comp.struct2.row(i) = points.row(3 + perm[i]);
            quick_comp.update_matrix();
            quick_comp.cal_eigenvalues();
            int index;
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
            << "         Auto pair = " << (v.auto_pair ? "ON" : "OFF") << endl
            << "-----------------------------------------------" << endl
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
