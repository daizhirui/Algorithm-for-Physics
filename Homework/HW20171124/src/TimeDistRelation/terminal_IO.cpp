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

using namespace std;

void usage()
{
    cout << "Usage: Random Walk Program" << endl
         << "  -h                   Print this usage." << endl
         << "  --dimension -d       The dimension of the space to walk" << endl
         << "  --totalstep -n       The number of steps to simulate" << endl
         << "  --possibility -p     The possibility to move" << endl
         << "  --steplen -l         The length of single step" << endl
         << "  --file -o            The file to store the result." << endl;
}

void process_param(int argc, char* argv[], ParamBox &paramBox)
{
    int opt;
    int option_index;
    static struct option long_options[] = {
        {"dimension", required_argument, NULL, 'd'},
        {"totalstep", required_argument, NULL, 'n'},
        {"possibility", required_argument, NULL, 'p'},
        {"steplen", required_argument, NULL, 'l'},
        {"file", required_argument, NULL, 'o'}
    };

    while ((opt = getopt_long(argc, argv, ":d:n:o:p:l:h", long_options, &option_index)) != -1)
    {
        switch(opt)
        {
            case 'h':
                usage();
                exit(STATUS_OK);
            case 'd':
                paramBox.dimension = atoi(optarg);
                break;
            case 'n':
                paramBox.totalstep = atoi(optarg);
                break;
            case 'o':
                paramBox.filename.clear();
                paramBox.filename.append(optarg);
                break;
            case 'p':
                paramBox.possibility = atof(optarg);
                break;
            case 'l':
                paramBox.steplen = atof(optarg);
                break;
            case '?':
                cout << "Error: option \'" << (char)optopt << "\' is unavailable!" << endl;
                usage();
                exit(STATUS_PARAM_ERROR);
            // Lack of parameters.
            case ':':
                cout << "Error: option \'" << (char)optopt << "\' requires a parameter!" << endl;
                usage();
                exit(STATUS_PARAM_ERROR);
        }
    }
}
