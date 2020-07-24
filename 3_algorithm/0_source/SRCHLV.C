/*                                                           */
/*  SRCHLV.C  :   General Linear Searching                  */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define MAX  10000

#define BASE(i)  ((char*)base + (i)*width)
typedef int (*FCMP)(const void*, const void*);

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

void *lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
    {
    int i = 0;
    while (fcmp(BASE(i), key) != 0 && i < *num) i++;
    return (i < *num ? BASE(i) : NULL);
    }

void *lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
    {
    memcpy(BASE((*num)++), key, width);
    return BASE((*num)-1);
    }

void *lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
    {
    void *ip;
    int i;
    if (*num > 0)
        {
        if ((ip = lv_search(key, base, num, width, fcmp)) == NULL)
            return NULL;
        for (i = ((char*)ip - (char*)base)/width+1; i < *num; i++)
            memcpy(BASE(i-1), BASE(i), width);
        (*num)--;
        return ip;
        }
    return NULL;
    }

void *lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp)
    {
    int i = 0, j;
    void *v;
    while (fcmp(BASE(i), key) != 0  &&  i < *num) i++;
    if (i >= *num) return NULL;
    v = malloc(width);
    memcpy(v, BASE(i), width);
    for (j = i+1; j < *num; j++)
        memcpy(BASE(j-1), BASE(j), width);
    for (j = *num-2; j >= 0; j--)
        memcpy(BASE(j+1), BASE(j), width);
    memcpy(base, v, width);
    return BASE(i);
    }

void li_list(int a[], int n)
    {
    int i;
    printf("\n");
    for (i = 0; i < n; i++) printf("%6c", a[i]);
    }

int intcmp(const void *a, const void *b)
    {
    return *(int*)a - *(int*)b;
    }

void interpret(int a[], int *np, int N)
    {
    char command[2];
    char key[2];
    int k;
    void *p;
    while (command[0] != 'q')
        {
        printf("\nInput command ->");
        scanf("%1s", command);
        scanf("%1s", &key);
        k = (int)key[0];
        switch (command[0])
            {
            case 'i' :
            case 'I' : if (*np < N)
                           {
                           lv_insert(&k, a, np, sizeof(int), intcmp);
                           printf("\n   Successful Insert.");
                           }
                       else
                           printf("\n   Error : Table full.");
                       break;
            case 'd' :
            case 'D' : if (lv_delete(&k, a, np, sizeof(int), intcmp) == NULL)
                           printf("\n   Error : Table empty or can't find.");
                       else
                           printf("\n   Successful delete.");
                       break;
            case 's' :
            case 'S' : if ((p = lv_search(&k, a, np, sizeof(int), intcmp)) == NULL)
                           printf("\n   Error : Can'f find that key");
                       else
                           printf("\n   Ok! find in %d th position",
                                        ((char*)p-(char*)a)/sizeof(int));
                       break;
            case 'f' :
            case 'F' : if ((p = lfv_search(&k, a, np, sizeof(int), intcmp)) == NULL)
                           printf("\n   Error : Can't find that key");
                       else
                           printf("\n   Ok ! find in %d th position & move front",
                                   ((char*)p-(char*)a)/sizeof(int));
                       break;
            case 'l' :
            case 'L' : li_list(a, *np);
                       break;
            }
        printf("  n = %d", *np);
        }
    }

#define LOOP 100

void lv_test(int a[], int n)
    {
    int i;
    int r;
    long t1, t2;
    t1 = get_tick();
    r = random(30000);
    for (i = 0; i < LOOP; i++) lv_search(&r, a, &n, sizeof(int), intcmp);
    t2 = get_tick();
    printf("\n lv_search %d loops ellapse %ld ticks.", LOOP, diff_tick(t1,t2));
    t1 = get_tick();
    r = random(30000);
    for (i = 0; i < LOOP; i++) lfv_search(&r, a, &n, sizeof(int), intcmp);
    t2 = get_tick();
    printf("\n lfv_search %d loops ellapse %ld ticks.", LOOP, diff_tick(t1,t2));
    }

void main(void)
    {
    int *table;
    /*
    int nitem = 10000;
    */
    int nitem = 0;
    table = (int*)malloc(sizeof(int)*MAX);
    /*
    load_data(table, nitem);
    li_test(table, nitem);
    */
    interpret(table, &nitem, MAX);
    free(table);
    }





