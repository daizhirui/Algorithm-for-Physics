//
//  practice1.cpp
//
//  Created by astro on 2017/11/29.
//  Copyright © 2017年 astro. All rights reserved.
//
#include <iostream>
#include "../../Eigen/Dense"

using namespace std;
using Eigen::MatrixXd;

int main()
{
    MatrixXd m(2,2);            // build a 2x2 matrix
    m(0,0) = 3;                 // modified the elements in the matrix
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    cout << m << endl;          // output this matrix
    return 0;
}