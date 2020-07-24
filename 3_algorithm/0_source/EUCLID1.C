/*                                                           */
/*  EUCLID1.C  :  Implementation of Euclid's aligorithm 1    */
/*                                                           */
/*                Programmed By Lee jaekyu                   */
/*                                                           */

#include <stdio.h>

int get_gcd(int u, int v)
    {
    int t;

    while (u)
        {
        if (u < v)    /* u must be larger than v, otherwise exchange them */
            {
            t = u ; u = v; v = t;
            }
        u = u - v;
        }
    return v;
    }

void main(void)
    {
    int u, v;

    puts("\n EUCLID1 : Get GCD of two positive integer"
         "\n           Input 0 to end program");

    while (1)
        {
        puts("\n\n Iput two positive integer -> ");
        scanf("%d %d", &u, &v);
        if (u < 0  ||  v < 0)   /* Invalid input */
            continue;
        if (u == 0  ||  v == 0)   /* Termination code */
            break;
        printf("\n    GCD of %d and %d is %d.", u, v, get_gcd(u, v));
        }
    }






