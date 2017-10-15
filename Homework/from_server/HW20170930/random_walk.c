/* ------------------------------------------------------------
 * File name: random_walk.c
 * Author: Zhirui Dai (Astro)
 * Date created: 2017-09-30
 * Last modified: 2017-10-02
 * Description: The program is to simulate random walk and try to 
 *      find out the relation between time and the square of distance.
 * ------------------------------------------------------------ */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "../STATUS_CODE.h"
#include "../CONSTANT.h"

/* ------------------------------------------------------------
 * Function name: usage
 * Date modified: 2017-09-30
 * Description: To print the usage.
 * ------------------------------------------------------------ */
void usage()
{
    printf("Usage: random_walk [-n nStep] [-o file] [-r repeat] [-s save]\n");
    printf("\t-h\tPrint this usage.\n");
    printf("\t-n\tDefine the number of steps to simulate random walk, default 1000.\n");
    printf("\t-o\tDefine the file to store the data, default \"random_walk.dat\", uneffective when using [-s 0].\n");
    printf("\t-r\tDefine the number of the simulation, default 1.\n");
    printf("\t-s\tDefine the switch of saving every simulation, 0=not save, 1=save, default 1.\n");
}
/* ------------------------------------------------------------
 * Function name: process_param
 * Date modified: 2017-10-01
 * Description: To process the parameters before the simulation.
 * ------------------------------------------------------------ */
void process_param(int argc, char *argv[], int *nStep, char *filename, int *repeat, int *save)
{
    int opt; // To record the option input.
    while ((opt = getopt(argc, argv, ":n:o:r:s:h")) != -1)
    {
        switch (opt)
        {
        case 'h':
            usage();
            exit(STATUS_OK); // Use usage() to print the help.
        case 'n':
            *nStep = atoi(optarg);
            break; // Modified the nStep.
        case 'o':
            strcpy(filename, optarg);
            break; // Modified the filename to store.
        case 'r':
            *repeat = atoi(optarg);
            break; // Modified the time of repeating the simulation.
        case 's':
            *save = atoi(optarg);
            break; // Modified the switch of saving every simulation.
        // Option unavailable.
        case '?':
            printf("Error: option \'-%c\' is unavailable!\n", (char)optopt);
            usage();
            exit(STATUS_PARAM_ERROR);
        // Lack of parameters.
        case ':':
            printf("Error: option \'-%c\' requires a parameter!\n", (char)optopt);
            usage();
            exit(STATUS_PARAM_ERROR);
        }
    }
}
/* ------------------------------------------------------------
 * Function name: decide_to_move
 * Date modified: 2017-09-30
 * Description: To decide whether to move or not. 80% to move and
 *      20% not to do so.
 * ------------------------------------------------------------ */
int decide_to_move()
{
    if ((rand() % 10000) / 10000.0 < 0.8)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/* ------------------------------------------------------------
 * Function name: decide_steplen
 * Date modified: 2017-09-30
 * Description: To decide the length of the current step. 50% to
 *      move 1.0 and 50% to move 0.5.
 * ------------------------------------------------------------ */
double decide_steplen()
{
    if ((rand() % 10000) / 10000.0 < 0.5)
    {
        return 0.5;
    }
    else
    {
        return 1.0;
    }
}
/* ------------------------------------------------------------
 * Function name: decide_direction
 * Date modified: 2017-09-30
 * Description: To decide the direction to move down. The possibility
 *      of every direction is equal.
 * ------------------------------------------------------------ */
double decide_direction()
{
    //return (rand() % 10000) / 10000.0 * 2 * PI;   // Doesn't produce possibility equally!
    return rand() / (float) RAND_MAX * 2.0 * PI;
}
/* ------------------------------------------------------------
 * Function name: move
 * Date modified: 2017-09-30
 * Description: To execute the moving action.
 * ------------------------------------------------------------ */
void move(double *x, double *y, double *distance)
{
    double angle;               // To record the current direction.
    double steplen;             // To record the length of current step.
    angle = decide_direction(); // Decide the direction to move down
    steplen = decide_steplen(); // Decide how far to move
    *x += steplen * cos(angle);
    *y += steplen * sin(angle);
    *distance = sqrt((*x) * (*x) + (*y) * (*y));
}
/* ------------------------------------------------------------
 * Function name: store_result
 * Date modified: 2017-09-30
 * Description: To store the result.
 * ------------------------------------------------------------ */
void store_result(int step, double x, double y, double distance, FILE *file)
{
    fprintf(file, "%d\t%f\t%f\t%f\n", step + 1, x, y, distance);
    fflush(file);
}
/* ------------------------------------------------------------
 * Function name: cal_average
 * Date modified: 2017-10-02
 * Description: To calculate the average of distance.
 * ------------------------------------------------------------ */
void cal_average(int index, int count, double distance, double *ave_buffer)
{
    ave_buffer[count] = (ave_buffer[count] * index + distance * distance) / (index + 1);
}
/* ------------------------------------------------------------
 * Function name: main
 * Date modified: 2017-10-02
 * Description: This is the main function.
 * ------------------------------------------------------------ */
int main(int argc, char *argv[])
{
    // Process parameters: nStep, fileName, repeat
    int nStep = 1000;                                            //> Total step, default is 1000.
    char filename[100] = "simulation";                           //> To store the custom filename.
    char cur_filename[120] = "";                                 //> To store the current filename.
    FILE *file_dat = NULL;                                       //> File ptr, the default name is "random_walk.dat".
    FILE *file_ave = NULL;                                       //> File ptr, to store the average result of the square of distance.
    double *ave_buffer = NULL;                                   //> double ptr, to store the average result of the square of distance.
    int repeat = 1;                                              //> To record the number of simulations.
    int save = 1;                                                //> To record whether to save the simulation.
    process_param(argc, argv, &nStep, filename, &repeat, &save); //> Process parameters.

    // Value preparation.
    double x = 0;                      //> To record the current x coordinate.
    double y = 0;                      //> To record the current y coordinate.
    double distance = 0;               //> To record the current distance.
    int count;                         //> To record the current step.
    int index;                         //> To record the current simulation.
    srand((unsigned int)(time(NULL))); //> Initialize the seed.

    // IO preparation.
    if (save)
        system("mkdir -p data_random_walk"); //> create a directory to store the data files.
    if (repeat > 1)
    {
        ave_buffer = (double *)malloc(sizeof(double) * nStep); //> create a buffer to store the average.
        for (count = 0; count < nStep; count++)
            ave_buffer[count] = 0.0; //> Initialize the buffer.
    }

    // Start to simulate.
    for (index = 0; index < repeat; index++)
    {
        //> IO preparation.
        if (save)
        {
            sprintf(cur_filename, "./data_random_walk/%s - %d", filename, index + 1);              //>> Generate the filename.
            file_dat = fopen(cur_filename, "w+");                                                  //>> Create the file.
            fprintf(file_dat, "NO. %d of %d simulations, nStep= %d.\n", index + 1, repeat, nStep); //>> Print the parameters.
            fprintf(file_dat, "Step\t X  \t Y  \t DIST  \n");                                      //>> Create the head of the data sheet.
            fflush(file_dat);                                                                      //>> Write into the file.
        }
        //> Simulation.
        x = 0;
        y = 0;
        distance = 0; //>> Initialize x,y,distance.
        for (count = 0; count < nStep; count++)
        {
            if (save)
                store_result(count, x, y, distance, file_dat);   //>> Store the result
            if (repeat > 1)
                cal_average(index, count, distance, ave_buffer); //>> Calculate the average.
            if (decide_to_move())                                //>> Decide whether to move.
            {
                move(&x, &y, &distance);                         //>> To move.
            }
        }
        if (save)
            fclose(file_dat);
    }

    // Store the average.
    if (repeat > 1)
    {
        file_ave = fopen("ave_random_walk.dat", "w+");                   //> Create the file ptr.
        fprintf(file_ave, "%d simulations, %d steps.\n", repeat, nStep); //> Print the parameters.
        fprintf(file_ave, "Step\t DIST \n");                             //> Create the head of the data sheet.
        fflush(file_ave);                                                // Write into the file.
        for (count = 0; count < nStep; count++)
        {
            fprintf(file_ave, "%d\t%lf\n", count, ave_buffer[count]);
            fflush(file_ave);
        }
        fclose(file_ave);
    }
    free(ave_buffer);

    // Program ends.
    return STATUS_OK;
}