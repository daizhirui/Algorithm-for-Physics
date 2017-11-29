#include <iostream>
#include <list>
using namespace std;
int main()
{
    list<int> intList;
    for(int i=0;i<10;i++)
        intList.push_back(i);
    for(int i:intList)
        cout << i << endl;
    return 0;
}