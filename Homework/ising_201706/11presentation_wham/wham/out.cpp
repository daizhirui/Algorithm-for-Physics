#include"histogram.h"
#include<iostream>
using namespace std;

void out(histogram* his,vector<double>* sc,vector<double>* vl){
    double E1=0,E2=0,E3=0;
    for(map<int,long double>::iterator it=his->outP.begin();it!=his->outP.end();it++){
        long Et2=(it->first)*(it->first);
        E1+=Et2*Et2*(it->second);
        E2+=Et2*(it->second);
        E3+=(it->first)*(it->second);
    }
    sc->push_back((his->K)*(his->K)*(E2-E3*E3)/his->L/his->L);
    vl->push_back(1-E1/3/E2/E2);
};

int main(){
    srand(time(NULL));
    histogram one;
    one.R.push_back(0);
    one.R.push_back(0.1);
    one.R.push_back(0.2);
    one.R.push_back(0.375);
    one.R.push_back(0.525);
    
    vector<double>* sc=new vector<double>;
    vector<double>* vl=new vector<double>;
    string outP,outsc,outvl;
    for(int L=4;L<17;L++){
        sc->clear();
        vl->clear();
        one.initial(L,500000,1000500000,1000);
        
        for(float k=0.1;k<0.8;k+=0.001){
            one.getP(k);
            char ps[30];
            sprintf(ps,"./data/%d/%dP%.3f",L,L,k);
            FILE* fp1=fopen(ps,"w");
            for(map<int,long double>::iterator it=one.outP.begin();it!=one.outP.end();it++){
                fprintf(fp1,"%d\t%Lf\n",it->first,it->second);
            }
            fclose(fp1);
 
            out(&one,sc,vl);
            char ssc[20];
            char svl[20];
            sprintf(ssc,"./data/%dsc",L);
            sprintf(svl,"./data/%dvl",L);
            FILE* fp2=fopen(ssc,"w");
            FILE* fp3=fopen(svl,"w");
            for(int i=0;i<(sc->size());i++){
                fprintf(fp2,"%f\n",(*sc)[i]);
                fprintf(fp3,"%f\n",(*vl)[i]);
            }
            fclose(fp2);
            fclose(fp3);
        }
    }
}
    
