/*                                                           */
/*  2DARRAY.C  :  Example of 2 dimensional array, matrix     */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>

#define MAX 2

void input_matrix(int m[][MAX], int n)
    {
    int i, j;

    printf("\nInput %d by %d Matrix in row order ->", n, n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &m[i][j]);
    }

void print_matrix(int m[][MAX], int n)
    {
    int i, j;

    printf("\n");
    for (i = 0; i < n; i++)
        {
        for (j = 0; j < n; j++)
            printf("%-6d", m[i][j]);
        printf("\n");
        }
    }


void multiply_matrix(int m1[][MAX], int m2[][MAX], int m3[][MAX], int n)
    {
    int i, j, k;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            {
            m3[i][j] = 0;
            for (k = 0; k < n; k++)
                m3[i][j] += m1[i][k] * m2[k][j];
            }
    }

void main(void)
    {
    int mat1[MAX][MAX];
    int mat2[MAX][MAX];
    int mat3[MAX][MAX];

    input_matrix(mat1, MAX);
    input_matrix(mat2, MAX);

    multiply_matrix(mat1, mat2, mat3, MAX);

    printf("\n Answer : ");
    print_matrix(mat3, MAX);
    }




