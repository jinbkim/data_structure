/*                                                           */
/*  SRCHLIT.C  :   Linear Searching Algorithm Test           */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define MAX  10000

void load_data(int a[], int n)
    {
    FILE *fp;
    if ((fp = fopen("RANDOM.DAT", "rb")) == NULL)
        {
        printf("\nDisk Error!");
        exit(1);
        }
    fread(a, n, sizeof(int), fp);
    fclose(fp);
    }

int *li_search(int key, int a[], int n)
    {
    int i = 0;
    while (a[i] != key && i < n) i++;
    return (i < n ? a+i : NULL);
    }

int *li_insert(int key, int a[], int *np)
    {
    a[(*np)++] = key;
    return a + *np - 1;
    }

int *li_delete(int key, int a[], int *np)
    {
    int *ip;
    int i;
    if (*np > 0)
        {
        if ((ip = li_search(key, a, *np)) == NULL) return NULL;
        for (i = (ip-a)+1; i < *np; i++) a[i-1] = a[i];
        (*np)--;
        return ip;
        }
    return NULL;
    }

int *lfi_search(int key, int a[], int n)
    {
    int i = 0, j;
    int v;
    while (a[i] != key && i < n) i++;
    if (i >= n) return NULL;
    v = key;
    for (j = i+1; j < n; j++) a[j-1] = a[j];
    for (j = n-2; j >= 0; j--) a[j+1] = a[j];
    a[0] = v;
    return a+i;
    }

void li_list(int a[], int n)
    {
    int i;
    printf("\n");
    for (i = 0; i < n; i++) printf("%6c", a[i]);
    }

void interpret(int a[], int *np, int N)
    {
    char command[2];
    char key[2];
    int *p;
    while (command[0] != 'q')
        {
        printf("\nInput command ->");
        scanf("%1s", command);
        scanf("%1s", &key);
        switch (command[0])
            {
            case 'i' :
            case 'I' : if (li_insert(key[0], a, np) == NULL)
                           printf("\n   Error : Table full.");
                       else
                           printf("\n   Successful insert.");
                       break;
            case 'd' :
            case 'D' : if (li_delete(key[0], a, np) == NULL)
                           printf("\n   Error : Table Empty.");
                       else
                           printf("\n   Successful delete.");
                       break;
            case 's' :
            case 'S' : if ((p = li_search(key[0], a, *np)) == NULL)
                           printf("\n   Error : Can'f find that key");
                       else
                           printf("\n   Ok! find in %d th position", p-a);
                       break;
            case 'f' :
            case 'F' : if ((p = lfi_search(key[0], a, *np)) == NULL)
                           printf("\n   Error : Can't find that key");
                       else
                           printf("\n   Ok ! find in %d th position & move front", p-a);
                       break;
            case 'l' :
            case 'L' : li_list(a, *np);
                       break;
            }
        printf("  n = %d", *np);
        }
    }

#define LOOP 100

void li_test(int a[], int n)
    {
    int i;
    long t1, t2;
    t1 = get_tick();
    for (i = 0; i < LOOP; i++) li_search(random(30000), a, n);
    t2 = get_tick();
    printf("\n li_search %d loops ellapse %ld ticks.", LOOP, diff_tick(t1,t2));
    t1 = get_tick();
    for (i = 0; i < LOOP; i++) lfi_search(random(30000), a, n);
    t2 = get_tick();
    printf("\n lfi_search %d loops ellapse %ld ticks.", LOOP, diff_tick(t1,t2));
    }

void main(void)
    {
    int *table;
    int nitem = 0;
    table = (int*)malloc(sizeof(int)*MAX);
    /*
    load_data(table, nitem);
    li_test(table, nitem);
    */
    interpret(table, &nitem, MAX);
    free(table);
    }





