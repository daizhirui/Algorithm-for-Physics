#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define     TEMPERATURE_BEGIN   0
#define     TEMPERATURE_STEP    0.001
#define     TEMPERATURE_NUM     10001

#define     SIZE                20
#define     DIRECTION           1
#define     J			        1

#define     SAMPLE_DISTANCE     100
#define     SAMPLE_NUM          50000

#define     STORE_DATATABLE     0

int steps=10000000;
int n=SIZE*SIZE;

int main(){
    double      temperature=0;
    int         Lattice[SIZE][SIZE]={0};
    int         row,column;
    double      randnum;
    int         i,j,k,flipcount;
    double      energy,deltaenergy,magnetic;
    int         p0,p1,p2,p3,p4,p5,p6;

    int         sample_begin=steps-SAMPLE_NUM*SAMPLE_DISTANCE;
    int         lastsample;
    double      sample[SAMPLE_NUM][2]={0};

    long double energy1[2]={0},energy2,magnetic1,magnetic2,permagnetic,heatCapacity,permeability,binderRatio,m2,m4,entropy=n*logl(2),freeenergy;

    FILE*       fp;
    char        filename[100];

    long        t1=time(NULL);

    srand((unsigned) t1);

    for(i=0;i<TEMPERATURE_NUM;i++){

        //calculate the temperature
        temperature=TEMPERATURE_BEGIN+i*TEMPERATURE_STEP;

        //open the file for DataTable
        if(STORE_DATATABLE){
            sprintf(filename, "./DataTable/DataTable Temperature=%lf.txt", temperature);
            fp = fopen(filename, "w");
            fprintf(fp, "energy\tmagnetic\tflipcount\tfliprow\tflipcolumn\n");
        }

        //initialize the Lattice Array
        for(j=0;j<SIZE;j++){
            for(k=0;k<SIZE;k++){
                Lattice[j][k]=DIRECTION;
            }
        }
        //initialize energy and magnetic
        energy=-2*n*J;
        magnetic=n*DIRECTION;

        //start simulation
        for(j=k=0,lastsample=sample_begin-SAMPLE_DISTANCE;j<steps;j++){

            row=(int)floor(rand()%SIZE);
            column=(int)floor(rand()%SIZE);

            p0 = Lattice[row][column];
            //p1 = Lattice[(row - 1 + SIZE) % SIZE][(column - 1 + SIZE) % SIZE];
            p2 = Lattice[(row - 1 + SIZE) % SIZE][column];
            p3 = Lattice[row][(column - 1 + SIZE) % SIZE];
            p4 = Lattice[row][(column + 1) % SIZE];
            p5 = Lattice[(row + 1) % SIZE][column];
            //p6 = Lattice[(row + 1) % SIZE][(column + 1) % SIZE];

            deltaenergy = 2 * (p2 + p3 + p4 + p5) * p0*J;
            //judge whether to flip
            if (deltaenergy <= 0) {
                Lattice[row][column] = -p0;
                energy += deltaenergy;
                magnetic -= 2*p0;
                flipcount++;
            }else {
                randnum = rand();
                if (randnum / RAND_MAX < expl(-deltaenergy * temperature)) {
                    Lattice[row][column] = -p0;
                    energy += deltaenergy;
                    magnetic -= 2 * p0;
                    flipcount++;
                }
            }
            if(STORE_DATATABLE){
                fprintf(fp,"%lf\t%lf\t%d\t%d\t%d\n",energy,magnetic,flipcount,row,column);
            }

            //sample
            if(j>=sample_begin&&(j-lastsample)>=SAMPLE_DISTANCE){
                sample[k][0]=energy;
                sample[k][1]=magnetic;
                k++;
                lastsample=j;
            }
        }
        //finish simulation
        printf("temperature=%lf\tsimulation completed\tpass %d s\n", temperature, (int) (time(NULL) - t1));
        
        if(STORE_DATATABLE){
            fclose(fp);    //DataTable output completed
            printf("DataTable saved\n");
        }

        //output Lattice
        sprintf(filename, "./Lattice/Lattice %d simulation, temp=%lf.txt", i+1, temperature);
        fp = fopen(filename, "w");
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < SIZE; k++) {
                fprintf(fp, "%d\t", Lattice[j][k]);
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
        printf("Lattice Status saved.\n");
        //output Lattice completed

        //output Sample
        sprintf(filename, "./Sample/Sample temperature=%lf.txt",temperature);
        fp=fopen(filename,"w");
        fprintf(fp,"Energy\tMagnetic\n");
        for(j=0;j<SAMPLE_NUM;j++){
            fprintf(fp,"%lf\t%lf\n",sample[j][0],sample[j][1]);
        }
        fclose(fp);
        printf("Sample saved\n");
        //output Sample completed

        //open the file for ThermalValue
        sprintf(filename,"./ThermalValue/ThermalValue SIZE=%d.txt",SIZE);
        fp=fopen(filename,"a+");
        if(i==0){
            fprintf(fp, "Temperature\tenergy1\tenergy2\tmagnetic1\tmagnetic2\tpermagnetic\theatCapacity\tpermeability\tbinderRatio\tentropy\tfreeenergy\n");
        }
        //initialize the thermal value
        energy1[1]=energy2=magnetic1=magnetic2=permagnetic=heatCapacity=permeability=binderRatio=m2=m4=0;
        //start to calculate
        for(j=0;j<SAMPLE_NUM;j++){
            energy1[1]+=sample[j][0];              //能量平均值
            energy2+=pow(sample[j][0],2);       //能量2次方平均值
            magnetic1+=sample[j][1];            //磁矩平均值
            magnetic2+=pow(sample[j][1],2);     //磁矩2次方平均值
            m4+=pow((sample[j][1])/n,4);        //单位磁矩4次方平均值
        }
        energy1[1]/=SAMPLE_NUM;
        energy2/=SAMPLE_NUM;
        magnetic1/=SAMPLE_NUM;
        magnetic2/=SAMPLE_NUM;
        permagnetic=magnetic1/n;                //单位磁矩
        m2=magnetic2/pow(n,2);                  //单位磁矩2次方平均值
        m4/=SAMPLE_NUM;

        heatCapacity=pow(temperature,2)*(energy2-pow((double)energy1[1],2));   //热容
        permeability=(temperature)*(magnetic2-pow((double)magnetic1,2));    //磁化率
        binderRatio=3/2*(1-m4/(3*pow((double)m2,2)));                       //宾德基能量
        entropy=entropy-energy1[0]*(temperature-TEMPERATURE_STEP)+energy1[1]*temperature-energy1[1]*TEMPERATURE_STEP;   //熵
		freeenergy=energy1[1]-temperature*entropy;
        energy1[0]=energy1[1];

        //output thermal values
        fprintf(fp,"%lf\t%Lf\t%Lf\t%Lf\t%Lf\t%Lf\t%Lf\t%Lf\t%Lf\t%Lf\t%Lf\n",temperature,energy1[1],energy2,magnetic1,magnetic2,
                permagnetic,heatCapacity,permeability,binderRatio,entropy, freeenergy);
        fclose(fp);
        printf("Thermal Value saved\tpass %d s\n\n", (int) (time(NULL) - t1));
    }
}
