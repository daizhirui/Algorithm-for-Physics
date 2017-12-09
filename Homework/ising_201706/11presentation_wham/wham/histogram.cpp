#include"histogram.h"

void histogram::judge(int E){
    if(N.find(E)==N.end()) N[E]=1;
    else N[E]++;
};

void histogram::getP(float outK){
    K=outK;
    for(map<int,int>::iterator it=N.begin();it!=N.end();it++){
        long double sig=0;
        for(int j=0;j<R.size();j++){
            sig+=exp(-(it->first)*R[j]);
        }
        outP[it->first]=(it->second)*exp(-(it->first)*outK)/(sig);
    }
    long double sig=0;
    for(map<int,long double>::iterator it=outP.begin();it!=outP.end();it++){
        sig+=it->second;
    }
    for(map<int,long double>::iterator it=outP.begin();it!=outP.end();it++){
        it->second=(it->second)/sig;
    }
};



void histogram::initial(int l,int begin,int end, int step){
    L=l;
    N.clear();
    outP.clear();
    status* mont;
    for(int i=0;i<R.size();i++){
        mont=new status(l,R[i]);
        int m;
        int n;
        for(int ct=0;ct<begin;ct++){
            m=rand()%(mont->L);
            n=rand()%(mont->L);
            mont->go(m,n);
        }
        for(int ct=begin;ct<end;ct++){
            m=rand()%(mont->L);
            n=rand()%(mont->L);
            mont->go(m,n);
            if(ct%step==0){
                judge(mont->ener);
            }
        }
        delete mont;
    }
};

    
    
    
    
    
