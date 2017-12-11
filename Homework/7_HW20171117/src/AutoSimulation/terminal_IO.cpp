#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <getopt.h>
#include "terminal_IO.h"
#include "STATUS_CODE.h"

#ifdef __linux__
#include <cstdlib>
#endif

using namespace std;

void usage()
{
    cout << "Usage: AutoSimulation Program" << endl
         << "  -h                   Print this usage." << endl
         << "  --program -p         The name of the program file" << endl
         << "  --static_flag -s     The static flag to send to the program, except output flag" << endl
         << "  --output_flag -o     The output flag of the program" << endl
         << "  --dynamic_flag -d    The dynamic flag to send to the program" << endl
         << "  --begin -b           The begin value of the value range of dynamic flag" << endl
         << "  --interval -i        The interval value of the value range" << endl
         << "  --end -e             The end value of the value range of dynamic flag" << endl;
}

string process_optarg(string str)
{
    long len = str.size();
    if((long)str.find_first_of('\"') != 0 || (long)str.find_last_of('\"') != (len -1))
    {
        cout << str << " must be wrapped by \" !";
        //exit(STATUS_PARAM_ERROR);
    }
    return str.substr(1, len - 1 );
}

void process_param(int argc, char* argv[], ParamBox &paramBox)
{
    int opt;
    int option_index;
    static struct option long_options[] = {
        {"program", required_argument, NULL, 'p'},
        {"static_flag", required_argument, NULL, 's'},
        {"output_flag", required_argument, NULL, 'o'},
        {"dynamic_flag", required_argument, NULL, 'd'},
        {"begin", required_argument, NULL, 'b'},
        {"interval", required_argument, NULL, 'i'},
        {"end", required_argument, NULL, 'e'}
    };

    while ((opt = getopt_long(argc, argv, ":p:s:o:d:b:i:e:h", long_options, &option_index)) != -1)
    {
        switch(opt)
        {
            case 'h':
                usage();
                exit(STATUS_OK);
            case 'p':
                paramBox.program = optarg;
                break;
            case 's':
                paramBox.static_flag = optarg;
                break;
            case 'o':
                paramBox.output_flag = optarg;
                break;
            case 'd':
                paramBox.dynamic_flag = optarg;
                break;
            case 'b':
                paramBox.begin = atof(optarg);
                break;
            case 'i':
                paramBox.interval = atof(optarg);
                break;
            case 'e':
                paramBox.end = atof(optarg);
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

bool isLegal(ParamBox &paramBox)
{
    if(paramBox.program == "")
    {
        cout << "No program is specified!" << endl;
        usage();
        exit(STATUS_PARAM_ERROR);
    }
    if(paramBox.output_flag == "")
    {
        cout << "No output flag is specified!" << endl;
        usage();
        exit(STATUS_PARAM_ERROR);
    }
    if(paramBox.dynamic_flag != "")
        if((paramBox.end - paramBox.begin) * paramBox.interval < 0)
        {
            cout << "begin = " << paramBox.begin << endl
                << "interval = " << paramBox.interval << endl
                << "end = " << paramBox.end << endl;
            cout << "Dynamic setting fails, dead loop!" << endl;
            usage();
            exit(STATUS_PARAM_ERROR);
        }
    return true;
}

string generate_command(ParamBox v, const int &i)
{
    ostringstream ssm;
    double value = i * v.interval + v.begin;
    ssm.str("");
    ssm << "./" << v.program
        << " " << v.static_flag
        << " " << v.dynamic_flag
        << " " << value
        << " " << v.output_flag
        << " " << "result_of_" << v.program
        << "_" << value;
    return ssm.str();
}