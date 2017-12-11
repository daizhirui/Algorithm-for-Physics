#include <map>
#include <string>
#include <vector>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace std;
class StrMap
{
    map< long, map< string, int > > _map;
    static map<char, long> _featureTable;
    static int  _tableInited;
    static long  _count;
    void initFeatureTable();
    long calculate_feature(const string&);
    void printTab(ofstream&, int);
    void JsonStyleWrite(ofstream&, string&);
public:
    StrMap();
    ~StrMap();
    void add(const string&);
    vector<long> all_features() const;
    long featureType_num() const;
    long stringType_num() const;
    long stringCount(long);
    long stringNum() const;
    map< string, int > operator[](const long&);
    void printJSONResult(const string&);
    void printTXTResult(const string&);
};
