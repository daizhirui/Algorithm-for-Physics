#include <string>
#include <iostream>
using namespace std;
int main()
{
    string str1("ABAD");
    string str2("ABC");
    cout << (int)(str1 < str2) << endl;
    cout << str1.compare(str2) << endl;
    return 0;
}