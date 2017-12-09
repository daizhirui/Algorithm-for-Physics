#include <iostream>
#include <fstream>
#include "Config.h"
#include "terminal_IO.h"
#include "Ising.h"
#include "ConvergenceMonitor.h"

using namespace std;
int main(int argc, char* argv[])
{
    ParamBox paramBox;
    paramBox.step = 15000000;
    paramBox.size = 100;
    paramBox.mutual_coeff = 1.0;
    paramBox.temperature = 1.0;
    paramBox.filename = "result";
    paramBox.std_error = 0;
    process_param(argc, argv, paramBox);

    fstream ofs;
    ofs.open((paramBox.filename+".txt").c_str(), ios::out);
    if(!ofs.is_open())
    {
        cout << "Fail to create the file  stream!" << endl;
        exit(-1);
    }
    else
    {
        ofs << "Simulated by ISING, VERSION " << ISING_VERSION << endl;
        ofs << "filename = " << paramBox.filename << endl;
        ofs << "step = " << paramBox.step << endl;
        ofs << "mutual_coefficient = " << paramBox.mutual_coeff << endl;
        ofs << "temperature = " << paramBox.temperature << endl;
        ofs << "ATTEENTION: 1ST_STD_ERROR and 2ND_STD_ERROR are calculated per 100 steps" << endl;
        ofs << "STEP\tMAGNETISM\tENERGY\t1ST_STD_ERROR\t2ND_STD_ERROR"  << endl;
    }

    Ising ising(paramBox);
    ConvergenceMonitor first_monitor(10000);
    ConvergenceMonitor second_monitor(10);
    double totalE, totalM, first_std_err, second_std_err;
    for(int i = 0; i < paramBox.step; i++)
    {
        ising.flip();
        totalE = ising.total_Energy();
        totalM = ising.total_Magnetism();
        first_monitor.add(ising.total_Magnetism());
        if(i % 100 == 0)
        {
            first_std_err = first_monitor.standard_error();
            second_monitor.add(first_std_err);
            second_std_err = second_monitor.standard_error();
        }
        ofs << i << '\t' << totalM << '\t' << totalE << '\t' << first_std_err << '\t' << second_std_err << endl;
        if(second_std_err < paramBox.std_error && i > 100)
        {
            cout << "The simulation is convergent now, stopped automatically." << endl;
            return 0;
        }
    }
    ofs.close();
    return 0;
}