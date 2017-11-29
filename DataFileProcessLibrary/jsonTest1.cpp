#include <fstream>
#include <string>
#include <cassert>
#include <iostream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#define psln(x) std::cout << #x " = " << (x) << std::endl
using namespace rapidjson;
using namespace std;
void JsonStyleWrite(ofstream& ofs, string& str);

void testSimpleDoc() {
    using std::string;
    using std::ifstream;
    using std::ofstream;

    // read json content into string.
    string      stringFromStream;
    ifstream    in;
    in.open("test.json", ifstream::in);
    if (!in.is_open())
        return;
    string line;
    while (getline(in, line)) {
        stringFromStream.append(line + "\n");
    }
    in.close();

    // ---------------------------- read json --------------------
    // parse json from string.
    using rapidjson::Document;
    Document doc;
    doc.Parse<0>(stringFromStream.c_str());
    if (doc.HasParseError()) {
        rapidjson::ParseErrorCode code = doc.GetParseError();
        psln(code);
        return;
    }

    // use values in parse result.
    using rapidjson::Value;
    Value & v = doc["dictVersion"];
    if (v.IsInt()) {
        psln(v.GetInt());
    }

    Value & contents = doc["content"];
    if (contents.IsArray()) {
        for (size_t i = 0; i < contents.Size(); ++i) {
            Value & v = contents[i];
            assert(v.IsObject());
            if (v.HasMember("key") && v["key"].IsString()) {
                psln(v["key"].GetString());
            }
            if (v.HasMember("value") && v["value"].IsString()) {
                psln(v["value"].GetString());
            }
        }
    }
    // ---------------------------- write json --------------------
    psln("add a value into array");

    Value item(Type::kObjectType);
    item.AddMember("key", "word6", doc.GetAllocator());
    item.AddMember("value", "单词6", doc.GetAllocator());
    contents.PushBack(item, doc.GetAllocator());

    // convert dom to string.
    StringBuffer buffer;      // in rapidjson/stringbuffer.h
    Writer<StringBuffer> writer(buffer); // in rapidjson/writer.h
    doc.Accept(writer);
    
    psln(buffer.GetString());

    ofstream ofs;
    ofs.open("new_test.json", ofstream::out);
    string str = buffer.GetString();
    JsonStyleWrite(ofs, str);
    ofs.close();
}

void printTab(ofstream& ofs, int i)
{
    for(int j=0;j<i;j++)
        ofs << '\t';
}

void JsonStyleWrite(ofstream& ofs, string& str)
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

int main()
{
    testSimpleDoc();
    return 0;
}