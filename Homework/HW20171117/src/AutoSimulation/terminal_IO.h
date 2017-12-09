#include <string>
using namespace std;
#ifndef TERMINAL_IO_H
#define TERMINAL_IO_H

typedef struct
{
    string  program;
    string  static_flag;
    string  output_flag;
    string  dynamic_flag;
    double  begin;
    double  interval;
    double  end;
} ParamBox;
void usage();
void process_param(int argc, char* argv[], ParamBox&);
bool isLegal(ParamBox &paramBox);
string generate_command(ParamBox v, const int &i);
#endif