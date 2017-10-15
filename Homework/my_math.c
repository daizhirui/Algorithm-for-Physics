#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void my_srand(){
    srand((unsigned int)(time(NULL))); //> Initialize the seed.
}
double my_rand(double range){
    return rand()/(double)RAND_MAX*range;
}

double my_distance(double x, double y){
    return sqrt(x*x+y*y);
}