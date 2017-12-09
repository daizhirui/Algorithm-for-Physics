#include"status.h"

int status::t=2500;

int main(){
    srand(time(NULL));
    status one;
    FILE* fp=fopen("const_t","w");
    fprintf(fp,"E=1,k=0.001,T=%d\n",status::t);
    
    int cc=0;
    int i,j;
    for(int ct=0;ct<5000000;ct++){
        i=rand()%100;
        j=rand()%100;
        one.go(i,j);
	}
    long co=0;
	for(int ct=5000000;ct<10000000;ct++){
        i=rand()%100;
        j=rand()%100;
        one.go(i,j);
        co+=one.sum;
        if(ct%100000==0){
			fprintf(fp,"%d\t%.1f\n",ct,co*1.0/(1+cc*100000));
			cc++;
        }
    }
    fclose(fp);
    return(0);
}
