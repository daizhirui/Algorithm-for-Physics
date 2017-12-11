#include <cstdlib>
#include "pdbAnalyser.h"
bool pdbAnalyser(Atom &atom, const string &str)
{
    if(str.substr(0,4) == "ATOM")
    {
        const char * cstr = str.c_str();
        int i = 4;
        string arg="";
        while(cstr[i]==' ')
            i++;
        // atomNum
        while(cstr[i]!=' ')
            arg.push_back(cstr[i++]);
        atom.atomNum = atoi(arg.c_str());
        arg.clear();
        while(cstr[i]==' ')
            i++;
        // atomName
        while(cstr[i]!=' ')
            arg.push_back(cstr[i++]);
        atom.atomName = arg;
        arg.clear();
        while(cstr[i]==' ')
            i++;
        // groupName
        while(cstr[i]!=' ')
            arg.push_back(cstr[i++]);
        atom.groupName = arg;
        arg.clear();
        while(cstr[i]==' ')
            i++;
        // unknown
        while(cstr[i]!=' ')
            arg.push_back(cstr[i++]);
        string unknown = arg;
        arg.clear();
        while(cstr[i]==' ')
            i++;
        // groupNum
        while(cstr[i]!=' ')
            arg.push_back(cstr[i++]);
        atom.groupNum = atoi(arg.c_str());
        arg.clear();
        // position of atom
        MyVector temp_pos;
        for(int j=0;j<3;j++)
        {
            while(cstr[i]==' ')
                i++;
            while(cstr[i]!=' ')
                arg.push_back(cstr[i++]);
            temp_pos[j] = atof(arg.c_str());
            arg.clear();
        }
        atom.position = temp_pos;
        // unknown
        while(cstr[i]==' ')
            i++;
        while(cstr[i]!=' ')
            arg.push_back(cstr[i++]);
        arg.clear();
        // unknown
        while(cstr[i]==' ')
            i++;
        while(cstr[i]!=' ')
            arg.push_back(cstr[i++]);
        arg.clear();
        while(cstr[i]==' ')
            i++;
        // atomType
        atom.atomType = str[i];

        return true;
    }
    else
        return false;
}