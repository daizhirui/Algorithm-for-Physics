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
    cout << "Usage: ISING Program" << endl
         << "  -h                   Print this usage." << endl
         << "  --step -n            The step to simulate" << endl
         << "  --mutual_coeff -j    The mutual effect coefficient" << endl
         << "  --size -s            The size of the lattice" << endl
         << "  --temperature -T     The temperature to analyze."  << endl
         << "  --std_error -R       When used, automatically stop simulation" << endl
         << "                       when it meets the standard error" << endl
         << "  --file -o            The file to store the result." << endl;
}

void process_param(int argc, char* argv[], ParamBox &paramBox)
{
    int opt;
    int option_index;
    static struct option long_options[] = {
        {"step", required_argument, NULL, 'n'},
        {"mutual_coeff", required_argument, NULL, 'j'},
        {"std_error", required_argument, NULL, 'R'},
        {"size", required_argument, NULL, 's'},
        {"temperature", required_argument, NULL, 'T'},
        {"file", required_argument, NULL, 'o'}
    };

    while ((opt = getopt_long(argc, argv, ":j:o:T:h", long_options, &option_index)) != -1)
    {
        switch(opt)
        {
            case 'h':
                usage();
                exit(STATUS_OK);
            case 'j':
                paramBox.mutual_coeff = atof(optarg);
                break;
            case 'n':
                paramBox.step = atoi(optarg);
                break;
            case 'o':
                paramBox.filename.clear();
                paramBox.filename.append(optarg);
                break;
            case 'R':
                paramBox.std_error = atof(optarg);
                break;
            case 's':
                paramBox.size = atoi(optarg);
                break;
            case 'T':
                paramBox.temperature = atof(optarg);
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
