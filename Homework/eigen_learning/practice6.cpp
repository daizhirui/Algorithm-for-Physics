#include <iostream>
#include "../../Eigen/Dense"
using namespace Eigen;
using namespace std;

int main()
{
    MatrixXd mat(4, 4);
    mat << 1, 2, 3, 4,
           5, 6, 7, 8,
           9, 10,11,12,
           13,14,15,16;
    cout << mat.size() << endl << endl;
    cout << mat.rowwise().squaredNorm() << endl << endl;
    cout << mat.colwise().squaredNorm() << endl << endl;
    cout << mat.block(0, 0, 4, 1).array().square() << endl << endl;
    cout << mat.array().sqrt() << endl << endl;
    //cout << mat.block<2,2>(1,3) << endl; // This line has problems!
    Matrix<double, 1, 4>    vect;
    vect << 1, 1, 1, 1;
    MatrixXd mat_temp(4, 4);
    mat = mat.rowwise() - vect;
    //mat = mat_temp;
    cout << mat << endl;
    Matrix<double, Dynamic, 1> vectx;
    vectx(3) = 0;
    cout << vectx << endl;
}
