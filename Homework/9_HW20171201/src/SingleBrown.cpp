#include <iostream>
#include <fstream>
#include <cmath>
#include "terminal_IO.h"
#include "Particle.h"

int main(int argc, char* argv[])
{
    ParamBox v;
    v.deltaT = 0.01;
    v.mass = 1.0;
    v.dimension = 2;
    v.gamma = 0.5;
    v.temperature = 1;
    v.totalstep = 1000000;
    v.filename = "result";
    process_param(argc, argv, v);

    ofstream ofs;
    ofs.open((v.filename+".txt").c_str(), ios::out);
    if(!ofs.is_open())
    {
        cout << "Fail to create the file stream!" << endl;
        exit(-1);
    }
    else
    {
        ofs << "Simulated by TimeDistRelation" << endl
            << "           filename = " << v.filename << endl
            << "    space dimension = " << v.dimension << endl
            << "             deltaT = " << v.deltaT << endl
            << "          totalstep = " << v.totalstep << endl
            << "               mass = " << v.mass << endl
            << "              gamma = " << v.gamma << endl
            << "        temperature = " << v.temperature << endl
            << "TIME\tPOS_X\tPOS_Y" << endl;
    }

    Particle ball(v.deltaT, v.dimension);
    ball.mass = v.mass;
    MyVector vec(v.dimension);
    vec[0] = vec[1] = 0;
    ball.acceleration = vec;
    ball.velocity = vec;
    ball.position = vec;

    MyVector force(v.dimension);
    double coeff1 = 1.0 / (1 + 0.5 * v.gamma * v.deltaT);
    double coeff2 = -v.mass * v.gamma;
    double coeff3 = sqrt(2 * v.mass * v.gamma * v.temperature / v.deltaT);
    for(int i=0;i<v.totalstep;i++)
    {   
        force = coeff1 * (coeff2 * ball.velocity + MyVector::gauss_vector(v.dimension) * coeff3);
        ball.go(force, v.deltaT);
        cout << i * v.deltaT << '\t';
        ofs << i * v.deltaT << '\t';
        for(int j=0;j<v.dimension;j++)
        {
            ofs << ball.position[j] << '\t';
            cout << ball.position[j] << '\t';
        }
        ofs << endl;
        cout << endl;
    }

    return 0;
}