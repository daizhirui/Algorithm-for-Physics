#include <string>

#ifndef TERMINAL_IO_H
#define TERMINAL_IO_H

typedef struct
{
    std::string in_filename;
    std::string out_filename;
} ParamBox;
struct option_explanation
{
    std::string long_option_name;
    std::string short_option_name;
    std::string default_value;
    std::string option_information;
};
void usage();
void print_usage(const option_explanation *, int);
void process_param(int argc, char *argv[], ParamBox &);
#endif