#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include "../RandomWalk/RandomWalk.h"
#include "terminal_IO.h"
using namespace std;

int main(int argc, char* argv[])
{
    ParamBox v;
    v.filename = "result";
    v.dimension = 2;
    v.repeat = 5000000;
    v.possibility = 0.8;
    v.steplen = 1.0;
    v.totalstep = 1000;
    process_param(argc, argv, v);

    ofstream ofs;
    ofs.open("result.txt", ios::out);
    if(!ofs.is_open())
    {
        cout << "Fail to create the file stream!" << endl;
        exit(-1);
    }
    else
    {
        ofs << "Simulated by DistDistribution" << endl
            << "           filename = " << v.filename << endl
            << "    space dimension = " << v.dimension << endl
            << "             repeat = " << v.repeat << endl
            << "walking possibility = " << v.possibility << endl
            << "            steplen = " << v.steplen << endl
            << "          totalstep = " << v.totalstep << endl;
    }

    map<int, int> result;
    for(int i = 0; i<v.repeat; i++)
    {
        RandomWalk rw(v.possibility, v.steplen, v.dimension);
        for(int j = 0; j<v.totalstep; j++)
            rw.move();
        result[floor(rw.distance())]++;
    }
    ofs << "DIST\tCOUNT\tRATIO" << endl;
    for(auto n:result)
    {
        ofs << n.first << '\t' << n.second << '\t' << n.second / (double)v.repeat << endl;
    }
    ofs.close();
    return 0;
}