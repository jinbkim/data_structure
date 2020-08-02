/*                                                           */
/*  LPHASH.C  :  Example of Linear probing hash              */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define TABLE_SIZE 10

int hash_func(int key)
    {
    int h;
    h = key % TABLE_SIZE;
    return h;
    }

int hlp_search(int key, int a[], int *np)
    {
    int try;
    try = hash_func(key);
    while (a[try] != -1)
	{
	if (a[try] == key) return try;
	try = (try+1) % TABLE_SIZE;   /* linear probing */
	}
    return -1;
    }

int hlp_insert(int key, int a[], int *np)
    {
    int try;
    try = hash_func(key);
    while (a[try] != -1) try = (try+1) % TABLE_SIZE;
    a[try] = key;
    (*np)++;
    return try;
    }

int hlp_init(int a[], int *np)
    {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) a[i] = -1;
    *np = 0;
    return 1;
    }

int hlp_list(int a[])
    {
    int i;
    for (i = 0; i < TABLE_SIZE; i++)
	printf("\n%d : %c", i, a[i]);
    return 1;
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
			   hlp_insert(key[0], a, np);
			   printf("\n   Successful insert.");
			   }
		       else
			   printf("\n   Error : Table full.");
		       break;
	    case 'd' :
	    case 'D' : if (hlp_init(a, np) < 0)
			   printf("\n   Error : Table Empty.");
		       else
			   printf("\n   Successful delete.");
                       break;
            case 's' :
	    case 'S' : if ((p = hlp_search(key[0], a, np)) < 0)
			   printf("\n   Error : Can'f find that key");
		       else
			   printf("\n   Ok! find in %d th position", p);
		       break;
	    case 'l' :
	    case 'L' : hlp_list(a);
		       break;
	    }
	printf("  n = %d", *np);
	}
    }

void main(void)
    {
    int *table;
    int nitem = 0;
    table = (int*)malloc(sizeof(int)*TABLE_SIZE);
    hlp_init(table, &nitem);
    interpret(table, &nitem, TABLE_SIZE);
    free(table);
    }





