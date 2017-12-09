#ifndef STATUS_H
#define STATUS_H

#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

struct status{
    static int t;
    int s[100][100];
    int sum;

    status();

    static void setT(int nt){t=nt;};

    float energy(int,int);
    float de(int,int);
    void go(int,int);
    void flip(int,int);
};

#endif
