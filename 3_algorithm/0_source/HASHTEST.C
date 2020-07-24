/*                                                           */
/*  HASHTEST.C  :  Hashing Example of separate chaining      */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include "schash.h"

#define TABLE_SIZE 10

int hash_func(const void *key)
    {
    int h;
    h = (*((int*)key)) % TABLE_SIZE;
    return h;
    }

int cmp_func(const void *a, const void *b)
    {
    return *(int*)a - *(int*)b;
    }

void int_prt(void *a)
    {
    printf("-> %c", *(int*)a);
    }

void interpret(node *a, int *np, int N)
    {
    char command[2];
    char key[2];
    int k;
    int p;
    while (command[0] != 'q')
        {
        printf("\nInput command ->");
        scanf("%1s", command);
	scanf("%1s", &key);
	k = key[0];
	switch (command[0])
	    {
	    case 'i' :
	    case 'I' : hsc_insert(&k, a, np, 2, cmp_func, hash_func);
		       printf("\n   Successful insert.");
		       break;
	    case 'd' :
	    case 'D' : if (hsc_delete(&k, a, np, 2, cmp_func, hash_func) == NULL)
			   printf("\n   Error : Table Empty or Can't find");
		       else
			   printf("\n   Successful delete.");
                       break;
            case 's' :
	    case 'S' : if ((p = hsc_search(&k, a, np, 2, cmp_func, hash_func)) == NULL)
			   printf("\n   Error : Can'f find that key");
		       else
			   printf("\n   Ok! find in %d th position", p);
		       break;
	    case 'l' :
	    case 'L' : hsc_list(a, N, int_prt);
		       break;
	    }
	printf("  n = %d", *np);
	}
    }

void main(void)
    {
    node *table;
    int nitem = 0;
    hsc_init(&table, &nitem, TABLE_SIZE);
    interpret(table, &nitem, TABLE_SIZE);
    hsc_deleteall(table, &nitem, TABLE_SIZE);
    free(table);
    }





