#include"status.h"

int status::t=5;


int main(){
    srand(time(0));
    status one;
    FILE* fp=fopen("vary_t","w");
    fprintf(fp,"E=1,k=0.001\n");
    for(int tem=1000;tem<2000;tem+=200){
        status::setT(tem);
        int i,j;
        for(int ct=0;ct<50000000;ct++){
            i=rand()%100;
            j=rand()%100;
            one.go(i,j);
	    }
        long co=0;
	    for(int ct=50000000;ct<100000000;ct++){
            i=rand()%100;
            j=rand()%100;
            one.go(i,j);
            co+=one.sum;
		}
        fprintf(fp,"%d\t%.1f\n",tem,co*1.0/50000000);
    }
    for(int tem=2000;tem<3000;tem+=10){
        status::setT(tem);
        int i,j;
        for(int ct=0;ct<50000000;ct++){
            i=rand()%100;
            j=rand()%100;
            one.go(i,j);
	    }
        long co=0;
	    for(int ct=50000000;ct<100000000;ct++){
            i=rand()%100;
            j=rand()%100;
            one.go(i,j);
            co+=one.sum;
		}
        fprintf(fp,"%d\t%.1f\n",tem,co*1.0/50000000);
    }
    for(int tem=3000;tem<4000;tem+=200){
        status::setT(tem);
        int i,j;
        for(int ct=0;ct<50000000;ct++){
            i=rand()%100;
            j=rand()%100;
            one.go(i,j);
	    }
        long co=0;
	    for(int ct=50000000;ct<100000000;ct++){
            i=rand()%100;
            j=rand()%100;
            one.go(i,j);
            co+=one.sum;
		}
        fprintf(fp,"%d\t%.1f\n",tem,co*1.0/50000000);
    }
    fclose(fp);
    return(0);
}
