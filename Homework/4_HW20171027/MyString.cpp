#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

struct MyString
{

    char *pstr;

    // construct function
    MyString();
    MyString(char);
    MyString(const char *);
    MyString(const MyString &);
    MyString(string);
    ~MyString(); // deconstruct function

    // return the number of elements satisfying the specific char
    int count(char);
    int count(const char *);

    // return the length of the string
    int length();

    // define a series of operators
    // =
    void operator=(char);
    void operator=(const char *);
    void operator=(const MyString &);
    void operator=(string);
    // +
    MyString operator+(char);
    MyString operator+(const char *);
    MyString operator+(const MyString &);
    MyString operator+(string);
    friend MyString operator+(char, const MyString &);
    friend MyString operator+(const char *, const MyString &);
    friend MyString operator+(string, const MyString&);
    // +=
    MyString operator+=(char);
    MyString operator+=(const char *);
    MyString operator+=(const MyString &);

    friend ostream &operator<<(ostream &, MyString &);

    char operator[](unsigned int);

    MyString assign(int, char);
    MyString assign(int, const char *);
    MyString assign(int, MyString &);
    MyString assign(int, string);

    char *c_str();

    int compare(const char *);
    int compare(MyString &);
    int compare(string);
};

MyString::MyString()
{
    char *pTmp = (char *)malloc(1);
    // check alloc memory success
    if (pTmp == NULL)
    { // failure
        cout << "Alloc memory failure" << endl;
        exit(1);
    }
    else
    {                   // success
        pTmp[0] = '\0'; // initialize MyString
        pstr = pTmp;
    }
}

MyString::MyString(char v)
{
    pstr = NULL;
    *this = v; // use the definition of =
}

MyString::MyString(const char *v)
{
    pstr = NULL;
    *this = v; // use the definition of =
}

MyString::MyString(const MyString &v)
{
    pstr = NULL;
    *this = v; // use the definition of =
}

MyString::MyString(string v)
{
    pstr = NULL;
    *this = v.c_str();
}

MyString::~MyString()
{
    free(pstr);
}

int MyString::count(char v)
{
    int n = 0;
    for (unsigned int i = 0; i < strlen(pstr); ++i)
    {
        if (pstr[i] == v)
            ++n;
    }
    return n;
}

int MyString::count(const char *v)
{
    int n = 0;
    for (unsigned int i = 0; i < strlen(v); ++i)
    {
        n += count(v[i]);
    }
    return n;
}

int MyString::length()
{
    return strlen(pstr);
}

void MyString::operator=(const char *v)
{
    char *pTmp = (char *)realloc(pstr, strlen(v) + 1);
    if (pTmp == NULL)
    {
        cout << "Alloc memory failure" << endl;
        exit(1);
    }
    else
    {
        strcpy(pTmp, v);
        pstr = pTmp;
    }
}

void MyString::operator=(char v)
{
    char s[2] = {v, '\0'};
    *this = s; // use the definition of =
}

void MyString::operator=(const MyString &v)
{   
    if(this == &v)  return; // avoid equal to self.
    *this = v.pstr; // use the definition of =
}

void MyString::operator=(string v)
{
    *this = v.c_str();
}

MyString MyString::operator+(const char *v)
{
    char *new_pstr = (char *)malloc(strlen(pstr) + strlen(v) + 1);
    if (new_pstr == NULL)
    {
        cout << "Alloc memory failure" << endl;
        exit(1);
    }
    else
    {
        strcpy(new_pstr, pstr);
        strcat(new_pstr, v);
        MyString str = MyString(new_pstr);
        free(new_pstr);
        return str;
    }
}

MyString MyString::operator+(char v)
{
    char s[2] = {v, '\0'};
    MyString str = *this + s;
    return str;
}

MyString MyString::operator+(const MyString &v)
{
    MyString str = *this + v.pstr;
    return str;
}

MyString MyString::operator+(string v)
{
    MyString str = *this + v.c_str();
    return str;
}

MyString operator+(char v, const MyString &str0)
{
    MyString str = MyString(v);
    str = str + str0;
    return str;
}

MyString operator+(const char *v, const MyString &str0)
{
    MyString str = MyString(v);
    str = str + str0;
    return str;
}

MyString operator+(string v, const MyString& str0){
    MyString str = MyString(v);
    str = str + str0;
    return str;
}

MyString MyString::operator+=(const char *v)
{
    char *new_pstr = (char *)malloc(strlen(pstr) + strlen(v) + 1);
    if (new_pstr == NULL)
    {
        cout << "Alloc memory failure" << endl;
        exit(1);
    }
    else
    {
        strcpy(new_pstr, pstr);
        strcat(new_pstr, v);
    }
    free(pstr);
    pstr = new_pstr; // new_pstr should not be fred!
    return *this;
}

MyString MyString::operator+=(char v)
{
    char s[2] = {v, '\0'};
    *this += s;
    return *this;
}

MyString MyString::operator+=(const MyString &v)
{
    *this += v.pstr;
    return *this;
}

ostream &operator<<(ostream &os, MyString &v)
{
    os << v.pstr;
    return os;
}

char MyString::operator[](unsigned int i)
{
    if (i >= strlen(pstr))
    {
        cerr << "Error(Subscript out of bound)\n";
        exit(-1);
    }
    return pstr[i];
}

MyString MyString::assign(int count, char v)
{
    if (count)
    {
        *this = v;
        for (int i = 0; i < count - 1; i++)
        {
            *this += v;
        }
    }
    else
    {
        *this = "";
    }
    return *this;
}

MyString MyString::assign(int count, const char *v)
{
    if (count)
    {
        *this = v;
        for (int i = 0; i < count - 1; i++)
        {
            *this += v;
        }
    }
    else
    {
        *this = "";
    }
    return *this;
}

MyString MyString::assign(int count, MyString &v)
{
    this->assign(count, v.pstr);
    return *this;
}

MyString MyString::assign(int count, string v)
{
    this->assign(count, v.c_str());
    return *this;
}

char *MyString::c_str()
{
    return pstr;
}

int MyString::compare(const char *v)
{
    char *pTmp = pstr;
    int i = 0;
    while (pTmp[i] && pTmp[i] == v[i])
    {
        i++;
    }
    return pTmp[i] - v[i];
}

int MyString::compare(MyString &v)
{
    return this->compare(v.pstr);
}

int MyString::compare(string v)
{
    return this->compare(v.c_str());
}

int main()
{
    MyString str1 = MyString();
    cout << "str1: Test MyString() and operator<<" << endl;
    cout << str1 << endl;
    MyString str2 = MyString('2');
    cout << "str2: Test MyString(char) and operator<<" << endl;
    cout << str2 << endl << endl;

    MyString str3 = MyString("I'm str3");
    cout << "str3: Test MyString(char*) and operator<<" << endl;
    cout << str3 << endl << endl;

    str1 = "I'm str1";
    MyString str4 = MyString(str1);
    cout << "str4: Test MyString(MyString&) operator= and operator<<" << endl;
    cout << str4 << endl << endl;

    string str = "This is a string";
    cout << "str5: Test MyString(string) operator= and operator<<" << endl;
    MyString str5 = MyString(str);
    cout << "string str: " << str << endl;
    cout << str5 << endl << endl;

    str1 = str2 + str3;
    cout << "Test: str1 = str2 + str3" << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;
    cout << str1 << endl << endl;

    str1 = '1' + str1;
    cout << "Test: str1 = '1' + str1" << endl;
    cout << str1 << endl << endl;

    str1 = "Hello " + str3;
    cout << "Test: str1 = \"Hello \" + str3" << endl;
    cout << str1 << endl << endl;

    str1 = str1 + 'A';
    cout << "Test: str1 = str1 + 'A'" << endl;
    cout << str1 << endl << endl;

    str1 = str1 + "Goodbye";
    cout << "Test: str1 = str1 + \"Goodbye\"" << endl;
    cout << str1 << endl << endl;

    str1 += str3;
    cout << "Test: str1 += str3" << endl;
    cout << str1 << endl << endl;

    str1 += 'A';
    cout << "Test: str1 += 'A'" << endl;
    cout << str1 << endl << endl;

    str1 += "Nice to meet you";
    cout << "Test: str1 += \"Nice to meet you\"" << endl;
    cout << str1 << endl << endl;

    str3 = '3';
    cout << "Test: str3 = '3'" << endl;
    cout << str3 << endl << endl;

    str3 = str2;
    cout << "Test: str3 = str2" << endl;
    cout << str3 << endl << endl;

    cout << "Test: str1.count('I')" << endl;
    cout << "There are " << str1.count('I') << " 'I' in \"" << str1 << "\"" << endl << endl;

    cout << "Test: str1.count(\"Im\")" << endl;
    cout << "There are " << str1.count("Im") << " 'I' or 'm' in \"" << str1 << "\"" << endl << endl;

    cout << "Test: str1.c_str()" << endl;
    cout << str1.c_str() << endl << endl;

    cout << "Test: str1.assign(4, '=')" << endl;
    str1.assign(4, '=');
    cout << str1 << endl << endl;

    cout << "Test: str1.assign(4, \"Hello World\")" << endl;
    str1.assign(4, "Hello World");
    cout << str1 << endl << endl;

    cout << "Test: str1.assign(4, str2)" << endl;
    cout << "str2: " << str2 << endl;
    str1.assign(4, str2);
    cout << str1 << endl << endl;

    cout << "Test: str1.assign(4, str)" << endl;
    cout << "str: " << str << endl;
    str1.assign(4, str);
    cout << str1 << endl << endl;

    cout << "Test: str1.compare(\"Hello World\")" << endl;
    str1 = "Hello World";
    cout << "str1: " << str1 << endl;
    cout << str1.compare("Hello World") << endl << endl;

    cout << "Test: str1.compare(str2)" << endl;
    str2 = "Hello World!";
    cout << "str2: " << str2 << endl;
    cout << "ASCII(!) = " << (int)'!' << endl;
    cout << str1.compare(str2) << endl
         << endl;

    str = "Hello";
    cout << "Test: str1.compare(str)" << endl;
    cout << "str: " << str << endl;
    cout << "ASCII(' ') = " << (int)' ' << endl;
    cout << str1.compare(str) << endl << endl;
    
    cout << "Test: str1.length()" << endl;
    cout << "str1: " << str1 << endl;
    cout << "The length of str1: " << str1.length() << endl << endl;
    
    cout << "Test: operator[]" << endl;
    for(int i = 0; i < str1.length(); i++)
    {
        cout << i << ": " << str1[i] << endl;
    }
    cout << endl;

    cout << "Test: str1 = str1" << endl;
    str1 = str1;
    cout << "str1(after str1 = str1): " << str1 << endl;
    cout << "******** Test Completed, All pass ********" << endl;
}
