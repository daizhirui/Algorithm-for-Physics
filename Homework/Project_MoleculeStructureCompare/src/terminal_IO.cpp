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
        {"auto_pair", "a", "0", "Auto pair the atoms of two molecules"},
        {"molecule_data", "m", "molecule.json", "The file store positions of molecules' atoms"},
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
    std::cout << "Molecule Structure Mean Difference Program" << std::endl
              << "  Usage: " << std::endl;
    // print table head
    std::string str;
    str = "LONG OPTION";
    int spacelen;
    std::cout << "    " << str;
    spacelen = max_longopt_len - str.size() + 2;
    for (int i = 0; i < spacelen; i++)
        std::cout << ' ';
    std::cout << "SHORT   DEFAULT";
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
        std::cout << "   -" << optexp[i].short_option_name
                  << "   " << optexp[i].default_value << "  ";
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
        {"auto_pair", required_argument, NULL, 'a'},
        {"molecule_data", required_argument, NULL, 'm'},
        {"output", required_argument, NULL, 'o'},
        {0, 0, 0, 0}};  // must end with {0,0,0,0} to avoid segmentfault

    while ((opt = getopt_long(argc, argv, ":a:m:o:h", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
            usage();
            exit(STATUS_OK);
        case 'a':
            v.auto_pair = atoi(optarg);
            break;
        case 'm':
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
// convert input json file to Document container
rapidjson::Document file_to_document(std::string &filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::in);
    if (!ifs.is_open())
    {
        std::cerr << filename << " doesn't exist!" << std::endl
                  << "Fail to open the file." << std::endl;
        exit(-1);
    }
    // convert to string
    std::string stringFromStream, temp;
    while (getline(ifs, temp))
        stringFromStream.append(temp + "\n");
    ifs.close();
    // parse string to Document
    using rapidjson::Document;
    Document doc;
    doc.Parse<0>(stringFromStream.c_str());
    if (doc.HasParseError())
    {
        rapidjson::ParseErrorCode code = doc.GetParseError();
        psln(code);
        exit(-1);
    }
    return doc;
}
// get the data in Document and store the data in vector
void document_to_vector(rapidjson::Document &doc, const std::string &key, std::vector<double> &buffer)
{
    using rapidjson::Value;
    if (doc.HasMember(key.c_str())) // check if doc has the molecule refered by key.
    {
        Value &molecule = doc[key.c_str()]; // get the molecule
        int atom_num = 0;
        if (!molecule.IsObject()) // check if the structure of this molecule is object
        {
            std::cerr << "Member: " << key << " should be an object!" << std::endl;
            exit(-1);
        }
        if (molecule.HasMember("atom_num")) // check if this molecule has member: atom_num
        {
            Value &atom_number = molecule["atom_num"];
            if (atom_number.IsInt()) // check atom_num's type
            {
                atom_num = atom_number.GetInt(); // get atom_num
            }
            else
            {
                std::cerr << key << "'s member, atom_num, should be an interger number!" << std::endl;
                exit(-1);
            }
        }
        else
        {
            std::cerr << key << " lacks a member: atom_num (the number of atoms consisting of this molecule)." << std::endl;
            exit(-1);
        }
        if (molecule.HasMember("data")) // check if this molecule has member: data
        {
            Value &data = molecule["data"]; // get data
            if (data.IsArray())             // check data's type
            {
                int i = 0;
                for (auto &n : data.GetArray()) // get data
                {
                    buffer.push_back(n.GetDouble()); // store to the buffer
                    i++;
                }
                if (buffer.size() == (unsigned int)atom_num * 3) // check the size of data
                    return;
                else
                {
                    std::cerr << key << "'s atom_num conflicts with the size of data!" << std::endl
                              << "atom_num = " << atom_num << std::endl
                              << "data's size = " << buffer.size() << "(It should be 3 * atom_num)." << std::endl;
                }
            }
            else
            {
                std::cerr << key << "'s member, data, should be an array!" << std::endl;
                exit(-1);
            }
        }
        else
        {
            std::cerr << key << " lacks a member: data (the position of all atoms consisting of this molecule)." << std::endl;
            exit(-1);
        }
    }
    else
    {
        std::cerr << "The input file doesn't provide the member: " << key << std::endl;
        exit(-1);
    }
}
// the entrance to analyse json file
void json_in(ParamBox &v)
{
    rapidjson::Document doc = file_to_document(v.in_filename);
    document_to_vector(doc, "molecule1", v.buffer1);
    document_to_vector(doc, "molecule2", v.buffer2);
}
// print tab when writing json file
void printTab(std::ofstream &ofs, int i)
{
    for (int j = 0; j < i; j++)
        ofs << '\t';
}
// convert string to json file
void json_out(std::string &jsonstr, std::string &out_filename)
{
    std::ofstream ofs;
    ofs.open(out_filename + ".json", std::ios::out);
    if (!ofs.is_open())
    {
        std::cerr << "Fail to create file " << out_filename << ".json" << std::endl;
        exit(-1);
    }
    int tabNum = 0;
    for (auto n : jsonstr)
    {
        if (n == '{' || n == ',' || n == '[')
        {
            ofs << n << '\n';
            if (n != ',')
                tabNum++;
            printTab(ofs, tabNum);
        }
        else
        {
            if (n == '}' || n == ']')
            {
                ofs << '\n';
                tabNum--;
                printTab(ofs, tabNum);
                ofs << n;
            }
            else
                ofs << n;
        }
    }
}