#include <string>
#include <map>
using namespace std;
class StrClass
{
    long        _feature;
    string      _str;
    static int  _tableInited;
    static      map<char, long> _featureTable;
    void initFeatureTable();
    long calculate_feature(const string&);
public:
    StrClass(const string&);
    ~StrClass();
    bool operator<(const StrClass&);
    long feature();
    string content();
};