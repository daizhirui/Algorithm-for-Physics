#include <iostream>
#include "../../Eigen/Dense"

using namespace std;
using namespace Eigen;

int main()
{
    cout << "------------------------------------" << endl;
    cout << "        SIZE SET AT RUN TIME        " << endl;
    // build a 3x3 matrix
    // element value is Random
    MatrixXd m1 = MatrixXd::Random(3,3);
    cout << "m1 = " << endl << m1 << endl;
    // build a 3x3 matrix
    // all coefficients are the same, 1.2
    MatrixXd m2 = MatrixXd::Constant(3,3,1.2);
    cout << "m2 = MatrixXd::Constant(3,3,1.2) = " << endl << m2 << endl;
    // 
    m1 = (m1 + m2) * 50;
    cout << "m1 = " << endl << m1 << endl;
    VectorXd v1(3);
    v1 << 1, 2, 3;
    cout << "m1 * v1 = " << endl << m1 * v1 << endl;

    cout << "------------------------------------" << endl;
    cout << "      SIZE SET AT COMPILE TIME      " << endl;
    Matrix3d m3 = Matrix3d::Random();
    Matrix3d m4 = Matrix3d::Constant(1.2);
    m3 = (m3 + m4) * 50;
    cout << "m3 = " << endl << m3 << endl;
    cout << "m4 = Matrix3d::Constant(1.2) = " << endl << m4 << endl;
    Vector3d v2(1,2,3);
    cout << "m3 * v2 = " << endl << m3 * v2 << endl;
    return 0;
}