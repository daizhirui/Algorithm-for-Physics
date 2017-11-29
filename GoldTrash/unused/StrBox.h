#include <map>
#include <string>
using namespace std;
class StrBox
{
    long _feature;          // a number indicates the feature of string
    map<string, int> _box;  // store all strings having the same characters
public:
    StrBox(const string&);
    ~StrBox();

    void append(const string&);

    static long calculate_feature(const string&);

    bool operator<(const StrBox&);
    
};
