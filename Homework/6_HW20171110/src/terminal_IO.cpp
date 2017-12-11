#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "terminal_IO.h"
#include "STATUS_CODE.h"
void seq(const char* filename)
{
	srand(time(0));
	ofstream out_file;
	out_file.open(filename,ios::out);
	for (int i = 0; i < 1000000; ++i)
	{
		string str;
		for (int j = 0; j < 5; ++j)
		{
			int n = rand() % 10;
			char ch = (char)(n + 65);
			if (str.find(ch) == string::npos)
				str.push_back(ch);
		}
		out_file << str << endl;
	}
	out_file.close();
}

void usage()
{
    printf("Usage: String Statistics Program\n");
    printf("\t-h\tPrint this usage.\n");
    printf("\t-f\tThe file to analyze.\n");
    printf("\t-g\tGenerate a sample file\n");
    printf("\t-o\tThe file to store the result.\n");
}

void process_param(int argc, char* argv[], string& in_file, string& out_file)
{
    int opt;
    while ((opt = getopt(argc, argv, ":f:o:gh")) != -1)
    {
        switch(opt)
        {
            case 'h':
                usage();
                exit(STATUS_OK);
            case 'f':
                in_file.clear();
                in_file.append(optarg);
                break;
            case 'g':
                seq("seq.txt");
                exit(0);
            case 'o':
                out_file.clear();
                out_file.append(optarg);
                break;
            case '?':
                printf("Error: option \'-%c\' is unavailable!\n", (char)optopt);
                usage();
                exit(STATUS_PARAM_ERROR);
            // Lack of parameters.
            case ':':
                printf("Error: option \'-%c\' requires a parameter!\n", (char)optopt);
                usage();
                exit(STATUS_PARAM_ERROR);
        }
    }
}
