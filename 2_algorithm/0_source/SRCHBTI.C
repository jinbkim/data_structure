/*                                                           */
/*  SRCHBTI.C  :  Binary tree Searching algorithm test       */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
#include "timer.h"

#define MAX  10000

typedef struct _node
    {
    struct _node *left;
    struct _node *right;
    int key;
    } node;

node *head;

void init_list(node **p)
    {
    *p = (node*)malloc(sizeof(node));
    (*p)->left = NULL;
    (*p)->right = NULL;
    }

node *bti_search(int key, node *base, size_t *num)
    {
    node *s;
    s = base->left;
    while (key != s->key && s != NULL)
        {
        if (key < s->key)
            s = s->left;
        else
            s = s->right;
        }
    return s;
    }

node *bti_insert(int key, node *base, size_t *num)
    {
    node *p, *s;
    p = base;
    s = base->left;
    while (s != NULL)
        {
        p = s;
        if (key < s->key)
            s = s->left;
        else
            s = s->right;
        }
    if ((s = (node*)malloc(sizeof(node))) == NULL)
        return NULL;
    s->key = key;
    s->left = NULL;
    s->right = NULL;
    if (key < p->key || p == base)
        p->left = s;
    else
        p->right = s;
    (*num)++;
    return s;
    }

node *bti_delete(int key, node *base, size_t *num)
    {
    node *parent, *son, *del, *center;
    parent = base;
    del = base->left;
    while (key != del->key && del != NULL)
        {
        parent = del;
        if (key < del->key)
            del = del->left;
        else
            del = del->right;
        }
    if (del == NULL) return NULL;
    if (del->right == NULL)
        son = del->left;
    else if (del->right->left == NULL)
        {
        son = del->right;
        son->left = del->left;
        }
    else
        {
        center = del->right;
        while (center->left->left != NULL) center = center->left;
        son = center->left;
        center->left = son->right;
        son->left = del->left;
        son->right = del->right;
        }
    if (key < parent->key)
        parent->left = son;
    else
        parent->right = son;
    (*num)--;
    return parent;
    }

void _deleteall(node *t)
    {
    if (t != NULL)
        {
        _deleteall(t->left);
        _deleteall(t->right);
        free(t);
        }
    }

node *bti_deleteall(node *base, size_t *num)
    {
    node *t;
    t = base->left;
    _deleteall(t);
    base->left = NULL;
    base->right = NULL;
    *num = 0;
    return base;
    }

void bti_list(node *p)
    {
    int i;
    static int x = 0;
    if (p != NULL)
        {
        x += 2;
        bti_list(p->right);
        for (i = 2; i < x; i++) printf("   ");
        printf("%c\n", p->key);
        bti_list(p->left);
        x -= 2;
        }
    }

void bti_sort(node *p)
    {
    if (p != NULL)
        {
        bti_sort(p->left);
        printf("%c  ", p->key);
        bti_sort(p->right);
        }
    }

int _index;

void _sort(node *p, int *a)
    {
    if (p != NULL)
        {
        _sort(p->left, a);
        a[_index++] = p->key;
        _sort(p->right, a);
        }
    }

node *_balance(int n, int *a)
    {
    int nl, nr;
    node *p;
    if (n > 0)
        {
        nl = (n-1) / 2;
        nr = n - nl - 1;
        p = (node*)malloc(sizeof(node));
        p->left = _balance(nl, a);
        p->key = a[_index++];
        p->right = _balance(nr, a);
        return p;
        }
    else
        return NULL;
    }

void bti_balance(node *base, size_t *num)
    {
    int *tmp;
    int ntmp = *num;
    tmp = (int*)malloc(sizeof(int)*(ntmp));
    _index = 0;
    _sort(base->left, tmp);
    ntmp = *num;
    bti_deleteall(base, num);
    _index = 0;
    base->left = _balance(ntmp, tmp);
    *num = ntmp;
    free(tmp);
    }

void interpret(node *a, size_t *np)
    {
    char command[2];
    char key[2];
    int k;
    void *p;
    while (command[0] != 'q')
        {
        printf("\nInput command ->");
        scanf("%1s", command);
        scanf("%1s", &key);
        k = (int)key[0];
        switch (command[0])
            {
            case 'i' :
            case 'I' : if (bti_insert(k,a,np) == NULL)
                           printf("\n   Error : Out of memory.");
                       else
                           printf("\n   Successful insert.");
                       break;
            case 'd' :
            case 'D' : if (bti_delete(k,a,np) == NULL)
                           printf("\n   Error : Table empty or can't find.");
                       else
                           printf("\n   Successful delete.");
                       break;
            case 's' :
            case 'S' : if (bti_search(k,a,np) == NULL)
                           printf("\n   Error : Can'f find that key");
                       else
                           printf("\n   Ok! find ");
                       break;
            case 'l' :
            case 'L' : bti_list(a->left);
                       break;
            case 'o' :
            case 'O' : printf("\n");
                       bti_sort(a->left);
                       break;
            case 'b' :
            case 'B' : bti_balance(a, np);
                       break;
            }
        printf("  n = %d", *np);
        }
    }

void load_data(node *a, size_t width, size_t *n, int N)
    {
    FILE *fp;
    int i;
    int v;
    if ((fp = fopen("RANDOM.DAT", "rb")) == NULL)
        {
        printf("\nDisk Error!");
        exit(1);
        }
    for (i = 0; i < N; i++)
        {
        v = getw(fp);
        bti_insert(v, a, n);
        }
    fclose(fp);
    }

#define LOOP 100

void bti_test(node *a, size_t n)
    {
    int i;
    int r;
    long t1, t2;
    t1 = get_tick();
    r = random(30000);
    for (i = 0; i < LOOP; i++)
        bti_search(r, a, &n);
    t2 = get_tick();
    printf("\n lv_search %d loops ellapse %ld ticks.", LOOP, diff_tick(t1,t2));
    }

void main(void)
    {
    int *table;
    size_t nitem = 0;
    /* li_test(table, nitem); */
    init_list(&head);
    interpret(head, &nitem);
    bti_deleteall(head, &nitem);
    }






