#include"status.h"

status::status(int nL,float nK){
    L=nL;
    K=nK;
    sum=L*L;
    ener=-2*sum;
    for(int i=0;i<sum;i++){
        s.push_back(1);
    }
};

int status::de(int i,int j){
    int i1=i-1,i2=i+1,j1=j-1,j2=j+1;
    if(i==0) i1=(L-1);
    else if(i==(L-1)) i2=0;
    if(j==0) j1=(L-1);
    else if(j==(L-1)) j2=0;
    return(2*(s[i1*L+j]+s[i2*L+j]+s[i*L+j1]+s[i*L+j2])*(s[i*L+j]));
};

void status::go(int i,int j){
    float d=de(i,j);
    if(d<=0) {flip(i,j);ener+=d;}
    else if((rand()*1.0/RAND_MAX)<exp(-d*K)) {flip(i,j);ener+=d;}
};

void status::flip(int i,int j){
	if(s[i*L+j]>0) sum=sum-2;
	else sum=sum+2;
	s[i*L+j]=-s[i*L+j];
};




