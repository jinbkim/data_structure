/*                                                           */
/*  FACTOR.C  :  Recursive Factorial                         */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>

int factorial(int n)
    {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
    }

int iter_factorial(int n)
    {
    int f = 1;
    while (n > 0)
        f = f * n--;
    return f;
    }

void main(void)
    {
    int i = 0;
    printf("\nIf you want to quit, enter minus integer.");
    while (1)
        {
        printf("\nEnter integer to get factorial -> ");
        scanf("%d", &i);
        if (i < 0) break;
        printf("\nRecursive Ans : %d! = %d", i, factorial(i));
        printf("\nIterative Ans : %d! = %d", i, iter_factorial(i));
        }
    }
