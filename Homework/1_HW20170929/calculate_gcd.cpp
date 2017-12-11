/* ------------------------------------------------------------
 * File name: calculate_gcd.c
 * Author: Zhirui Dai (Astro)
 * Last modified: 2017-09-29
 * Description: The program is to calculate gcd of two numbers with
 *      the method of "Divide Each Other", which is the Version 2.0
 *      of the method of "Minus Each Other".
 *      When "a % b = 0" appears, the gcd of a0 and b0 is b.
 *     gcd: Greatest Common Divisor.
 * ------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "STATUS_CODE.h"
/* ------------------------------------------------------------
 * Function name: gcd
 * Last modified: 2017-09-29
 * Description: gcd is to calculate the greatest common divisor(gcd)
 *      of two numbers.
 * ------------------------------------------------------------ */
int gcd(int a, int b)
{   
    a = abs(a);
    b = abs(b);
    // To check if a or b is zero.
    if (!(a * b))
    {
        if (a)
            return a; // a is not zero, gcd is a.
        else
            return b; // a is zero, gcd is b.
    }
    // Both numbers are not zero, start to calculate gcd.
    while (a * b)
    {
        if (a > b)
        {
            if (!(a %= b))
                return b; // Calculation completed, b is gcd.
        }
        else
        {
            if (!(b %= a))
                return a; // Calculation completed, a is gcd.
        }
    }
    return STATUS_RETURN_ERROR;
}
/* ------------------------------------------------------------
 * Function name: main
 * Last modified: 2017-09-29
 * Description: This is the main function.
 * ------------------------------------------------------------ */
int main(int argc, char *argv[])
{
    // Check the parameters.
    //> Check the number of the parameters.
    if (argc < 3)
    {
        printf("ERROR: Not enough parameters!\n");
        return STATUS_PARAM_ERROR;
    }
    if (argc > 3)
    {
        printf("WARNNING: Too many parameters! Automatically ignore the rest.\n");
    }
    //> Check the type of the parameters.

    if (*(argv + 1)[0] == '+' || *(argv + 1)[0] == '-' || (*(argv + 1)[0] >= '0' && *(argv + 1)[0] <= '9'))
        ;
    else
    {
        printf("ERROR: The first parameter is not a number!\n");
        return STATUS_PARAM_ERROR;
    }
    if (*(argv + 2)[0] == '+' || *(argv + 2)[0] == '-' || (*(argv + 2)[0] >= '0' && *(argv + 2)[0] <= '9'))
        ;
    else
    {
        printf("ERROR: The second parameter is not a number!\n");
        return STATUS_PARAM_ERROR;
    }
    // Parameter check completed. Start to calculate the gcd.
    int num[2];
    // Parameter type convert.
    num[0] = atoi(argv[1]);
    num[1] = atoi(argv[2]);
    // Print the result.
    printf("The greatest common divisor (gcd) of %d and %d is %d.\n", num[0], num[1], gcd(num[0],num[1]));
    return STATUS_OK;
}
