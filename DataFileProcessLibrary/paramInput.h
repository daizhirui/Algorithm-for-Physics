#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
union paramBox
{
    int     intValue;           // for int type
    int*    intPtr1D;           // for int 1D_array
    unsigned int    uintValue;  // for unsigned int type
    unsigned int*   uintPtr1D;  // for unsigned int 1D_array
    long    longValue;          // for long type
    long*   longPtr;            // for long 1D_array
    unsigned long   ulongValue; // for unsigned long type
    unsigned long*  ulongPtr;   // for unsigned long 1D_array
    float   floatValue;         // for float type
    float*  floatPtr;           // for float 1D_array
    double  doubleValue;        // for double type
    double* doublePtr;          // for double 1D_array
    char    charValue;          // for char type    
    char*   charPtr;            // for char 1D_array
    string* stringPtr;          // for string pointer
};

// paramData.json   ->  Get the parameters' values, each item should have member "type","value"; "comment" is optional.

class ParamInput
{
    map<string, paramBox>   _paramMap;  // the map of the parameters
    string                  _filename;  // the name of the json file
    ifstream                _ifs;       // open the json file
    vector<string>          _paramName; // the name of every parameter to get in
    int checkType();
    paramBox getValue();

public:
    ParamInput(const string&, const vector<string>&);
    paramBox& operator[](const string&);
};
enum type
{
    int,
    float,
    double,
    string
};
Document::AllocatorType allocator;
                jKey.CopyFrom(itr->name, allocator);
                jValue.CopyFrom(itr->value,allocator);
               if (jKey.IsString())
               {
                       string name = jKey.GetString();
                       printf("\r\nname: %s\r\n",name.c_str());
               } 