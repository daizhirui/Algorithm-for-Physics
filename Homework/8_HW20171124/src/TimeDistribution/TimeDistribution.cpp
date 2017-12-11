#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include "../RandomWalk/RandomWalk.h"
#include "terminal_IO.h"

#ifdef __linux__
#include <cstdlib>
#endif

int main(int argc, char* argv[])
{
    ParamBox param;
    param.filename = "result";
    param.dimension = 2;
    param.possibility = 0.8;
    param.steplen = 1.0;
    param.target_distance = 40.0;
    param.distance_error = 1;
    param.sample_volume = 50000000;
    process_param(argc, argv, param);
    // calculate the number of steps to walk every time
    int totalstep = pow(param.target_distance/param.possibility/param.steplen,2);
    totalstep *= 10;

    ofstream ofs;
    ofs.open((param.filename+".txt").c_str(), ios::out);
    if(!ofs.is_open())
    {
        cout << "Fail to create the file stream!" << endl;
        exit(-1);
    }
    else
    {
        ofs << "Simulated by TimeDistribution" << endl
            << "           filename = " << param.filename << endl
            << "    space dimension = " << param.dimension << endl
            << "walking possibility = " << param.possibility << endl
            << "            steplen = " << param.steplen << endl
            << "          totalstep = " << totalstep << endl
            << "    target_distance = " << param.target_distance << endl
            << "     distance_error = " << param.distance_error << endl
            << "      sample_volume = " << param.sample_volume << endl
            << "TIME\tCOUNT\tRATIO" << endl; 
    }


    map<int, double>   result; // a map to store the result
    int count = 0;  // store the number of samples we have collected
    double down_edge = param.target_distance - param.distance_error;
    double up_edge = param.target_distance + param.distance_error;
    int simulation_count = 0;
    while(count <= param.sample_volume)
    {
        RandomWalk rw(param.possibility, param.steplen, param.dimension);
        double dist;
        for(int i = 0; i < totalstep; i++)
        {
            rw.move();
            dist = rw.distance();
            if(dist >= down_edge && dist < up_edge)
            {
                cout << "time = " << i << ", " << "distance = " << dist << endl;
                result[i]++;
                count++;
            }
        }
        simulation_count++;
    }

    //for(auto n:result)
    //{
    //    ofs << n.first << '\t' << n.second << '\t' << n.second/count << endl;     // count is the real sample_volume
    //}
    for(int i = 0;i<totalstep;i++)
    {
        auto it = result.find(i);
        if(it != result.end())
            ofs << it->first << '\t' << it->second << '\t' << it->second/count << endl;
        else
            ofs << i << '\t' << 0 << '\t' << 0 << endl;
    }
    ofs << endl << "   Simulation Count = " << simulation_count << endl
        << endl << "Final Sample Volume = " << count << endl;
    ofs.close();
    return 0;
}