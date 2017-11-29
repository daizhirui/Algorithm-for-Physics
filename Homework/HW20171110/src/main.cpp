#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "StrMap.h"
#include "terminal_IO.h"
#include "STATUS_CODE.h"
using namespace std;

int main(int argc, char* argv[])
{
    // Terminal IO: get parameters in
    string in_filestr = "seq.txt";
    string out_filestr = "result";
    process_param(argc, argv, in_filestr, out_filestr);
    // Read data from specific file and store data
    ifstream in_file(in_filestr, ios::in);
    if(in_file.fail())
    {
        cout << in_filestr << " does not exist!" << endl;
        exit(STATUS_PARAM_ERROR);
    }
    StrMap strMap;
    int line = 0;
    while(!in_file.eof())
    {   
        string temp;
        getline(in_file, temp);
        strMap.add(temp);
        line++;
    }
    in_file.close();
    // print the result
    strMap.printJSONResult(out_filestr+".json");
    strMap.printTXTResult(out_filestr+".txt");
    cout << "result is store in " << out_filestr+".json" << " and " << out_filestr+".txt" << endl;
    return 0;
}