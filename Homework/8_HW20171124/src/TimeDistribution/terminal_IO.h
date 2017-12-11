#include <string>
using namespace std;
#ifndef TERMINAL_IO_H
#define TERMINAL_IO_H

typedef struct
{
    int     dimension;
    int     sample_volume;
    double  possibility;
    double  steplen;
    double  target_distance;
    double  distance_error;
    string  filename;
} ParamBox;
void usage();
void process_param(int argc, char* argv[], ParamBox&);

#endif