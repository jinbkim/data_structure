/*                                                           */
/*  JOSHEP.C  :  Joshep's problem using circular linked list */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>

typedef struct _node
    {
    int key;
    struct _node *next;
    } node;

node *head;

void insert_nodes(int k)
    {       /* insert nodes reverse order k to 1 */
    node *t;
    int i;
    t = (node*)malloc(sizeof(node));
    t->key = 1;
    head = t;
    for (i = 2; i <= k; i++)
       {    /* construct circular linked list */
       t->next = (node*)malloc(sizeof(node));
       t = t->next;
       t->key = i;
       }
    t->next = head;
    }

void delete_after(node *t)
    {     /* delete node after t */
    node *s;
    s = t->next;
    t->next = t->next->next;  /* delete after t */
    free(s);
    }

void josephus(int n, int m)
    {   /* solve josephus problem, n nodes, step m */
    node *t;
    int i;
    insert_nodes(n);
    t = head;
    printf("\nAnswer : ");
    while (t != t->next)
	{
	for (i = 0; i < m-1; i++)
	    t = t->next;
	printf("%d  ", t->next->key);
	delete_after(t);
	}
    printf("%d", t->key);  /* print last node */
    }

void main(void)
    {
    int n, m;
    printf("\nIf you want to quit, enter 0 or minus value");
    while (1)
	{
	printf("\nEnter N and M -> ");
	scanf("%d %d", &n, &m);
	if (n <= 0 || m <= 0)
	    return;
	josephus(n, m);
	}
    }









