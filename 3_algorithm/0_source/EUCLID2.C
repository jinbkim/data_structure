/*                                                           */
/*  EUCLID2.C  :  Advanced  Euclid's aligorithm              */
/*                                                           */
/*                Programmed By Lee jaekyu                   */
/*                                                           */

#include <stdio.h>
// #include <dos.h>
// #include "timer.h"
#include <time.h>

/* function for getting gcd by minus method */

int gcd_minus(int u, int v)
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

/* function for getting gcd by modulus method */

int gcd_modulus(int u, int v)
    {
    int t;

    while (v)
        {
        t = u % v;
        u = v;
        v = t;
        }
    return u;
    }

/* functions for getting gcd by recursion */

int gcd_recursion(int u, int v)
    {
    if (v == 0)
        return u;
    else
	return gcd_recursion(v, u % v);
    }

#define LOOP 10000

int main(void)
    {
    int u, v, gcd;
    long t1, t2;
    int i;

    puts("\n EUCLID2 : Get GCD with time checking"
         "\n           Input 0 to end program");

    while (1)
        {
        puts("\n\nInput two positive integer -> ");
        scanf("%d %d", &u, &v);
        if (u < 0  ||  v < 0)   /* Invalid input */
            continue;
        if (u == 0  ||  v == 0)   /* Termination code */
            break;

        t1 = clock();;
        for (i = 0; i < LOOP; i++)
	    gcd = gcd_minus(u, v);
	t2 = clock();;
	printf("\n Minus methods : GCD of %d and %d is %d. in %ld ticks",
		u, v, gcd, t2 - t1);

        t1 = clock();;
        for (i = 0; i < LOOP; i++)
	    gcd = gcd_modulus(u, v);
	t2 = clock();;
	printf("\n Modulus methods : GCD of %d and %d is %d. in %ld ticks",
		u, v, gcd, t2 - t1);

        t1 = clock();;
        for (i = 0; i < LOOP; i++)
	    gcd = gcd_recursion(u, v);
	t2 = clock();;
	printf("\n Recursion methods : GCD of %d and %d is %d. in %ld ticks",
		u, v, gcd, t2 - t1);
	}
    }






