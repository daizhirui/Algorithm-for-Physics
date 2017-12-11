# MyString

## History
- 2017-10-27
    - first release, complete **operator+、+=**
- 2017-11-20
    - add **assign**, **c_str** and **compare**
    - **Use "make" to compile and test MyString automatically!**
- 2017-11-23
    - add **length** and **operator[]**
- 2017-11-24
    - **fix a bug** of **operator=(const MyString& v)**, avoid losing the content when equal to self
    - update makefile to a better style
        - use "make" to compile a test program: testMyString
        - use "make test" to run a test
## Member Functions

### Construct functions

```cpp
MyString::MyString();
MyString::MyString(char v);
MyString::MyString(const char* v);
MyString::MyString(const MyString& v);
MyString::MyString(string v);
```

### Deconstruct function
```cpp
MyString::~MyString();
```

### Element access

```cpp
char* MyString::c_str();
```

### Operators

```cpp
void MyString::operator=(char v);
void MyString::operator=(const char* v);
void MyString::operator=(const MyString& v);
void MyString::operator=(string v);

MyString MyString::operator+(char v);
MyString MyString::operator+(const char* v);
MyString MyString::operator+(const MyString& v);
MyString MyString::operator+(string v);
friend MyString operator+(char, MyString&);
friend MyString operator+(const char*, MyString&);
friend MyString operator+(string, MyString&);

MyString operator+=(char);
MyString operator+=(const char*);
MyString operator+=(const MyString&);
char operator[](unsigned int i);

friend ostream& operator<<(ostream&, MyString&);
```

### STL Functions
The following functions have been achieved according to STL.
```cpp
int MyString::count(char);
int MyString::count(const char *);
int MyString::length();

MyString MyString::assign(int, char);
MyString MyString::assign(int, const char*);
MyString MyString::assign(int, MyString&);
MyString MyString::assign(int, string);

int MyString::compare(const char*);
int MyString::compare(MyString&);
int MyString::compare(string);
```

