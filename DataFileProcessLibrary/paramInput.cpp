#include "paramInput.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#define psln(x) cout << #x " = " << (x) << endl
ParamInput::ParamInput(const string& filename, const vector<string>& paramName)
{
    // member variable initilization
    _filename = filename;
    _paramName = paramName;
    // open the json file
    _ifs.open(_filename, ios::in);
    if(!_ifs.is_open())
    {
        cout << _filename << " does not exist!" << endl;
        exit(-1);
    }
    // dump file content to string buffer
    string  stringFromStream;
    string  line;
    while(getline(_ifs, line))
        stringFromStream.append(line);
    _ifs.close();   // close json file
    // parse json from string and check if there is error
    using rapidjson::Document;
    Document    doc;
    doc.Parse<0>(stringFromStream.c_str());
    if(doc.HasParseError())
    {
        rapidjson::ParseErrorCode code = doc.GetParseError();
        psln(code);
        exit(-1);
    }
    // check if all the parameters required are provided
    // check if every parameter's value has member "type", "value"
    Value key;
    Value value;
    for(rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); itr++)
    {
        Document::AllocatorType allocator;
        key.CopyFrom(itr->name, allocator);
        if(key.IsString())
        {
            string name = key.GetString();
            _paramMap[name]
        }
        else
        {
            key.GetType();
        }
    }
    
}