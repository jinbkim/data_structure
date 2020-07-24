/*                                                           */
/*  SWAP.C  :   Swap for any data type                       */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <alloc.h>
#include <mem.h>

void swap(void *a, void *b, int n)
    {
    char *t;
    t = (char*)malloc(n);
    memcpy(t, a, n);
    memcpy(a, b, n);
    memcpy(b, t, n);
    free(t);
    }

void main(void)
    {
    char c1 = 'A', c2 = 'B';
    int  i1 = 100, i2 = 200;
    float f1 = 3.14, f2 = 2.71;

    printf("\nBefore : %c  %c", c1, c2);
    swap(&c1, &c2, sizeof(char));
    printf("\tAfter : %c  %c", c1, c2);

    printf("\nBefore : %d  %d", i1, i2);
    swap(&i1, &i2, sizeof(int));
    printf("\tAfter : %d  %d", i1, i2);

    printf("\nBefore : %f  %f", f1, f2);
    swap(&f1, &f2, sizeof(float));
    printf("\tAfter : %f  %f", f1, f2);
    }

