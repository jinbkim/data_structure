/*                                                           */
/*  1DARRAY.C  :  Example of 1 dimensional array             */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>

#define MAX  10

int average(int a[], int n)
    {
    int sum = 0;
    int i;

    for (i = 0; i < n; i++)
        sum += a[i];

    return (sum / n);
    }

void main(void)
    {
    int array[MAX];
    int i;

    printf("\nInput %d integer -> ", MAX);
    for (i = 0; i < MAX; i++)
        scanf("%d", array + i);
    printf("\nAverage of %d integer is %d", MAX, average(array, MAX));
    }


