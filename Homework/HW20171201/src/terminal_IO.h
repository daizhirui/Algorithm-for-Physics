#include <string>

using namespace std;

#ifndef TERMINAL_IO_H
#define TERMINAL_IO_H

typedef struct
{
    int     dimension;
    double  gamma;
    double  mass;
    int     totalstep;
    double  deltaT;
    double  temperature;
    string  filename;
} ParamBox;
void usage();
void process_param(int argc, char* argv[], ParamBox&);

#endif