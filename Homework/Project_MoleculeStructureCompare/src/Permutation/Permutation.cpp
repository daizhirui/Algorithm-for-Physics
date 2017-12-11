#include <iostream>
#include <algorithm>
#include "Permutation.h"

#ifdef __linux__
#include <stdlib.h>
#endif

Permutation::Permutation(const int n, const int m)
{
    if(n<m)
    {
        std::cerr << "Permutation::Permutation(n,m): Illegal parameter, n should be greater than m" << std::endl;
        exit(-1);
    }
    this->n = n;
    this->m = m;
    count = 0;
    final = false;
    box.resize(n);
    per.resize(m);
    for(int i=0;i<n;i++)
        box[i]=i;
    for(int i=0;i<m;i++)
        per[i]=i;
}

std::vector<int> Permutation::pop()
{
    if(final)
    {
        per.resize(0);
        return per;
    }
    bool found = false;
    if(!count)
        found = true;
    while(!found)
    {
        int i;
        for(i=n-1;i>=0;i--)
            if(i && box[i-1]<box[i])    // new Complete Permutation
            {
                for(int j=n-1;j>=0;j--)
                    if(box[j]>box[i-1])
                    {
                        std::swap(box[i - 1], box[j]);
                        break;
                    }
                found = true;
                break;
            }
        std::vector<int>::iterator it = box.begin();
        if(i<0)
            i=0;
        it += i;
        std::reverse(it,box.end());
        if(found)
        {
            bool diff = false;
            for(i=0;i<m;i++)
                if(box[i]!=per[i])      // new target Permutation
                {
                    diff = true;
                    break;
                }
            if(diff)
            {
                for(i=0;i<m;i++)
                    per[i]=box[i];
                break;
            }
            else
                found = false;
        }
    }
    final = true;
    for(int i=0;i<m;i++)
        if(per[i]!=n-i-1)
            final = false;
    count++;
    return per;
}

void Permutation::restart()
{
    count = 0;
    final = false;
    per.resize(m);
    for(int i =0;i<m;i++)
        per[i]=i;
}