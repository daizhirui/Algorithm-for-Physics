/* ------------------------------------------------------------
 * File name: monte_carlo_walk.c
 * Author: Zhirui Dai (Astro)
 * Date created: 2017-10-14
 * Last modified: 2017-10-15
 * Description: The program is to simulate Monte Carlo Walk and try to 
 *      find out the relation between the number of Monte Carlo Steps
 *      and the statistical result.
 * ------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "STATUS_CODE.h"
#include "CONSTANT.h"

#define STABLE_STATE 1
#define EXCITED_STATE 0

/**
 * @brief 
 * 
 * To print the usage.
 * 
 */
void usage()
{
    printf("Usage: monte_carlo_walk\n");
    printf("\t-h\tPrint this usage.\n");
    printf("\t-l\tTo setup the length of the simulation, default 0.5\n");
    printf("\t-n\tTo setup the length of the simulation, default 1000\n");
    printf("\t-o\tTo setup the name of the output file, ineffective when using [-s 0], default monte_carlo_data.dat\n");
    printf("\t-O\tTo setup the name of the file containing the possibility of stable state, default possibility_stable_state.dat\n");
    printf("\t-s\tTo setup whether to save the original data of the simulation, 0=Not save, 1=save, default 1\n");
}
/**
 * @brief 
 * 
 * To process the parameters before the simulation.
 * 
 * @param argc      The number of parameters posted.
 * @param argv      The buffer storing the parameters posted.
 * @param nStep     The pointer to nStep, which stores the total Monte Carlo Steps.
 * @param stepLen   The pointer to stepLen, which stores the length of single step.
 * @param repeat    The pointer to repeat, which stores the time to repeat the simulation.
 * @param possFile  The pointer to possFile, which stores the filename of file_poss and file_poss_all.
 * @param dataFile  The pointer to dataFile, which stores the filename of file_data.
 * @param save      The pointer to save, which stores the switch of data saving.
 */
void process_param(int argc, char *argv[],                                 // Option parameters.
                   int *nStep, double *stepLen, double *temperature,       // Simulation parameters.
                   int *repeat, char *possFile, char *dataFile, int *save) // IO parameters.
{
    int opt; // To read the option input.
    while ((opt = getopt(argc, argv, ":l:n:o:O:r:s:T:h")) != -1)
    {
        switch (opt)
        {
        case 'h':
            usage();
            exit(STATUS_OK); // Use usage() to print the help.
        case 'l':
            *stepLen = atof(optarg);
            break; // Modified the length of single step.
        case 'n':
            *nStep = atoi(optarg);
            break; // Modified the nStep.
        case 'o':
            strcpy(dataFile, optarg);
            break; // Modified the filename to store.
        case 'O':
            strcpy(possFile, optarg);
            break; // Modified the filename to store.
        case 'r':
            *repeat = atoi(optarg);
            break; // Modified the time of repeating the simulation.
        case 's':
            *save = atoi(optarg);
            break; // Modified the switch of saving every simulation.
        case 'T':
            *temperature = atof(optarg);
            break; // Modified the temperature.
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
/**
 * @brief 
 * 
 * To generate a number within the range provided randomly.
 * 
 * @param range     The range which the random number should be within.
 * 
 * @return double   A random number within the range provided.
 */
double my_rand(double range)
{
    return rand() / (float)RAND_MAX * range;
}
/**
 * @brief 
 * 
 * To calculate the distance according to the position provided.
 * 
 * @param x     X_position
 * @param y     Y_position
 * 
 * @return double   The distance
 */
double my_distance(double x, double y)
{
    return sqrt(x * x + y * y);
}
/**
 * @brief 
 * 
 * To calculate the energy according to the distance provided.
 * energy = -0.5 * cos(0.5 * PI * d) - cos(1.5 * PI * d)
 * 
 * @param d         The distance.
 * 
 * @return double   The energy.
 */
double energy(double d)
{
    return -0.5 * cos(0.5 * PI * d) - cos(1.5 * PI * d);
}
/**
 * @brief 
 * 
 * To generate an initial position randomly.
 * 
 * @param x     X_position
 * @param y     Y_position
 */
void position_initialize(double *x, double *y)
{
    double l = my_rand(2.0);
    double angle = my_rand(2.0 * PI);
    *x = l * cos(angle);
    *y = l * sin(angle);
}
/**
 * @brief 
 * 
 * To generate the direction of the next step.
 * 
 * @return double   The direction, in the form of angle within [0,2*PI].
 */
double decide_direction()
{
    return rand() / (float)RAND_MAX * 2.0 * PI;
}
/**
 * @brief 
 * 
 * To execute one Monte Carlo Step according to the del_energy.
 * 
 * @param x             X_position
 * @param y             Y_position
 * @param distance      The distance
 * @param temperature   The temperature
 * @param stepLen       The length of single step
 */
void monte_carlo_step(double *x, double *y, double *distance, double temperature, double stepLen)
{
    double angle = my_rand(2.0 * PI); //>>> Generate an angle
    double new_x = *x + stepLen * cos(angle);
    double new_y = *y + stepLen * sin(angle);
    double new_distance = my_distance(new_x, new_y);
    if (new_distance > 2)
        return;                                                   // Overstep the range, the possibility of the step is 0.
    double del_energy = energy(new_distance) - energy(*distance); // Calculate the del_energy.
    if (del_energy <= 0)
    { // Ready to move.
    }
    else
    { //>>> Calculate the possibility and judge
        if (my_rand(1.0) < exp(-del_energy / temperature))
        { // Ready to move.
        }
        else
        {
            return; // Not to move.
        }
    }
    // Start to move.
    *x = new_x;
    *y = new_y;
    *distance = new_distance;
}
/**
 * @brief 
 * 
 * To check the current state of the particle.
 * The stable state is within [0,0.69825].
 * 
 * @param distance
 * 
 * @return int
 */
int check_state(double distance)
{
    if (distance <= 0.69825)
    {
        return STABLE_STATE;
    }
    else
    {
        return EXCITED_STATE;
    }
}
/**
 * @brief 
 * 
 * To store the original data of the simulation.
 * 
 * @param fp        The file pointer.
 * @param step      The step number.
 * @param x         X_position
 * @param y         Y_position
 * @param distance  The distance
 * @param state     The state, 1=STABLE_STATE, 0=EXCITED_STATE
 */
void store_data(FILE *fp, int step, double x, double y, double distance, int state)
{
    fprintf(fp, "%d\t%.4lf\t%.4lf\t%.4lf\t%d\n", step, x, y, distance, state);
    fflush(fp);
}
/**
 * @brief 
 * 
 * To store the possibility of STABLE_STATE.
 * 
 * @param fp            The file pointer.
 * @param step          The step number.
 * @param count         The stable_state_count.
 * @param possibility   The possibility of STABLE_STATE.
 */
void store_poss(FILE *fp, int step, int count, double possibility)
{
    fprintf(fp, "%d\t%d\t%.4lf\n", step, count, possibility);
}

/**
 * @brief 
 * 
 * This is the main function.
 * 
 * @param argc      The number of parameters posted.
 * @param argv      The buffer storing the parameters posted.
 * 
 * @return int
 */
int main(int argc, char *argv[])
{
    // Process parameters
    int nStep = 1000;
    double stepLen = 0.5;
    double temperature = 2.0;
    char possFile[100] = "possibility_stable_state";
    char dataFile[100] = "monte_carlo_data";
    char cur_possFile[120] = "";
    char cur_dataFile[120] = "";
    FILE *file_data = NULL;
    FILE *file_poss = NULL;
    FILE *file_poss_all = NULL;
    int total_state_count = 0;
    int current_state_count = 0;
    int state = 0;
    int save = 1;
    int repeat = 1;
    process_param(argc, argv, &nStep, &stepLen, &temperature, &repeat, possFile, dataFile, &save);

    // Value preparation
    double x = 0;                      //> To record the current x coordinate.
    double y = 0;                      //> To record the current y coordinate.
    double distance = 0;               //> To record the current distance.
    int count;                         //> To record the current step.
    int index;                         //> To record the current simulation.
    srand((unsigned int)(time(NULL))); //> Initialize the seed.

    // IO preparation I
    if (save)
        system("mkdir -p data_monte_carlo_walk"); //> create a directory to store the data files.
    if (repeat > 1)
    {
        sprintf(cur_possFile, "%s_all.dat", possFile);              //> Generate the filename.
        file_poss_all = fopen(cur_possFile, "w+");                  //> Generate the file ptr.
        fprintf(file_poss_all, "BASED ON ALL THE MARKOV CHAINS\n"); //> This file stores the changes of the possibility.
        //> Printf the parameters.
        fprintf(file_poss_all, "TOTAL_STEP=%d\t SINGLE_STEP=%f\t NUMBER OF MARKOV CHAINS=%d\n", nStep, stepLen, repeat);
        fflush(file_poss_all);                                      //> Write into the file.
        //> create a directory to store the possibility_stable_state files.
        system("mkdir -p poss_monte_carlo_walk");
    }

    // Start to simulate
    for (index = 0; index < repeat; index++)
    {
        //> IO preparation II
        if (repeat > 1)
        {                                                                                       //>> About the possibility_stable_state of this Markov chain.
            sprintf(cur_possFile, "./poss_monte_carlo_walk/%s - %d.dat", possFile, index + 1);  //>> Generate the filename.
            file_poss = fopen(cur_possFile, "w+");                                              //>> Generate the file ptr.
            fprintf(file_poss, "TOTAL_STEP=%d\t SINGLE_STEP=%f\n", nStep, stepLen);             //>> Print the parameters.
        }
        else
        {
            //>>  No repeating. Just one file_poss is ok.
            sprintf(cur_possFile, "%s.dat", possFile);                                  //>> Generate the filename.
            file_poss_all = fopen(cur_possFile, "w+");                                  //>> Generate the file ptr.
            fprintf(file_poss_all, "TOTAL_STEP=%d\t SINGLE_STEP=%f\n", nStep, stepLen); //>> Print the parameters.
            fflush(file_poss_all);                                                      //>> Write into the file.
        }

        if (save)
        {                                                                                       //>> About the original data of this Markov chain.
            sprintf(cur_dataFile, "./data_monte_carlo_walk/%s - %d.dat", dataFile, index + 1);  //>> Generate the filename.
            file_data = fopen(cur_dataFile, "w+");                                              //>> Generate the file ptr.
            fprintf(file_data,"1 = STABLE_STATE, 0 = EXCITED_STATE\n");
            fprintf(file_data, "Step\t X \t Y \t d \t state \n");                          //>> Print the head of the table.
            fflush(file_data);                                                             //>> Write into the file,
            if (repeat > 1)
                fprintf(file_poss, "DATA NOT SAVED!\n");
            else
                fprintf(file_poss_all, "DATA NOT SAVED!\n"); //>> Record the data origin into cur_possFile.
        }
        else
        {
            if (repeat > 1)
                fprintf(file_poss, "DATA NOT SAVED!\n");
            else
                fprintf(file_poss_all, "DATA NOT SAVED!\n");
        }
        if (repeat > 1){
            fprintf(file_poss, "INDEX\t COUNT\t POSSIBILITY\n");     //> Print the head of the table.
            fflush(file_poss);                                       //>> Write into the file.
        }
        fprintf(file_poss_all, "INDEX\t COUNT\t POSSIBILITY\n");     //> Print the head of the table.
        fflush(file_poss_all);                                       //>> Write into the file.

        //> Simulation.
        //>> Generate an initial position.
        position_initialize(&x, &y);   //>>> Generate initial position.
        distance = my_distance(x, y);  //>>> Calculate the distance.
        state = check_state(distance); //>>> Check the state.
        current_state_count = 0;       //>>> Reset state counter.
        //>> Generate a [nStep] Markov chain and count the states.
        for (count = 0; count < nStep; count++)
        {
            if (save)
                store_data(file_data, count, x, y, distance, state);
            if (repeat > 1) //>>> Calculate the ratio of stable states and store.
                store_poss(file_poss_all, count, current_state_count, current_state_count / (double)(count + 1));
            //>>> Calculate the ratio of stable states and store.
            store_poss(file_poss_all, index * nStep + count, total_state_count, total_state_count / (double)(index * nStep + count + 1));
            monte_carlo_step(&x, &y, &distance, temperature, stepLen); //>>> Execute one monte_carlo_step
            state = check_state(distance);                             //>>> Check and count the states.
            current_state_count += state;                              //>>> Count the states.
            total_state_count += state;                                //>>> Count the states.
        }
        if (save)
            fclose(file_data);
        if (repeat > 1)
            fclose(file_poss);
    }
    fclose(file_poss_all);
    return STATUS_OK;
}