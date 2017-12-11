#include <iostream>
#include "Permutation.h"
using namespace std;
int main()
{
    Permutation perm(3, 3);
    vector<int> temp;
    while ((temp = perm.pop()).size())
    {
        for (uint i = 0; i < temp.size(); i++)
            cout << temp[i] + 1 << ' ';
        cout << endl;
    }
    cout << "there are " << perm.count << " results" << endl;
    perm.restart();
    cout << "-----restart-----" << endl;
    while ((temp = perm.pop()).size())
    {
        for (uint i = 0; i < temp.size(); i++)
            cout << temp[i] + 1 << ' ';
        cout << endl;
    }
    return 0;
}