#include <iostream>
#include <sstream>
#include "terminal_IO.h"
#include "STATUS_CODE.h"

#ifdef __linux__
#include <cstdlib>
#endif

int main(int argc, char* argv[])
{
    ParamBox paramBox;
    paramBox.program = "";
    paramBox.static_flag = "";
    paramBox.output_flag = "";
    paramBox.dynamic_flag = "";
    paramBox.begin = 0;
    paramBox.interval = 0;
    paramBox.end = 0;
    process_param(argc, argv, paramBox);
    string command;
    int step = (paramBox.end - paramBox.begin) / paramBox.interval;
    if(isLegal(paramBox))
    {
        for(int i = 0; i <= step; i++)
        {
            command = generate_command(paramBox, i);
            cout << command << endl;
            system(command.c_str());
        }
    }
}