#include <iostream>
#include "StrClass.h"
int StrClass::_tableInited = 0;
map<char, long> StrClass::_featureTable;
void StrClass::initFeatureTable()
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

long StrClass::calculate_feature(const string &v)
{
    long result = 0;
    for (int i = 0; i < v.size(); i++)
    {
        result |= _featureTable[v[i]];
    }
    return result;
}

StrClass::StrClass(const string& v)
{
    initFeatureTable();
    _str = v;
    _feature = calculate_feature(_str);
}

bool StrClass::operator<(const StrClass& v)
{
    if(_feature < v._feature)
        return true;
    else
        return false;
}

StrClass::~StrClass(){}

long StrClass::feature()
{
    return _feature;
}

string StrClass::content()
{
    return _str;
}
