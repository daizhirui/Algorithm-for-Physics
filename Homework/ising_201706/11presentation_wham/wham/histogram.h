#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include"status.h"
#include<map>


using namespace std;

struct histogram{
    
    int L;
    vector<float> R;
    map<int,int> N;
    map<int,long double> outP;
    float K;
    
    void judge(int E);
    void getP(float outK);
    void initial(int l,int begin,int end,int step);
    
};

#endif
