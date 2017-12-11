#include <iostream>
#include "../../Eigen/Dense"
using namespace std;
int main()
{
  Eigen::Matrix2d mat;
  std::ptrdiff_t i, j;
  mat << 1, 2,
         3, 4;
  cout << "mat = " << endl << mat << endl;
  cout << "Here is mat.sum():       " << mat.sum()       << endl;
  cout << "Here is mat.prod():      " << mat.prod()      << endl;
  cout << "Here is mat.mean():      " << mat.mean()      << endl;
  cout << "Here is mat.minCoeff():  " << mat.minCoeff()  << endl;
  mat.minCoeff(&i, &j);
  cout << "mat.minCoeff(&i, &j) returns the position" << '(' << i << ',' << j << ')' << endl;
  cout << "Here is mat.maxCoeff():  " << mat.maxCoeff()  << endl;
  cout << "Here is mat.trace():     " << mat.trace()     << endl;
  cout << "Here is mat.diagonal().sum(): " << mat.diagonal().sum() << endl;
}