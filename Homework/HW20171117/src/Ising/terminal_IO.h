#include <string>
using namespace std;
#ifndef TERMINAL_IO_H
#define TERMINAL_IO_H

typedef struct
{
    int     step;
    int     size;
    double  mutual_coeff;
    double  temperature;
    double  std_error;
    string  filename;
} ParamBox;
void usage();
void process_param(int argc, char* argv[], ParamBox&);

#endif