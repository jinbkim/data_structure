/*                                                           */
/*  SORTGEN.C  :  Sorting algorithm general version          */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <alloc.h>
#include <string.h>
#include <bios.h>
#include <stdlib.h>
#include <mem.h>
#include "timer.h"

#define SORTED   0
#define RANDOM   1
#define HALFSO   2
#define REVERS   3

#define MAX  20000
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

int intcmp(const void *a, const void *b)
    {
    return (*(int*)a - *(int*)b);
    }

long sort_testnm(int n, int m,
     void (*sort_func)(void*,size_t,size_t,int(*)(const void*,const void*)))
    {
    long t1, t2, t;
    int *a;
    a = set_array(a, n, m);
    t1 = get_tick();
    sort_func(a, n, sizeof(int), intcmp);
    t2 = get_tick();
    t = diff_tick(t1, t2);
    if (!is_sorted(a, n))
	t = -1;
    free(a);
    return t;
    }

void sort_testn(int n,
     void (*sort_func)(void*,size_t,size_t,int(*)(const void*,const void*)))
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

void sort_test(char *name,
     void (*sort_func)(void*,size_t,size_t,int(*)(const void*,const void*)))
    {
    int n[] =
	 { 10, 100, 500, 1000, 2000, -1}; /*
	   3000, 4000, 5000 };  6000, 7000, 8000,
           9000, 10000, -1 };  */
    int i = 0;
    printf("\n%s",name);
    while (n[i] > 0)
        sort_testn(n[i++], sort_func);
    }

void select_sort(void *base, size_t nelem, size_t width,
     int (*fcmp)(const void*, const void*))
    {
    void *min;
    int minindex;
    int i, j;

    min = malloc(width);
    for (i = 0; i < nelem - 1; i++)
	{
	minindex = i;
	memcpy(min, (char*)base + i*width, width);
	for (j = i + 1; j < nelem; j++)
	    {
	    if (fcmp(min, (char*)base + j*width) > 0)
		{
		memcpy(min, (char*)base + j*width, width);
		minindex = j;
		}
	    }
	memcpy((char*)base + minindex*width, (char*)base + i*width, width);
	memcpy((char*)base + i*width, min, width);
	}
    free(min);
    }

void insert_sort(void*base, size_t nelem, size_t width,
		 int (*fcmp)(const void*, const void*))
    {
    int i, j;
    void *t;
    t = malloc(width);
    for (i = 1; i < nelem; i++)
	{
	memcpy(t, (char*)base + i*width, width);
	j = i;
	while (fcmp((char*)base + (j-1)*width, t) > 0  &&  j > 0)
	    {
	    memcpy((char*)base + j*width, (char*)base + (j-1)*width, width);
	    j--;
	    }
	memcpy((char*)base + j*width, t, width);
	}
    free(t);
    }

void bubble_sort(void *base, size_t nelem, size_t width,
		 int (*fcmp)(const void*, const void*))
    {
    int i, j, s;
    void *t;
    t = malloc(width);
    for (i = 0; i < nelem-1; i++)
	{
	s = 0;
	for (j = 1; j < nelem-i; j++)
	    {
	    if (fcmp((char*)base + (j-1)*width, (char*)base + j*width) > 0)
		{
		memcpy(t, (char*)base + (j-1)*width, width);
		memcpy((char*)base + (j-1)*width, (char*)base + j*width, width);
		memcpy((char*)base + j*width, t, width);
		s = 1;
		}
	    }
	if (s == 0) break;
	}
    free(t);
    }

void shell_sort(void *base, size_t nelem, size_t width,
		int (*fcmp)(const void*,const void*))
    {
    int i, j, k, h;
    void *v;
    v = malloc(width);
    for (h = 1; h < nelem; h = 3*h+1);
    for (h /= 3; h > 0; h /= 3)
	{
	for (i = 0; i < h; i++)
	    {
	    for (j = i+h; j < nelem; j += h)
		{
		memcpy(v, (char*)base + j*width, width);
		k = j;
		while (k > h-1 && fcmp((char*)base+(k-h)*width, v) > 0)
		    {
		    memcpy((char*)base+k*width,(char*)base+(k-h)*width,width);
		    k -= h;
		    }
		memcpy((char*)base+k*width, v, width);
		}
	    }
	}
    free(v);
    }

void quick_sort1(void *base, size_t nelem, size_t width,
		int (*fcmp)(const void*, const void*))
    {     /* remove recursion & median & small subfile insert*/
    void *v, *u;
    int i, j, t;
    int l, r;
    init_stack();
    v = malloc(width);
    u = malloc(width);
    l = 0;
    r = nelem-1;
    push(r);
    push(l);
    while (!is_stack_empty())
	{
	l = pop();
	r = pop();
	if (r-l+1 > 100)    /* terminal condition */
	    {
	    t = (r+l) >> 1;    /* t is middle */
	    if (fcmp((char*)base+l*width, (char*)base+t*width) > 0)  /* sort left, middle, right */
		{
		memcpy(v, (char*)base+l*width, width);
		memcpy((char*)base+l*width, (char*)base+t*width, width);
		memcpy((char*)base+t*width, v, width);
		}
	    if (fcmp((char*)base+l*width, (char*)base+r*width) > 0)  /* sort left, middle, right */
		{
		memcpy(v, (char*)base+l*width, width);
		memcpy((char*)base+l*width, (char*)base+r*width, width);
		memcpy((char*)base+r*width, v, width);
		}
	    if (fcmp((char*)base+t*width, (char*)base+r*width) > 0)  /* sort left, middle, right */
		{
		memcpy(v, (char*)base+t*width, width);
		memcpy((char*)base+t*width, (char*)base+r*width, width);
		memcpy((char*)base+r*width, v, width);
		}
	    memcpy(v, (char*)base+t*width, width);    /* exchange middle with a[r-1] */
	    memcpy((char*)base+t*width, (char*)base+(r-1)*width, width);
	    memcpy((char*)base+(r-1)*width, v, width);
	    i = l;     /* partition l+1 to r-2 */
	    j = r-1;
	    while (1)      /* partition */
		{
		while (fcmp((char*)base+(++i)*width, v) < 0);
		while (fcmp((char*)base+(--j)*width, v) > 0);
		if (i >= j) break;
		memcpy(u, (char*)base+i*width, width);
		memcpy((char*)base+i*width, (char*)base+j*width, width);
		memcpy((char*)base+j*width, u, width);
		}
	    memcpy(u, (char*)base+i*width, width);
	    memcpy((char*)base+i*width, (char*)base+(r-1)*width, width);
	    memcpy((char*)base+(r-1)*width, u, width);
	    push(r);
	    push(i+1);
	    push(i-1);
	    push(l);
	    }
	else
	    insert_sort((char*)base+l*width, r-l+1, width, fcmp);  /* small sub file */
	}
    free(u);
    free(v);
    }

void quick_sort2(void *base, size_t nelem, size_t width,
		int (*fcmp)(const void*, const void*))
    {     /* remove recursion & random & small subfile insert*/
    void *v, *u;
    int i, j, t;
    int l, r;
    init_stack();
    v = malloc(width);
    u = malloc(width);
    l = 0;
    r = nelem-1;
    push(r);
    push(l);
    while (!is_stack_empty())
	{
	l = pop();
	r = pop();
	if (r-l+1 > 100)    /* terminal condition */
	    {
	    t = random(r-l+1) + l;    /* t is random */
	    memcpy(v, (char*)base+t*width, width);    /* exchange random with a[r] */
	    memcpy((char*)base+t*width, (char*)base+r*width, width);
	    memcpy((char*)base+r*width, v, width);
	    i = l-1;     /* partition l to r-1 */
	    j = r;
	    while (1)      /* partition */
		{
		while (fcmp((char*)base+(++i)*width, v) < 0);
		while (fcmp((char*)base+(--j)*width, v) > 0);
		if (i >= j) break;
		memcpy(u, (char*)base+i*width, width);
		memcpy((char*)base+i*width, (char*)base+j*width, width);
		memcpy((char*)base+j*width, u, width);
		}
	    memcpy(u, (char*)base+i*width, width);
	    memcpy((char*)base+i*width, (char*)base+r*width, width);
	    memcpy((char*)base+r*width, u, width);
	    push(r);
	    push(i+1);
	    push(i-1);
	    push(l);
	    }
	else
	    insert_sort((char*)base+l*width, r-l+1, width, fcmp);  /* small sub file */
	}
    free(u);
    free(v);
    }

void merge_sort(void *base, size_t nelem, size_t width,
                int (*fcmp)(const void*, const void*))
    {
    int i, j, k, first, second, size;
    void *b;
    if ((b = malloc(width*nelem)) == NULL)
        {
        printf("\nOut of memory error!");
        return;
        }
    for (size = 1; size < nelem; size <<= 1)
        {
        first = -2 * size;
        second = first + size;
        while (second+size < nelem)
            {
            first = second + size;
            second = first + size;
            i = first;
            j = second;
            k = first;
            while (i < first+size || (j < second+size && j < nelem))
                {
                if (fcmp((char*)base+i*width, (char*)base+j*width) <= 0)
                    {
                    if (i < first+size)
                        memcpy((char*)b+(k++)*width, (char*)base+(i++)*width,
                               width);
                    else
                        memcpy((char*)b+(k++)*width, (char*)base+(j++)*width,
                               width);
                    }
                else
                    {
                    if (j < second+size && j < nelem)
                         memcpy((char*)b+(k++)*width, (char*)base+(j++)*width,
                               width);
                    else
                         memcpy((char*)b+(k++)*width, (char*)base+(i++)*width,
                               width);
                    }
                }
            }
        memcpy(base, b, nelem*width);
        }
    free(b);
    }

void downheap(void *base, size_t nelem, size_t width,
              int (*fcmp)(const void*,const void*), int k)
    {
    int i;
    void *v;
    v = malloc(width);
    memcpy(v, (char*)base+(k-1)*width, width);
    while (k <= nelem/2)
        {
        i = k<<1;
        if (i<nelem && fcmp((char*)base+(i-1)*width,(char*)base+i*width)<0)
            i++;
        if (fcmp(v, (char*)base+(i-1)*width) >= 0)
            break;
        memcpy((char*)base + (k-1)*width, (char*)base + (i-1)*width, width);
        k = i;
        }
    memcpy((char*)base + (k-1)*width, v, width);
    free(v);
    }

void heap_sort(void *base, size_t nelem, size_t width,
               int (*fcmp)(const void*, const void*))
    {
    int k;
    void *t;
    t = malloc(width);
    for (k = nelem/2; k >= 1; k--)
        downheap(base, nelem, width, fcmp, k);
    while (nelem > 1)
        {
        memcpy(t, base, width);
        memcpy(base, (char*)base + (nelem-1)*width, width);
        memcpy((char*)base + (nelem-1)*width, t, width);
        downheap(base, --nelem, width, fcmp, 1);
        }
    free(t);
    }

void main(void)
    {
/*    sort_test("Selection Sort", select_sort); */
/*    sort_test("Insertion Sort", insert_sort); */
/*    sort_test("Bubble Sort", bubble_sort);  */
    sort_test("Shell Sort", shell_sort);
    sort_test("Quick Sort using median", quick_sort1);
    sort_test("Quick Sort using random", quick_sort2);
    sort_test("Merge Sort buttom-up", merge_sort);
    sort_test("Heap Sort buttom-up", heap_sort);
    }





