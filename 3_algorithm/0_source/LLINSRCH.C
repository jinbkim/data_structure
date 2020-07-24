/*                                                           */
/*  LLINSRCH.C  :   Linear Search Linked list version         */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>

typedef int (*FCMP)(const void*, const void*);

typedef struct _node { struct _node *next; } node;

void init_list(node **p, node **q)
    {
    *p = (node*)malloc(sizeof(node));
    *q = (node*)malloc(sizeof(node));
    (*p)->next = *q;
    (*q)->next = NULL;
    }

void *llv_search(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    node *t;
    t = base->next;
    while (fcmp(t+1, key) != 0 && t->next != NULL) t = t->next;
    return (t->next == NULL ? NULL : t+1);
    }

void *llv_insert(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    node *t;
    if ((t = (node*)malloc(sizeof(node)+width)) == NULL)
        return NULL;
    memcpy(t+1, key, width);
    t->next = base->next;
    base->next = t;
    (*num)++;
    return t+1;
    }

void *llv_delete(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    node *t, *p;
    if (base->next->next != NULL)
        {
        if ((t = (node*)llv_search(key, base, num, width, fcmp)) == NULL)
            return NULL;
        t = t-1;
        p = base;
        while (p->next != t) p = p->next;
        p->next = t->next;
        free(t);
        (*num)--;
        return p;
        }
    return NULL;
    }

void *llfv_search(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    void *v;
    void *f;
    if ((v = llv_search(key, base, num, width, fcmp)) == NULL)
        return NULL;
    f = malloc(width);
    memcpy(f, v, width);
    llv_delete(key, base, num, width, fcmp);
    v = llv_insert(f, base, num, width, fcmp);
    free(f);
    return v;
    }

void *llv_deleteall(node *base, node *end)
    {
    node *t, *s;
    t = base->next;
    while (t->next != NULL)
        {
        s = t;
        t = t->next;
        free(s);
        }
    base->next = end;
    return base;
    }






