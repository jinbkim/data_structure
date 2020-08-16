/*                                                           */
/*  SCHASH.C  :  Hashing Library  of separate chaining       */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <mem.h>
#include <stdlib.h>

typedef int (*FCMP)(const void*,const void*);
typedef int (*HASH)(const void*);

typedef struct _node
    {
    struct _node *next;
    } node;

node *hsc_init(node **base, size_t *num, size_t N)
    {
    int i;
    if ((*base = (node*)malloc(sizeof(node)*N)) == NULL)
	return NULL;
    for (i = 0; i < N; i++)
	(*base)[i].next = NULL;
    *num = 0;
    return *base;
    }

node *hsc_deleteall(node *base, size_t *num, size_t N)
    {
    node *t, *p;
    int i;
    for (i = 0; i < N; i++)
	{
	t = base[i].next;
	while (t != NULL)
	    {
	    p = t;
	    t = t->next;
	    free(p);
	    }
	base[i].next = NULL;
	}
    *num = 0;
    return base;
    }

void *hsc_search(void *key, node *base, size_t *num, size_t width,
		 FCMP fcmp, HASH hash)
    {
    node *t;
    t = base[hash(key)].next;
    while (t != NULL && fcmp(key, t+1) != 0)
	t = t->next;
    if (t == NULL) return NULL;
    else return t+1;
    }

void *hsc_insert(void *key, node *base, size_t *num, size_t width,
		 FCMP fcmp, HASH hash)
    {
    int try;
    node *t;
    if ((t = (node*)malloc(sizeof(node)+width)) == NULL)
	return NULL;
    try = hash(key);
    t->next = base[try].next;
    memcpy(t+1, key, width);
    base[try].next = t;
    (*num)++;
    return t+1;
    }

void *hsc_delete(void *key, node *base, size_t *num, size_t width,
		 FCMP fcmp, HASH hash)
    {
    node *p;
    node *t;
    if (*num > 0)
	{
	p = &base[hash(key)];
	t = p->next;
	while (t != NULL && fcmp(key, t+1) != 0)
	    {
	    p = t;
	    t = t->next;
	    }
	if (t == NULL) return NULL;
	p->next = t->next;
	free(t);
	(*num)--;
	return p+1;
	}
    return NULL;
    }

void hsc_list(node *base, int N, void (*fprt)(void*))
    {
    int i;
    node *t;
    for (i = 0; i < N; i++)
	{
	printf("\nBucket %d :", i);
	t = base[i].next;
	while (t != NULL)
	    {
	    fprt(t+1);
	    t = t->next;
	    }
	}
    }


