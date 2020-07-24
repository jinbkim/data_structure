/*                                                           */
/*  FIBO.C  :  Get Fibonacci numbers                         */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>

int fibonacci(int n)
    {
    if (n == 1 || n == 2)
        return 1;
    else
        return fibonacci(n-1) + fibonacci(n-2);
    }

int iter_fibonacci(int n)
    {
    int r = 0;
    int a = 1, b = 1;

    if (n == 1 || n == 2)
        return 1;

    while (n-- > 2)
        {
        r = a + b;
        a = b;
        b = r;
        }
    return r;
    }

void main(void)
    {
    int i = 0;
    printf("\nIf you want to quit, enter minus integer.");
    while (1)
        {
        printf("\nEnter integer to get fibonacci numbers -> ");
        scanf("%d", &i);
        if (i <= 0) break;
        printf("\nRecursive Ans : Fibonacci[%d] = %d", i, fibonacci(i));
        printf("\nIterative Ans : Fibonacci[%d] = %d", i, iter_fibonacci(i));
        }
    }

