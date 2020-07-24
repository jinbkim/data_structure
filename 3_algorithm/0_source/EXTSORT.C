/*                                                           */
/*  EXTSORT.C  :  External Sort Alogorithm Test              */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <alloc.h>
#include "timer.h"

typedef int (*FCMP)(const void*, const void*);
typedef void (*ESFNC)(FILE*,FILE*,size_t,void*,size_t,FCMP);

int intcmp(const void *a, const void *b)
    {
    return (*(int*)a - *(int*)b);
    }

int is_sorted(FILE *fp)
    {
    int sorted = 1;
    int i;
    int n;
    int t1, t2;
    fseek(fp, 0L, SEEK_END);
    n = (int)(ftell(fp) / sizeof(int));
    rewind(fp);
    t1 = getw(fp);
    for (i = 0; i < n-1; i++)
	{
        t2 = getw(fp);
	if (t1 > t2)
	    return !sorted;
        t1 = t2;
	}
    return sorted;
    }

#define BUFSIZE  4098

void sort_test(ESFNC sort_func)
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
    for (i = 3; i >=0; i--)
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
        printf("\n    Sorting %s in %ld ticks. %s", fn[i], t,
                    is_sorted(dst) ? "Ok" : "fails");

        rewind(dst);
        printf("\n");
        while (1)
            {
            if (fread(buf, sizeof(int), 1, dst) == 0)
                break;
            printf("%8d", *(int*)buf);
            }

        fclose(src);
        fclose(dst);
        }
    free(buf);
    }

void shell_sort(void *base, size_t nelem, size_t width, FCMP fcmp)
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

struct entry
    {
    FILE *fp;
    char fname[13];
    void *v;
    int is_eof;
    };

void external_sort(FILE *src, FILE *dst, size_t width,
                   void *buf, size_t buflen, FCMP fcmp)
    {
    int i, minindex, done;
    int nelem, nbuf, nfile;
    void *min;
    struct entry *tmp;

    min = malloc(width);

    fseek(src, 0L, SEEK_END);
    nelem = (int)(ftell(src) / width);
    nbuf = buflen / width;
    nfile = nelem/nbuf + 1;

    printf("\n Records of File : %d"
           "\n Records of Buffer : %d"
           "\n Number of File : %d", nelem, nbuf, nfile);

    tmp = (struct entry*)malloc(sizeof(struct entry) * nfile);
    for (i = 0; i < nfile; i++)
        {
        sprintf(tmp[i].fname, "%d.TMP", i);
        tmp[i].fp = fopen(tmp[i].fname, "wb");
        tmp[i].v = malloc(width);
        tmp[i].is_eof = 0;
        }

    fseek(src, 0L, SEEK_SET);
    for (i = 0; i < nfile-1; i++)
        {
        fread(buf, width, nbuf, src);
        shell_sort(buf, nbuf, width, fcmp);
        fwrite(buf, width, nbuf, tmp[i].fp);

        printf("\n Reading & Sorting & Writing %s.", tmp[i].fname);

        }
    fread(buf, width, nelem%nbuf, src);
    shell_sort(buf, nelem%nbuf, width, fcmp);
    fwrite(buf, width, nelem%nbuf, tmp[i].fp);

    printf("\n Reading & Sorting & Writing %s.", tmp[i].fname);

    for (i = 0; i < nfile; i++)
        {
        rewind(tmp[i].fp);
        if (fread(tmp[i].v, width, 1, tmp[i].fp) == 0)
            tmp[i].is_eof = 1;
        }
    rewind(dst);

    printf("\n Now merging...");

    while (1)
        {
        done = 1;
        for (i = 0; i < nfile; i++)
            if (!tmp[i].is_eof) done = 0;
        if (done) break;
        i = 0;
        while (tmp[i].is_eof) i++;
        minindex = i;
        memcpy(min, tmp[minindex].v, width);
        while (++i < nfile)
            {
            if (!tmp[i].is_eof && fcmp(min, tmp[i].v) > 0)
                {
                minindex = i;
                memcpy(min, tmp[i].v, width);
                }
            }
        fwrite(tmp[minindex].v, width, 1, dst);
        if (fread(tmp[minindex].v, width, 1, tmp[minindex].fp) == 0)
            tmp[minindex].is_eof = 1;
        }

    printf(" Completed. \n Deleting Temporary files...");

    for (i = 0; i < nfile; i++)
        {
        fclose(tmp[i].fp);
        unlink(tmp[i].fname);
        free(tmp[i].v);
        }
    free(min);
    free(tmp);
    }

void main(void)
    {
    sort_test(external_sort);
    }





