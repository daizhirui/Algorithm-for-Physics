#include <iostream>
#include <fstream>
#include <vector>
#include "../RandomWalk/RandomWalk.h"
#include "Eigen/Dense"
#include "terminal_IO.h"

#ifdef __linux__
#include <cstdlib>
#endif

using namespace Eigen;

int main(int argc, char* argv[])
{
    ParamBox param;
    param.filename = "result";
    param.dimension = 2;
    param.possibility = 0.8;
    param.steplen = 1.0;
    param.totalstep = 1000;
    process_param(argc, argv, param);

    ofstream ofs;
    ofs.open((param.filename+".txt").c_str(), ios::out);
    if(!ofs.is_open())
    {
        cout << "Fail to create the file stream!" << endl;
        exit(-1);
    }
    else
    {
        ofs << "Simulated by TimeDistRelation" << endl
            << "           filename = " << param.filename << endl
            << "    space dimension = " << param.dimension << endl
            << "walking possibility = " << param.possibility << endl
            << "            steplen = " << param.steplen << endl
            << "          totalstep = " << param.totalstep << endl;
    }

    double r = 0.0;
    Matrix<double, Dynamic, 1> resultX;
    Matrix<double, Dynamic, 1> resultY;
    resultX.resize(param.totalstep);
    resultY.setConstant(param.totalstep, 1, 0.0);
    for(int i = 0; i < param.totalstep; i++)
        resultX(i) = (double)i;

    double temp;
    int count = 0;  // store the number of completed simulations
    // calculation the l_xx
    double x_sum = resultX.sum();
    double x2_sum = resultX.squaredNorm();
    double l_xx = x2_sum - std::pow(x_sum,2) / param.totalstep;
    double l_xy = 0;    // l_xy
    double l_yy = 0;    // l_yy
    while(r < 0.999)
    {
        RandomWalk rw(param.possibility, param.steplen, param.dimension);
        for(int i = 0; i < param.totalstep; i++)
        {
            rw.move();
            temp = (resultY(i) * count + std::pow(rw.distance(),2)) / (count + 1);
            resultY(i) = temp;
        }
        count++;
        if(count % 2)
        {
            l_xy = (resultX.array() * resultY.array()).sum() - (x_sum * resultY.sum()) / param.totalstep;
            l_yy = resultY.squaredNorm() - pow(resultY.sum(),2) / param.totalstep;
            r = l_xy / std::sqrt(l_xx * l_yy);
            cout << l_xy << ' ' << l_xx << ' ' << l_yy << ' ' << r << endl;
        }
    }
    double k = l_xy / l_xx;
    double b = resultY.mean() - k * x_sum / param.totalstep;
    ofs << "The relation between DIST^2 and TIME: " << endl
        << "WITH    INTERCEPTION: DIST^2 = " << k << " * TIME + " << b << endl
        << "WITHOUT INTERCEPTION: DIST^2 = " << (resultX.array() * resultY.array()).sum() / x2_sum << " * TIME " << endl
        << "R = " << r << endl;
    ofs << "DATA: " << endl << "TIME\tDIST^2\tDIST" << endl;
    for(int i = 0; i < param.totalstep; i++)
        ofs << i << '\t' << resultY(i) << '\t' << std::sqrt(resultY(i)) << endl;
    ofs.close();
    return 0;
}