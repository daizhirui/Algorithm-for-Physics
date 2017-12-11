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
    cout << "Usage: Brown Dynamics of Single Particle" << endl
         << "  -h                   Print this usage." << endl
         << "  --dimension -d       The dimension of the space to walk" << endl
         << "  --gamma -g           The gamma of mass*gamma*velocity" << endl
         << "  --mass -m            The mass of the particle" << endl
         << "  --totalstep -n       The total time to simulate" << endl
         << "  --deltaT -t          The length of time of single step" << endl
         << "  --temperature -T     The temperature" << endl
         << "  --file -o            The file to store the result." << endl;
}

void process_param(int argc, char* argv[], ParamBox &paramBox)
{
    int opt;
    int option_index;
    static struct option long_options[] = {
        {"dimension", required_argument, NULL, 'd'},
        {"gamma", required_argument, NULL, 'g'},
        {"mass", required_argument, NULL, 'm'},
        {"totalstep", required_argument, NULL, 'n'},
        {"deltaT", required_argument, NULL, 't'},
        {"temperature", required_argument, NULL, 'T'},
        {"file", required_argument, NULL, 'o'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, ":d:g:m:n:t:T:o:h", long_options, &option_index)) != -1)
    {
        switch(opt)
        {
            case 'h':
                usage();
                exit(STATUS_OK);
            case 'd':
                paramBox.dimension = atoi(optarg);
                break;
            case 'g':
                paramBox.gamma = atof(optarg);
            case 'o':
                paramBox.filename.clear();
                paramBox.filename.append(optarg);
                break;
            case 'm':
                paramBox.mass = atof(optarg);
                break;
            case 'n':
                paramBox.totalstep = atoi(optarg);
                break;
            case 't':
                paramBox.deltaT = atof(optarg);
                break;
            case 'T':
                paramBox.temperature = atof(optarg);
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
