#include "Combination.h"
#include <iostream>
Combination::Combination(const int n, const int m)
{
    if(n<m)
    {
        std::cerr << "Combination::Combination(n,m): Illegal parameter, n should be greater than m" << std::endl;
        exit(-1);
    }
    this->n = n;
    this->m = m;
    count = 0;
    box.resize(n);
    for(int i=0;i<m;i++)
        box[i]=1;
    com.resize(m);
}

std::vector<int> Combination::pop()
{
    bool found = false;
    if(!count)
        found = true;
    else
        for(int i=0;i<this->n-1;i++)
            if(box[i] && !box[i+1])
            {
                std::swap(box[i], box[i+1]);
                tidy(i);
                found = true;
                break;
            }
    if(found)
    {
        int j = 0;
        for(int i=0;i<this->n;i++)
            if(box[i])
                com[j++] = i;
        count++;
    }
    else
        com.resize(0);
    return com;
}

void Combination::tidy(int i)
{
    for(int j=0;j<i;j++)
        if(!box[j])
            for(int k=j+1;k<i;k++)
                if(box[k])
                    std::swap(box[j],box[k]);
}

void Combination::restart()
{
    count = 0;
    int i = 0;
    for(i =0;i<m;i++)
        box[i]=1;
    for(;i<n;i++)
        box[i]=0;
    com.resize(m);
}