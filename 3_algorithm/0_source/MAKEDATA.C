/*                                                           */
/*  MAKEDATA.C  :   Make data file for Sort & Search         */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

void main(void)
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








