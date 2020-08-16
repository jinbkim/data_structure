/*                                                           */
/*  SRCHLLV.C  :   Linear Search Linked list version         */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define MAX  10000

typedef int (*FCMP)(const void*, const void*);

typedef struct _node { struct _node *next; } node;

node *head, *tail;

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

void llv_list(node *p)
    {
    p = p->next;
    printf("\n");
    while (p->next != NULL)
        {
        printf("%6c", *(int*)(p+1));
        p = p->next;
        }
    }

int intcmp(const void *a, const void *b)
    {
    return *(int*)a - *(int*)b;
    }

void interpret(node *a, size_t *np)
    {
    char command[2];
    char key[2];
    int k;
    size_t w;
    void *p;
    w = sizeof(int);
    while (command[0] != 'q')
        {
        printf("\nInput command ->");
        scanf("%1s", command);
        scanf("%1s", &key);
        k = (int)key[0];
        switch (command[0])
            {
            case 'i' :
            case 'I' : if (llv_insert(&k,a,np,w,intcmp) == NULL)
                           printf("\n   Error : Out of memory.");
                       else
                           printf("\n   Successful insert.");
                       break;
            case 'd' :
            case 'D' : if (llv_delete(&k,a,np,w,intcmp) == NULL)
                           printf("\n   Error : Table empty or can't find.");
                       else
                           printf("\n   Successful delete.");
                       break;
            case 's' :
            case 'S' : if (llv_search(&k,a,np,w,intcmp) == NULL)
                           printf("\n   Error : Can'f find that key");
                       else
                           printf("\n   Ok! find ");
                       break;
            case 'f' :
            case 'F' : if (llfv_search(&k,a,np,w,intcmp) == NULL)
                           printf("\n   Error : Can't find that key");
                       else
                           printf("\n   Ok ! find ");
                       break;
            case 'l' :
            case 'L' : llv_list(a);
                       break;
            }
        printf("  n = %d", *np);
        }
    }

void load_data(node *a, size_t width, size_t *n, int N)
    {
    FILE *fp;
    int i;
    void *v;
    if ((fp = fopen("RANDOM.DAT", "rb")) == NULL)
        {
        printf("\nDisk Error!");
        exit(1);
        }
    v = malloc(width);
    for (i = 0; i < N; i++)
        {
        fread(v, 1, width, fp);
        llv_insert(v, a, n, width, NULL);
        }
    fclose(fp);
    free(v);
    }

#define LOOP 100

void llv_test(node *a, size_t n)
    {
    int i;
    int r;
    long t1, t2;
    t1 = get_tick();
    r = random(30000);
    for (i = 0; i < LOOP; i++)
        llv_search((void*)&r, a, &n, sizeof(int), intcmp);
    t2 = get_tick();
    printf("\n lv_search %d loops ellapse %ld ticks.", LOOP, diff_tick(t1,t2));
    t1 = get_tick();
    r = random(30000);
    for (i = 0; i < LOOP; i++)
        llfv_search((void*)&r, a, &n, sizeof(int), (FCMP)intcmp);
    t2 = get_tick();
    printf("\n lfv_search %d loops ellapse %ld ticks.", LOOP, diff_tick(t1,t2));
    }

void main(void)
    {
    int *table;
    size_t nitem = 0;
    /* li_test(table, nitem); */
    init_list(&head, &tail);
    interpret(head, &nitem);
    llv_deleteall(head, tail);
    }





