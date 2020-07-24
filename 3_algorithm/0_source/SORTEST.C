/*                                                           */
/*  SORTEST.C  :  Sorting algorithm speed test               */
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

#define MAX  10000
int top;
int stack[MAX];

#define init_stack()      (top = -1)
#define push(t)           (stack[++top] = t)
#define pop()             (stack[top--])
#define is_stack_empty()  (top < 0)

int *set_array(int *a, int n, int m)
    {
    int i;
    FILE *fp;
    if ((a = (int*)malloc(sizeof(int) * n)) == NULL)
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
                      fread(a, sizeof(int), n, fp);
                      fclose(fp);
                      break;
        case RANDOM : if ((fp = fopen("RANDOM.DAT", "rb")) == NULL)
                          {
                          printf("\nFile reading error!");
                          return NULL;
                          }
                      fread(a, sizeof(int), n, fp);
                      fclose(fp);
                      break;
        case HALFSO : if ((fp = fopen("ASCEND.DAT", "rb")) == NULL)
                          {
                          printf("\nFile reading error!");
                          return NULL;
                          }
                      fread(a, sizeof(int), n/2, fp);
                      fclose(fp);
                      if ((fp = fopen("RANDOM.DAT", "rb")) == NULL)
                          {
                          printf("\nFile reading error!");
                          return NULL;
                          }
                      fread(a + n/2, sizeof(int), n - n/2, fp);
                      fclose(fp);
                      break;
        case REVERS : if ((fp = fopen("DESCEND.DAT", "rb")) == NULL)
                          {
                          printf("\nFile reading error!");
                          return NULL;
                          }
                      fread(a, sizeof(int), n, fp);
                      fclose(fp);
                      break;
        }
    return a;
    }

int is_sorted(int *a, int n)
    {
    int sorted = 1;
    int i;
    for (i = 0; i < n-1; i++)
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

void select_sort(int a[], int n)
    {
    int min;
    int minindex;
    int i, j;

    for (i = 0; i < n - 1; i++)
	{
	minindex = i;
	min = a[i];
	for (j = i + 1; j < n; j++)
	    {
	    if (min > a[j])
		{
		min = a[j];
		minindex = j;
		}
	    }
	a[minindex] = a[i];
	a[i] = min;
	}
    }

void insert_sort(int a[], int n)
    {
    int i, j, t;
    for (i = 1; i < n; i++)
	{
	t = a[i];
	j = i;
	while (a[j-1] > t && j > 0)
	    {
	    a[j] = a[j-1];
	    j--;
	    }
	a[j] = t;
	}
    }

void insert_sort1(int a[], int n)
    {    /* use sentinel a[0] must be smallest number */
    int i, j, t;
    for (i = 2; i <= n; i++)
	{
	t = a[i];
	j = i;
	while (a[j-1] > t)
	    {
	    a[j] = a[j-1];
	    j--;
	    }
	a[j] = t;
	}
    }

void bubble_sort(int a[], int n)
    {
    int i, j, t;
    for (i = 0; i < n-1; i++)
	{
	for (j = 1; j < n-i; j++)
	    {
	    if (a[j-1] > a[j])
		{
		t = a[j-1];
		a[j-1] = a[j];
		a[j] = t;
		}
	    }
	}
    }


void bubble_sort1(int a[], int n)
    {      /* sentinel */
    int i, j, t, s;
    for (i = 0; i < n-1; i++)
	{
	s = 0;
	for (j = 1; j < n-i; j++)
	    {
	    if (a[j-1] > a[j])
		{
		t = a[j-1];
		a[j-1] = a[j];
		a[j] = t;
		s = 1;
                }
            }
	if (s == 0)   /* sort completed */
            break;
        }
    }

void shell_sort(int a[], int n)
    {
    int i, j, k, h, v;
    for (h = n/2; h > 0; h /= 2)
	{
	for (i = 0; i < h; i++)
	    {
	    for (j = i+h; j < n; j += h)
		{
		v = a[j];
		k = j;
		while (k > h-1 && a[k-h] > v)
		    {
		    a[k] = a[k-h];
		    k -= h;
		    }
		a[k] = v;
		}
	    }
	}
    }

void shell_sort1(int a[], int n)
    {
    int i, j, k, h, v;
    for (h = 1; h < n; h = 3*h+1);
    for (h /= 3; h > 0; h /= 3)   /* (h-1)/3 */
	{
	for (i = 0; i < h; i++)
	    {
	    for (j = i+h; j < n; j += h)
		{
		v = a[j];
		k = j;
		while (k > h-1 && a[k-h] > v)
		    {
		    a[k] = a[k-h];
		    k -= h;
		    }
		a[k] = v;
		}
	    }
	}
    }

void quick_sort(int a[], int n)
    {
    int v, t;
    int i, j;
    if (n > 1)    /* terminal condition */
	{
	v = a[n-1];
	i = -1;
	j = n-1;
	while (1)      /* partition */
	    {
	    while (a[++i] < v);
	    while (a[--j] > v);
	    if (i >= j) break;
	    t = a[i];
	    a[i] = a[j];
	    a[j] = t;
	    }
	t = a[i];
	a[i] = a[n-1];
	a[n-1] = t;
	quick_sort(a, i);
	quick_sort(a+i+1, n-i-1);
	}
    }

int intcmp(const void *a, const void *b)
    {
    return (*(int*)a - *(int*)b);
    }

void quick_sort5(int a[], int n)
    {    /* library function */
    qsort(a, n, sizeof(int), intcmp);
    }

void quick_sort1(int a[], int n)
    {     /* remove recursion */
    int v, t;
    int i, j;
    int l, r;
    init_stack();
    l = 0;
    r = n-1;
    push(r);
    push(l);
    while (!is_stack_empty())
	{
	l = pop();
	r = pop();
	if (r-l+1 > 1)    /* terminal condition */
	    {
	    v = a[r];
	    i = l-1;
	    j = r;
	    while (1)      /* partition */
		{
		while (a[++i] < v);
		while (a[--j] > v);
		if (i >= j) break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
		}
	    t = a[i];
	    a[i] = a[r];
	    a[r] = t;
	    push(r);
	    push(i+1);
	    push(i-1);
	    push(l);
	    }
	}
    }

void quick_sort2(int a[], int n)
    {     /* remove recursion & random partition*/
    int v, t;
    int i, j;
    int l, r;
    init_stack();
    l = 0;
    r = n-1;
    push(r);
    push(l);
    while (!is_stack_empty())
	{
	l = pop();
	r = pop();
	if (r-l+1 > 1)    /* terminal condition */
	    {
	    t = random(r-l+1) + l;
	    v = a[t];     /* exchange partition with rightmost */
	    a[t] = a[r];
	    a[r] = v;
	    i = l-1;
	    j = r;
	    while (1)      /* partition */
		{
		while (a[++i] < v);
		while (a[--j] > v);
		if (i >= j) break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
		}
	    t = a[i];
	    a[i] = a[r];
	    a[r] = t;
	    push(r);
	    push(i+1);
	    push(i-1);
	    push(l);
	    }
	}
    }


void quick_sort3(int a[], int n)
    {     /* remove recursion & random partition & small subfile insert*/
    int v, t;
    int i, j;
    int l, r;
    init_stack();
    l = 0;
    r = n-1;
    push(r);
    push(l);
    while (!is_stack_empty())
	{
	l = pop();
	r = pop();
	if (r-l+1 > 200)    /* terminal condition */
	    {
	    t = random(r-l+1) + l;
	    v = a[t];     /* exchange partition with rightmost */
	    a[t] = a[r];
	    a[r] = v;
	    i = l-1;
	    j = r;
	    while (1)      /* partition */
		{
		while (a[++i] < v);
		while (a[--j] > v);
		if (i >= j) break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
		}
	    t = a[i];
	    a[i] = a[r];
	    a[r] = t;
	    push(r);
	    push(i+1);
	    push(i-1);
	    push(l);
	    }
	else
	    insert_sort(a+l, r-l+1);  /* small sub file */
	}
    }

void quick_sort4(int a[], int n)
    {     /* remove recursion & median & small subfile insert*/
    int v, t;
    int i, j;
    int l, r;
    init_stack();
    l = 0;
    r = n-1;
    push(r);
    push(l);
    while (!is_stack_empty())
	{
	l = pop();
	r = pop();
	if (r-l+1 > 200)    /* terminal condition */
	    {
	    t = (r+l) >> 1;    /* t is middle */
	    if (a[l] > a[t])  /* sort left, middle, right */
		{
		v = a[l];
		a[l] = a[t];
		a[t] = v;
		}
	    if (a[l] > a[r])
		{
		v = a[l];
		a[l] = a[r];
		a[r] = v;
		}
	    if (a[t] > a[r])
		{
		v = a[t];
		a[t] = a[r];
		a[r] = v;
		}
	    v = a[t];    /* exchange middle with a[r-1] */
	    a[t] = a[r-1];
	    a[r-1] = v;
	    i = l;     /* partition l+1 to r-2 */
	    j = r-1;
	    while (1)      /* partition */
		{
		while (a[++i] < v);
		while (a[--j] > v);
		if (i >= j) break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
		}
	    t = a[i];
	    a[i] = a[r-1];
	    a[r-1] = t;
	    push(r);
	    push(i+1);
	    push(i-1);
	    push(l);
	    }
	else
	    insert_sort(a+l, r-l+1);  /* small sub file */
	}
    }

unsigned bits(unsigned x, int k, int j)
    {
    return (x >> k) & ~(~0 << j);
    }

/*
void radix_exchange_sort(int a[], int n, int b)
    {
    int t, i, j;
    if (n > 1  &&  b >= 0)
        {
        i = 0;
        j = n-1;
        while (i != j)
            {
            while (bits(a[i], b, 1) == 0 && i < j) i++;
            while (bits(a[j], b, 1) != 0 && i < j) j--;
            t = a[i];
            a[i] = a[j];
            a[j] = t;
            }
        if (bits(a[n-1], b, 1) == 0) j++;
        radix_exchange_sort(a, j, b-1);
        radix_exchange_sort(a+j, n-j, b-1);
        }
    }
*/
void radix_exchange_sort1(int a[], int n)
    {
    int t, i, j;
    int l, r;
    int b;
    init_stack();
    b = 15;
    l = 0;
    r = n-1;
    push(b);
    push(r);
    push(l);
    while (!is_stack_empty())
        {
        l = pop();
        r = pop();
        b = pop();
        if (r > l  &&  b >= 0)
            {
            i = l;
            j = r;
            while (1)
                {
                while (bits(a[i], b, 1) == 0 && i < j) i++;
                while (bits(a[j], b, 1) != 0 && i < j) j--;
                if (i >= j) break;
                t = a[i];
                a[i] = a[j];
                a[j] = t;
                }
            if (bits(a[r], b, 1) == 0) j++;
            push(b-1);
            push(r);
            push(j);
            push(b-1);
            push(j-1);
            push(l);
            }
        }
    }

#define W  16
#define M  4
#define MV (1 << M)

void straight_radix_sort(int a[], int n)
    {
    int i, j, pass;
    int *b, *count;
    b = (int*)malloc(sizeof(int)*n);
    count = (int*)malloc(sizeof(int)*MV);
    for (pass = 0; pass < W/M; pass++)
        {
        for (j = 0; j < MV; j++)
            count[j] = 0;
        for (i = 0; i < n; i++)
            count[bits(a[i], pass*M, M)]++;
        for (j = 1; j < MV; j++)
            count[j] = count[j] + count[j-1];
        for (i = n-1; i >= 0; i--)
            b[--count[bits(a[i], pass*M, M)]] = a[i];
        for (i = 0; i < n; i++)
            a[i] = b[i];
        }
    free(b);
    free(count);
    }

void merge_sort(int a[], int n)
    {
    int i, j, k, first, second, size;
    int *b;
    b = (int*)malloc(sizeof(int)*n);
    for (size = 1; size < n; size <<= 1)
        {
        first = -2 * size;
        second = first + size;
        while (second+size < n)
            {
            first = second + size;
            second = first + size;
            i = first;
            j = second;
            k = first;
            while (i < first+size || (j < second+size && j < n))
                {
                if (a[i] <= a[j])
                    {
                    if (i < first+size)
                        b[k++] = a[i++];
                    else
                        b[k++] = a[j++];
                    }
                else
                    {
                    if (j < second+size && j < n)
                        b[k++] = a[j++];
                    else
                        b[k++] = a[i++];
                    }
                }
            }
        for (i = 0; i < n; i++)
            a[i] = b[i];   /* memcpy(a, b, sizeof(int)*n); */
        }
    free(b);
    }

void main(void)
    {
/*    sort_test("Selection Sort", select_sort);
    sort_test("Insertion Sort", insert_sort);
    sort_test("Bubble Sort", bubble_sort);
    sort_test("Bubble Sort using sentinel", bubble_sort1); */
/*    sort_test("Shell Sort h = 2*h", shell_sort);
    sort_test("Shell Sort h = 3*h+1", shell_sort1); */
/*    sort_test("Quick Sort recursive", quick_sort);
    sort_test("Quick Sort nonrecursive ", quick_sort1);
    sort_test("Quick Sort nonrecursive & random partition", quick_sort2);
    sort_test("Quick Sort nonrecursive & random & insertion", quick_sort3);
    sort_test("Quick Sort nonrecursive & median & insertion", quick_sort4);
    sort_test("Quick Sort using library qsort()", quick_sort5);  */
/*    sort_test("Radix Exchange Sort", radix_exchange_sort); */
/*    sort_test("Radix Exchange Sort Nonrecursive", radix_exchange_sort1);*/
    sort_test("Straight Radix Sort", straight_radix_sort);
/*    sort_test("Heap Sort", heap_sort); */
    sort_test("Buttom up merge sort ", merge_sort);
    }





