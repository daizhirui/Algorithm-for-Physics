#include "StrBox.h"

StrBox::StrBox(const string &v)
{
    _feature = 0;
    _box.insert(pair<string, int>(v, 1));
    initFeatureTable();
    _count++;
}

StrBox::~StrBox()
{
    _count--;
}

void StrBox::append(const string &v)
{
    if (_feature == calculate_feature(v))
        _box[v]++;
}


bool StrBox::operator<(const StrBox& v)
{
    if(_feature < v._feature) return true;
    return ;
}