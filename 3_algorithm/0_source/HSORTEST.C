/*                                                           */
/*  HSORTEST.C  :  Heap sort algorithm speed test            */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <alloc.h>
#include <string.h>
#include <bios.h>
#include <stdlib.h>
#include <limits.h>
#include "timer.h"

#define SORTED   0
#define RANDOM   1
#define HALFSO   2
#define REVERS   3

int *set_array(int *a, int n, int m)
    {
    int i;
    FILE *fp;
    if ((a = (int*)malloc(sizeof(int) * (n+1))) == NULL)
        {
        printf("\nOut of memory");
        return a;
        }
    switch (m)
        {
        case SORTED : if ((fp = fopen("ASCEND.DAT", "rb")) == NULL)
                          {
                          printf("\nFile reading error!");
                          return NULL;
                          }
                      fread(a+1, sizeof(int), n, fp);
                      fclose(fp);
                      break;
        case RANDOM : if ((fp = fopen("RANDOM.DAT", "rb")) == NULL)
                          {
                          printf("\nFile reading error!");
                          return NULL;
                          }
                      fread(a+1, sizeof(int), n, fp);
                      fclose(fp);
                      break;
        case HALFSO : if ((fp = fopen("ASCEND.DAT", "rb")) == NULL)
                          {
                          printf("\nFile reading error!");
                          return NULL;
                          }
                      fread(a+1, sizeof(int), n/2, fp);
                      fclose(fp);
                      if ((fp = fopen("RANDOM.DAT", "rb")) == NULL)
                          {
                          printf("\nFile reading error!");
                          return NULL;
                          }
                      fread(a+1 + n/2, sizeof(int), n - n/2, fp);
                      fclose(fp);
                      break;
        case REVERS : if ((fp = fopen("DESCEND.DAT", "rb")) == NULL)
                          {
                          printf("\nFile reading error!");
                          return NULL;
                          }
                      fread(a+1, sizeof(int), n, fp);
                      fclose(fp);
                      break;
        }
    return a;
    }

int is_sorted(int *a, int n)
    {
    int sorted = 1;
    int i;
    for (i = 1; i < n; i++)
	{
	if (a[i] > a[i+1])
	    return !sorted;
	}
    return sorted;
    }

long sort_testnm(int n, int m, void (*sort_func)(int*, int))
    {
    long t1, t2, t;
    int *a;
    a = set_array(a, n, m);
    t1 = get_tick();
    sort_func(a, n);
    t2 = get_tick();
    t = diff_tick(t1, t2);
    if (!is_sorted(a, n))
	t = -1;
    free(a);
    return t;
    }

void sort_testn(int n, void (*sort_func)(int*, int))
    {
    long t;
    int i;
    char *str[] =
        {  "Sorted", "Random", "Half-Sorted", "Reversed" };
    printf("\n    finish %d element", n);
    for (i = SORTED; i <= REVERS; i++)
        {
        t = sort_testnm(n, i, sort_func);
        printf("\n        %s in %ld ticks", str[i], t);
        }
    }

void sort_test(char *name, void (*sort_func)(int*, int))
    {
    int n[] =
	 { 10, 100, 500, 1000, 2000, 3000, 4000, 5000, 7000, 10000, -1};
    int i = 0;
    printf("\n%s",name);
    while (n[i] > 0)
        sort_testn(n[i++], sort_func);
    }

void upheap(int a[], int k)
    {
    int v;
    v = a[k];
    a[0] = INT_MAX;  /* sentinel */
    while (a[k/2] <= v)
        {
        a[k] = a[k/2];
        k /= 2;
        }
    a[k] = v;
    }

void downheap(int a[], int n, int k)
    {
    int i, v;
    v = a[k];
    while (k <= n/2)
        {
        i = k<<1;
        if (i < n && a[i] < a[i+1]) i++;
        if (v >= a[i]) break;
        a[k] = a[i];
        k = i;
        }
    a[k] = v;
    }

void insert(int a[], int *n, int v)
    {
    a[++(*n)] = v;
    upheap(a, *n);
    }

int extract(int a[], int *n)
    {
    int v = a[1];
    a[1] = a[(*n)--];
    downheap(a, *n, 1);
    return v;
    }

void heap_sort(int a[], int n)
    {    /* top-down heap sort */
    int i;
    int hn = 0;
    for (i = 1; i <= n; i++)
        insert(a, &hn, a[i]);
    for (i = hn; i >= 1; i--)
        a[i] = extract(a, &hn);
    }

void heap_sort1(int a[], int n)
    {
    int k, t;
    for (k = n/2; k >= 1; k--)
        downheap(a, n, k);
    while (n > 1)
        {
        t = a[1];
        a[1] = a[n];
        a[n] = t;
        downheap(a, --n, 1);
        }
    }

void main(void)
    {
    sort_test("Heap Sort top-down construction", heap_sort);
    sort_test("Heap Sort buttom-up construction", heap_sort1);
    }





