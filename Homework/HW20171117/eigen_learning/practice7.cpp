#include <iostream>
#include "../../Eigen/Dense"
using namespace Eigen;
using namespace std;
int main()
{
    MatrixXd mat(4, 4);
    mat << 80,   0, -80,   0,
  0, 112,   0, -48,
-80,   0,  80,   0,
  0, -48,   0, 112;
    SelfAdjointEigenSolver<MatrixXd> solver1(mat);
    cout << "SelfAdjointEigenSolver: " << endl
         << solver1.eigenvalues() << endl << endl
         << solver1.eigenvectors() << endl << endl
         << solver1.eigenvectors().block(0,0,4,1) << endl << endl;
    Matrix4d    result = solver1.eigenvectors();
    cout << "result: " << endl
         << result << endl << endl;
    EigenSolver<MatrixXd> solver2(mat);
    cout << "EigenSolver: " << endl
         << solver2.eigenvalues() << endl << endl
         << solver2.eigenvectors() << endl << endl;
}
