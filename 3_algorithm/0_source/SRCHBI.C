/*                                                           */
/*  SRCHBI.C  :   Binary Searching Algorithm Test            */
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

int bi_search(int key, int a[], int n)
    {
    int mid;
    int left = 0;
    int right = n-1;
    while (right >= left)
        {
        mid = (right + left) / 2;
        if (key == a[mid]) return mid;
        if (key <  a[mid]) right = mid - 1;
        else              left = mid + 1;
        }
    return -1;
    }

int bi_insert(int key, int a[], int *np)
    {
    int p = 0;
    int i;
    while (key > a[p] && p < *np) p++;  /* find position */
    for (i = *np; i > p; i--) a[i] = a[i-1];   /* make hole */
    a[p] = key;   /* fill hole with key */
    (*np)++;      /* increase n */
    return p;
    }

int bi_delete(int key, int a[], int *np)
    {
    int p;
    int i;
    if (*np > 0)
        {
        if ((p = bi_search(key, a, *np)) < 0) return -1;
        for (i = p+1; i < *np; i++) a[i-1] = a[i];
        (*np)--;
        return p;
        }
    return -1;
    }

int bii_search(int key, int a[], int n)
    {
    int mid;
    int left = 0;
    int right = n-1;
    while (right >= left)
        {
        if (a[right] != a[left])
            mid = left + (float)(key-a[left])*(right-left)/(a[right]-a[left]);
        else
            mid = (left + right) / 2;
        if (key == a[mid]) return mid;
        if (key <  a[mid]) right = mid - 1;
        else              left = mid + 1;
        }
    return -1;

    }

void bi_list(int a[], int n)
    {
    int i;
    printf("\n");
    for (i = 0; i < n; i++) printf("%6c", a[i]);
    }

void interpret(int a[], int *np, int N)
    {
    char command[2];
    char key[2];
    int p;
    while (command[0] != 'q')
        {
        printf("\nInput command ->");
        scanf("%1s", command);
        scanf("%1s", &key);
        switch (command[0])
            {
            case 'i' :
            case 'I' : if (*np < N)
                           {
                           bi_insert(key[0], a, np);
                           printf("\n   Successful insert.");
                           }
                       else
                           printf("\n   Error : Table full.");
                       break;
            case 'd' :
            case 'D' : if (bi_delete(key[0], a, np) < 0)
                           printf("\n   Error : Table Empty.");
                       else
                           printf("\n   Successful delete.");
                       break;
            case 's' :
            case 'S' : if ((p = bi_search(key[0], a, *np)) < 0)
                           printf("\n   Error : Can'f find that key");
                       else
                           printf("\n   Ok! find in %d th position", p);
                       break;
            case 'f' :
            case 'F' : if ((p = bii_search(key[0], a, *np)) < 0)
                           printf("\n   Error : Can't find that key");
                       else
                           printf("\n   Ok ! find in %d th position & move front", p);
                       break;
            case 'l' :
            case 'L' : bi_list(a, *np);
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
    for (i = 0; i < LOOP; i++) bi_search(random(30000), a, n);
    t2 = get_tick();
    printf("\n li_search %d loops ellapse %ld ticks.", LOOP, diff_tick(t1,t2));
    t1 = get_tick();
    for (i = 0; i < LOOP; i++) bii_search(random(30000), a, n);
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





