#include <string>
#include <vector>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#ifndef TERMINAL_IO_H
#define TERMINAL_IO_H

typedef struct
{
    std::vector<double> buffer1;
    std::vector<double> buffer2;
    std::string in_filename;
    std::string out_filename;
    bool auto_pair;
} ParamBox;
struct option_explanation
{
    std::string long_option_name;
    std::string short_option_name;
    std::string default_value;
    std::string option_information;
};
void usage();
void print_usage(const option_explanation *, int);
void process_param(int argc, char *argv[], ParamBox &);
rapidjson::Document file_to_document(std::string &);
void document_to_vector(rapidjson::Document &, const std::string &, std::vector<double> &);
void json_in(ParamBox &);
void json_out(std::string &jsonstr, std::string &out_filename);
void printTab(std::ofstream &, int);
#endif