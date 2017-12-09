#include"status.h"


status::status(){
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            s[i][j]=1;
        }
    }
    sum=10000;
};

float status::energy(int i,int j){
    int i1=i-1,i2=i+1,j1=j-1,j2=j+1;
    if(i==0) i1=99;
    else if(i==99) i2=0;
    if(j==0) j1=99;
    else if(j==99) j2=0;
    return(-(s[i1][j]+s[i2][j]+s[i][j1]+s[i][j2])*(s[i][j]));
};
float status::de(int i,int j){
    return(-2*(energy(i,j)));
};
void status::go(int i,int j){
    float k=0.001;
    float d=de(i,j);
    if(d<=0) flip(i,j);
    else if((rand()*1.0/RAND_MAX)<exp(-d/(k*t))) flip(i,j);
};

void status::flip(int i,int j){
	if(s[i][j]>0) sum=sum-2;
	else sum=sum+2;
	s[i][j]=-s[i][j];
};




