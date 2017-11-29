#include <iostream>
#include <map>
#include <string>
using namespace std;
int main()
{
    map<string, int> box;
    box["ABCDEFG"]++;
    box["ABCDEFG"]++;
    cout << box["ABCDEFG"] << endl;
    return 0;
}
