/*                                                           */
/*  SORTDEMO.C  :  Demonstration for Sort Library            */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "timer.h"

#define SORTED  0
#define RANDOM  1
#define HALFSO  2
#define REVERS  3

typedef void (*SORTFNC)(void*,size_t,size_t,FCMP);
typedef void (*ESFNC)(FILE*,FILE*,size_t,void*,size_t,FCMP);

int intcmp(const void *a, const void *b)
    {
    return (*(int*)a - *(int*)b);
    }

void set_array(int *a, int n, int m)
    {
    int i;
    char *fname[] =
        { "ASCEND.DAT", "RANDOM.DAT", "HALFSORT.DAT", "DESCEND.DAT"};
    FILE *fp;

    if ((fp = fopen(fname[m], "rb")) == NULL)
        {
        printf("\nFile reading error!");
        return;
        }
    fread(a, sizeof(int), n, fp);
    fclose(fp);
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

long sort_testnm(int n, int m, SORTFNC sort_func)
    {
    long t1, t2, t;
    int *a;
    if ((a = (int*)malloc(sizeof(int)*n)) == NULL)
        {
        printf("\nOut of Memory...");
        exit(1);
        }
    set_array(a, n, m);
    t1 = get_tick();
    sort_func(a, n, sizeof(int), intcmp);
    t2 = get_tick();
    t = diff_tick(t1, t2);
    if (!is_sorted(a, n))
	t = -1;
    free(a);
    return t;
    }

void sort_testn(int n, SORTFNC sort_func)
    {
    long t;
    int i;
    printf("\n    %6d", n);
    for (i = SORTED; i <= REVERS; i++)
        {
        t = sort_testnm(n, i, sort_func);
        printf("  %10ld", t);
        }
    }

void sort_test(char *name, SORTFNC sort_func)
    {
    int n[] =
	 { 10, 100, 500, 1000, 2000, 5000, 7000, 10000, -1};
    int i = 0;
    printf("\n*** %s"
           "\n      N     Sorted      Random      Half-sorted Reversed"
           "\n    ------  ----------  ----------  ----------  ----------"
           , name);
    while (n[i] > 0)
        sort_testn(n[i++], sort_func);
    printf("\n");
    }

#define MAX 10000

void make_data(void)
    {
    FILE *fp;
    int i;

    if ((fp = fopen("ASCEND.DAT", "wb")) == NULL)
        {
        printf("\n Disk Error !");
        exit(1);
        }
    printf("\n Creating ascending file ...");
    for (i = 1; i <= MAX; i++)
        putw(i, fp);
    fclose(fp);

    if ((fp = fopen("DESCEND.DAT", "wb")) == NULL)
        {
        printf("\n Disk Error !");
        exit(1);
        }
    printf("\n Creating descending file ...");
    for (i = MAX; i > 0; i--)
        putw(i, fp);
    fclose(fp);

    if ((fp = fopen("RANDOM.DAT", "wb")) == NULL)
        {
        printf("\n Disk Error !");
        exit(1);
        }
    printf("\n Creating random file ...");
    for (i = 0; i < MAX; i++)
        putw(random(MAX) + 1, fp);
    fclose(fp);

    if ((fp = fopen("HALFSORT.DAT", "wb")) == NULL)
        {
        printf("\n Disk Error!");
        exit(1);
        }
    printf("\n Creating half-sorted file ...");
    for (i = 0; i < MAX; i++)
        {
        if (i % 3)
            putw(random(MAX) + 1, fp);
        else
            putw(i, fp);
        }
    }

#define BUFSIZE  8192

void external_sort_test(ESFNC sort_func)
    {
    long t1, t2, t;
    void *buf;
    FILE *src, *dst;
    char *fn[] =
        { "ASCEND.DAT", "DESCEND.DAT", "RANDOM.DAT", "HALFSORT.DAT" };
    int i;
    if ((buf = malloc(BUFSIZE)) == NULL)
        {
        printf("Out of memory");
        exit(1);
        }

    printf("\n*** External Sort"
           "\n      N     Sorted      Random      Half-sorted Reversed"
           "\n    ------  ----------  ----------  ----------  ----------");
    printf("\n    %6d", MAX);

    for (i = 0; i < 4; i++)
        {
        if ((src = fopen(fn[i], "rb")) == NULL)
            {
            printf("\nDisk Error!");
            exit(1);
            }
        if ((dst = fopen("RESULT.DAT", "wb")) == NULL)
            {
            printf("\nDisk Error!");
            exit(1);
            }
        t1 = get_tick();
        sort_func(src, dst, sizeof(int), buf, BUFSIZE, intcmp);
        t2 = get_tick();
        t = diff_tick(t1, t2);
        printf("  %10ld", t);
        fclose(src);
        fclose(dst);
        }
    free(buf);
    }


void main(void)
    {
    make_stack();
    make_data();
    sort_test("Seletion Sort", select_sort);
    sort_test("Insertion Sort", insert_sort);
    sort_test("Bubble Sort", bubble_sort);
    sort_test("Shell Sort", shell_sort);
    sort_test("Quick Sort1 : using median", quick_sort1);
    sort_test("Quick Sort2 : using random", quick_sort2);
    sort_test("Quick Sort : using qsort()", qsort);
    sort_test("Merge Sort", merge_sort);
    sort_test("Heap Sort", heap_sort);
    external_sort_test(external_sort);
    remove_stack();
    }






