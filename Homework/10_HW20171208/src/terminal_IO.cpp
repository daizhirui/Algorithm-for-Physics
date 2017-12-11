#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <getopt.h>
#include "terminal_IO.h"
#include "STATUS_CODE.h"
#ifdef __linux__
#include <stdlib.h>
#endif
#define psln(x) std::cout << #x " = " << (x) << std::endl
// entrance to print_usage
void usage()
{
    static struct option_explanation optexp[] = {
        {"help", "h", "", "Print this usage"},
        {"input", "i", "1COA.pdb", "The file to read in"},
        {"output", "o", "result.txt", "The file to store the result"}};
    print_usage(optexp, sizeof(optexp) / sizeof(option_explanation));
}
// to print the help information to the screen
void print_usage(const option_explanation *optexp, int optnum)
{
    unsigned int max_longopt_len = 0;
    unsigned int max_default_len = 0;
    // calculate max_default_len and max_longopt_len
    for (int i = 0; i < optnum; i++)
    {
        if (optexp[i].long_option_name.size() > max_longopt_len)
            max_longopt_len = optexp[i].long_option_name.size();
        if (optexp[i].default_value.size() > max_default_len)
            max_default_len = optexp[i].default_value.size();
    }
    // print title
    std::cout << "Interface of Molecule System" << std::endl
              << "  Usage: " << std::endl;
    // print table head
    std::string str;
    str = "LONG OPTION";
    int spacelen;
    std::cout << "    " << str;
    spacelen = max_longopt_len - str.size() + 2;
    for (int i = 0; i < spacelen; i++)
        std::cout << ' ';
    std::cout << "  SHORT   DEFAULT";
    spacelen = max_default_len - 5;
    for (int i = 0; i < spacelen; i++)
        std::cout << ' ';
    std::cout << "DESCRIPTION" << std::endl;
    // print options and their information
    for (int i = 0; i < optnum; i++)
    {
        std::cout << "    --" << optexp[i].long_option_name;
        spacelen = max_longopt_len - optexp[i].long_option_name.size();
        for (int j = 0; j < spacelen; j++)
            std::cout << ' ';
        std::cout << "     -" << optexp[i].short_option_name
                  << "      " << optexp[i].default_value << "  ";
        spacelen = max_default_len - optexp[i].default_value.size();
        for (int j = 0; j < spacelen; j++)
            std::cout << ' ';
        std::cout << optexp[i].option_information << std::endl;
    }
}
// parse command from terminal to ParamBox
void process_param(int argc, char *argv[], ParamBox &v)
{
    int opt;
    int option_index;
    static struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {0, 0, 0, 0}};  // must end with {0,0,0,0} to avoid segmentfault

    while ((opt = getopt_long(argc, argv, ":i:o:h", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
            usage();
            exit(STATUS_OK);
        case 'i':
            v.in_filename = optarg;
            break;
        case 'o':
            v.out_filename = optarg;
            break;
        case '?':
            std::cout << "Error: option \'" << (char)optopt << "\' is unavailable!" << std::endl;
            usage();
            exit(STATUS_PARAM_ERROR);
        // Lack of parameters.
        case ':':
            std::cout << "Error: option \'" << (char)optopt << "\' requires a parameter!" << std::endl;
            usage();
            exit(STATUS_PARAM_ERROR);
        }
    }
}
