#include <fstream>
#include <iostream>
#include "StrMap.h"

int StrMap::_tableInited = 0;
long StrMap::_count = 0;
map<char, long> StrMap::_featureTable;
// initilize the _featureTable,
// this table stores the feature value of all the characters
void StrMap::initFeatureTable()
{
    if (!_tableInited)
    {
        int i;
        char c;
        for (i = 0, c = 'A'; i < 26; i++, c++)
            _featureTable[c] = (long)1<<i;
        for (i = 26, c = 'a'; i < 52; i++, c++)
            _featureTable[c] = (long)1<<i;
        _tableInited = 1;
    }
}
// calculate the feature value of the string
long StrMap::calculate_feature(const string &v)
{
    long result = 0;
    for (int i = 0; i < (int)v.size(); i++)
    {
        result |= _featureTable[v[i]];
    }
    return result;
}
// for JsonStyleWrite, control the tab
void StrMap::printTab(ofstream& ofs, int i)
{
    for(int j=0;j<i;j++)
        ofs << '\t';
}
// output the json string as a json file
void StrMap::JsonStyleWrite(ofstream& ofs, string& str)
{
    int tabNum = 0;
    for(auto n:str)
    {
        if(n=='{'||n==','||n=='[')
        {
            ofs << n << '\n';
            if(n!=',')
                tabNum++;
            printTab(ofs, tabNum);
        }
        else
        {
            if(n=='}'||n==']')
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

StrMap::StrMap()
{
    initFeatureTable();
    _map.clear();
}

StrMap::~StrMap(){}
// add a new string to _map
// calculate the feature value of the string
// and update the statistics
void StrMap::add(const string& v)
{
    long feature = calculate_feature(v);
    _map[feature][v]++;
    _count++;
}
// return all feature values in _map
vector<long> StrMap::all_features() const
{
    vector<long> result;
    result.clear();
    for(auto it:_map)
        if(it.first)
            result.push_back(it.first);
    return result;
}

long StrMap::featureType_num() const
{
    return _map.size()-1;
}
// return the number of strings of the same feature value
long StrMap::stringType_num() const
{
    long result = 0;
    for(auto i:_map)
    {   // i is <long, <string, int> >
        result += i.second.size();
    }
    return result;
}

long StrMap::stringCount(long v)
{
    long result = 0;
    for(auto i:_map[v])
    {   // i is <string, int>
        result += i.second;
    }
    return result;
}

long StrMap::stringNum() const
{
    return _count-1;
}
// return a string box about the specific feature value
// this box is a map
map< string, int > StrMap::operator[](const long& v)
{
    return _map[v];
}
// convert the result to json string and write in a file automatically
void StrMap::printJSONResult(const string& filename)
{
    // create a json document object
    rapidjson::Document doc;
    doc.SetObject();
    // create the iterator of _map
    auto it = _map.begin();
    it++;   // the key of the first item of _map is 0, discard it.
    // create a buffer to convert long number to 
    char buffer[8];

    // ****** start to convert ******
    // using rapidjson to convert
    for(; it != _map.end(); it++)
    {
        // convert feature value to string
        int len = sprintf(buffer,"%ld",it->first);
        rapidjson::Value value; // to store string-count pair
        rapidjson::Value s;     // to store feature value as a string
        value.SetObject();
        // If we need the total number of every feature value, cancle the following 3 comment
        //s.SetString("total", 5, doc.GetAllocator());
        //int count = (int)stringCount(it->first);
        //value.AddMember(s,count,doc.GetAllocator());
        for(auto n:it->second)
        {
            s.SetString(n.first.c_str(),n.first.size(),doc.GetAllocator());
            value.AddMember(s,n.second,doc.GetAllocator());
        }
        s.SetString(buffer, len, doc.GetAllocator());
        doc.AddMember(s,value,doc.GetAllocator());
    }
    // store the content into a stringBuffer
    // doc >> writer >> jsonbuffer
    rapidjson::StringBuffer jsonbuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(jsonbuffer);
    doc.Accept(writer);
    // ****** start to output to a file ******
    ofstream ofs;
    ofs.open(filename, ios::out);
    string str = jsonbuffer.GetString();
    JsonStyleWrite(ofs, str);
    ofs.close();
}

void StrMap::printTXTResult(const string& filename)
{
    auto it = _map.begin();
    it++;
    ofstream ofs;
    ofs.open(filename, ios::out);
    if(!ofs.is_open())
    {
        cout << "faile tp create file!" << endl;
        exit(-1);
    }
    ofs << stringNum() << " strings are read in." << endl;
    ofs << "There are " << featureType_num() << " kinds of string counting by the **feature**" << endl;
    ofs << "There are " << stringType_num() << " kinds of string counting by the **content**" << endl;
    ofs << "\nThe following shows the result, which is also in the JSON file:" << endl;
    for(; it!=_map.end(); it++)
    {
        ofs << it->first << ':' << stringCount(it->first) << endl;
        map<string, int>& box = it->second;
        for(auto n:box)
        {
            ofs << '\t' << n.first << ": " << n.second << endl;
        }
    }
    ofs.close();
};

