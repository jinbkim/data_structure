/*                                                           */
/*  SORTEXT.C  :   Sorting text demonstration                */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <limits.h>

#define LEN  20

int *base;

char *str = "TOLEARNSORTALGORITHM";

void print_array(int *a, int n)
    {
    int i;
    printf("\n    ");
    for (i = 0; i < n; i++)
	printf("%c  ", a[i]);
    }

void set_array(int *a)
    {
    int i;
    for (i = 0; i < LEN; i++)
        a[i] = (int)str[i];
    }

void t_select_sort(int a[], int n)
    {
    int min;
    int minindex;
    int i, j;

    printf("\nSelection Sort");
    for (i = 0; i < n-1; i++)
	{
	print_array(a, LEN);
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

void t_insert_sort(int a[], int n)
    {
    int i, j, t;
    printf("\nInsertion Sort");
    for (i = 1; i < n; i++)
	{
	print_array(a, LEN);
	t = a[i];
	j = i;
	while (a[j-1] > t && j > 0)
	    {
	    a[j] = a[j-1];
	    j--;
	    }
	a[j] = t;
	}
	print_array(a, LEN);
    }

void t_bubble_sort(int a[], int n)
    {
    int i, j, t;
    printf("\nBubble Sort");
    for (i = 0; i < n-1; i++)
	{
	print_array(a, LEN);
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

void t_shell_sort(int a[], int n)
    {
    int i, j, k, h, v;
    printf("\nShell Sort");
    for (h = n/2; h > 0; h /= 2)
	{
	for (i = 0; i < h; i++)
	    {
	    for (j = i+h; j < n; j += h)
		{
		v = a[j];
		k = j;
		print_array(a, LEN);
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

void t_quick_sort(int a[], int n)
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
	    print_array(base, LEN);
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
	t_quick_sort(a, i);
	t_quick_sort(a+i+1, n-i-1);
	}
    }

void t_merge_sort(int a[], int n)
    {
    int i, j, k, first, second, size;
    int *b;
    printf("\nMerge Sort");
    print_array(a, LEN);
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
        print_array(a, LEN);
        }
    free(b);
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

void t_heap_sort(int a[], int n)
    {    /* top-down heap sort */
    int i;
    int hn = 0;
    printf("\nHeap Sort top-down construction ");
    for (i = 1; i <= n; i++)
        {
        print_array(a+1, LEN);
        insert(a, &hn, a[i]);
        }
    for (i = hn; i >= 1; i--)
        {
        print_array(a+1, LEN);
        a[i] = extract(a, &hn);
        }
    }

void main(void)
    {
    int *a;

    if ((a = (int*)malloc(sizeof(int)*(LEN+1))) == NULL)
        {
        printf("\nOut of memory");
        return;
        }

		      /*
    set_array(a);
    t_select_sort(a, LEN);

    set_array(a);
    t_insert_sort(a, LEN);

    set_array(a);
    t_bubble_sort(a, LEN);

    set_array(a);
    t_bubble_sort(a, LEN);

    set_array(a);
    t_shell_sort(a, LEN);
			*/
    set_array(a);
    base = a;
    t_quick_sort(a, LEN);

    set_array(a);
    t_merge_sort(a, LEN);

    set_array(a+1);
    t_heap_sort(a, LEN);
    }






