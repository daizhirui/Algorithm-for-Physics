#include <iostream>
#include "Combination.h"
using namespace std;
int main()
{
    Combination comb(5, 3);
    vector<int> temp;
    while((temp=comb.pop()).size())
    {
        for(uint i=0;i<temp.size();i++)
            cout << temp[i] + 1 << ' ';
        cout << endl;
    }
    cout << "there are " << comb.count << " results" << endl;
    comb.restart();
    cout << "-----restart-----" << endl;
    while((temp=comb.pop()).size())
    {
        for(uint i=0;i<temp.size();i++)
            cout << temp[i] + 1 << ' ';
        cout << endl;
    }
    return 0;
}