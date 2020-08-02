/*                                                           */
/*  PRIME1.C  :   prime test program 1                       */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>

#define TRUE   1

int is_prime(int n)
    {
    int i;
    for (i = 2; i < n; i++)
        if (n % i == 0)
            return !TRUE;
    return TRUE;
    }

void main(void)
    {
    int n;

    puts("\n PRIME1  :  Test that input number is prime or not."
         "\n            Input 0 to end program.");

    while (TRUE)
        {
        puts("\nInput number to test ->");
        scanf("%d", &n);
        if (n < 0)   /* Invalid input */
            continue;
        if (n == 0)   /* Terminate */
            break;
	printf("\n   Ans : %d is%s prime number"
	       ,n , is_prime(n) ? "" : " not");
	}
    }




