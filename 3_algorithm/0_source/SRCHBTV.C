/*                                                           */
/*  SRCHBTV.C  :  Binary tree Searching Library              */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
#include <graphics.h>
#include "hardcopy.h"

#define MAX  10000

#define BASE(i) ((char*)base + (i)*width)

typedef int (*FCMP)(const void*, const void*);

typedef struct _node
    {
    struct _node *left;
    struct _node *right;
    } node;

node *head;

void init_list(node **p)
    {
    *p = (node*)malloc(sizeof(node));
    (*p)->left = NULL;
    (*p)->right = NULL;
    }

void *btv_search(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    node *s;
    s = base->left;
    while (fcmp(key, s+1) != 0 && s != NULL)
        {
        if (fcmp(key, s+1) < 0)
            s = s->left;
        else
            s = s->right;
        }
    if (s == NULL) return NULL;
    else return s+1;
    }

void *btv_insert(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    node *p, *s;
    p = base;
    s = base->left;
    while (s != NULL)
        {
        p = s;
        if (fcmp(key, s+1) < 0)
            s = s->left;
        else
            s = s->right;
        }
    if ((s = (node*)malloc(sizeof(node) + width)) == NULL)
        return NULL;
    memcpy(s+1, key, width);
    s->left = NULL;
    s->right = NULL;
    if (fcmp(key, p+1) < 0 || p == base)
        p->left = s;
    else
        p->right = s;
    (*num)++;
    return s;
    }

void *btv_delete(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    node *parent, *son, *del, *nexth;
    parent = base;
    del = base->left;
    while (fcmp(key, del+1) != 0 && del != NULL)
        {
        parent = del;
        if (fcmp(key, del+1) < 0)
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
	nexth = del->right;
	while (nexth->left->left != NULL) nexth = nexth->left;
	son = nexth->left;
	nexth->left = son->right;
	son->left = del->left;
	son->right = del->right;
	}
    if (fcmp(key, parent+1) < 0 || parent == base)
        parent->left = son;
    else
	parent->right = son;
    free(del);
    (*num)--;
    return parent;
    }

void *btv_delete1(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    node *parent, *son, *del, *nexth;
    parent = base;
    del = base->left;
    while (fcmp(key, del+1) != 0 && del != NULL)
        {
        parent = del;
        if (fcmp(key, del+1) < 0)
            del = del->left;
        else
            del = del->right;
        }
    if (del == NULL) return NULL;
    if (del->left == NULL && del->right == NULL) son = NULL;
    else if (del->left != NULL && del->right != NULL)
	{
	nexth = del->right;
	if (nexth->left != NULL)
	    {
	    while (nexth->left->left != NULL) nexth = nexth->left;
	    son = nexth->left;
	    nexth->left = son->right;
	    son->left = del->left;
	    son->right = del->right;
	    }
	else
	    {
	    son = nexth;
	    son->left = del->left;
	    }
	}
    else
	{
	if (del->left != NULL) son = del->left;
	else son = del->right;
	}
    if (fcmp(key, parent+1) < 0 || parent == base)
        parent->left = son;
    else
	parent->right = son;
    free(del);
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

void *btv_deleteall(node *base, size_t *num)
    {
    node *t;
    t = base->left;
    _deleteall(t);
    base->left = NULL;
    base->right = NULL;
    *num = 0;
    return base;
    }

void btv_list(node *p)
    {
    int i;
    static int x = 0;
    if (p != NULL)
        {
        x += 2;
        btv_list(p->right);
        for (i = 2; i < x; i++) printf("   ");
        printf("%c\n", *(int*)(p+1));
        btv_list(p->left);
        x -= 2;
        }
    }

void btv_sort(node *p)
    {
    if (p != NULL)
        {
        btv_sort(p->left);
        printf("%c  ", *(int*)(p+1));
        btv_sort(p->right);
        }
    }

int _index;

void _sort(node *p, void *a, size_t width)
    {
    if (p != NULL)
        {
        _sort(p->left, a, width);
        memcpy((char*)a+(_index++)*width, p+1, width);
        _sort(p->right, a, width);
        }
    }

node *_balance(int n, void *a, size_t width)
    {
    int nl, nr;
    node *p;
    if (n > 0)
        {
        nl = (n-1) / 2;
        nr = n - nl - 1;
        p = (node*)malloc(sizeof(node) + width);
        p->left = _balance(nl, a, width);
        memcpy(p+1, (char*)a+(_index++)*width, width);
        p->right = _balance(nr, a, width);
        return p;
        }
    else
        return NULL;
    }

void btv_balance(node *base, size_t *num, size_t width)
    {
    void *tmp;
    int ntmp = *num;
    tmp = malloc(width*ntmp);
    _index = 0;
    _sort(base->left, tmp, width);
    ntmp = *num;
    btv_deleteall(base, num);
    _index = 0;
    base->left = _balance(ntmp, tmp, width);
    *num = ntmp;
    free(tmp);
    }

#define DY  50

void _draw_node(node *p, int x1, int x2, int y)
    {
    char content[2];
    if (p != NULL)
	{
	_draw_node(p->left, x1, (x1+x2)/2, y+DY);
	content[0] = *((char*)(p+1));
	content[1] = NULL;
	fillellipse((x1+x2)/2, y,
		    textheight(content)/2+5, textheight(content)/2+5);
	outtextxy((x1+x2)/2, y-3, content);
	_draw_node(p->right, (x1+x2)/2, x2, y+DY);
	}
    else
	fillellipse((x1+x2)/2, y, 3, 3);
    }

void _draw_link(node *p,int x1, int x2, int y)
    {
    if (p != NULL)
	{
	lineto((x1+x2)/2, y);
	_draw_link(p->left, x1, (x1+x2)/2, y+DY);
	moveto((x1+x2)/2, y);
	_draw_link(p->right, (x1+x2)/2, x2, y+DY);
	lineto((x1+x2)/2, y);
	}
    else
	{
	lineto((x1+x2)/2, y);
	moveto((x1+x2)/2, y);
	}
    }

void btv_draw(node *p)
    {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    if (graphresult() != grOk)
	{
	printf("\n Graphic system error !");
	return;
	}
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setfillstyle(0, BLACK);
    moveto(getmaxx()/2, 10);
    _draw_link(p, 7, getmaxx()-7, 15);
    _draw_node(p, 7, getmaxx()-7, 15);
    setcolor(WHITE);
    wait_hardcopy(LPT1);
    closegraph();
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
    size_t w = sizeof(int);
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
	    case 'I' : if (btv_insert(&k,a,np,w,intcmp) == NULL)
			   printf("\n   Error : Out of memory.");
		       else
			   printf("\n   Successful insert.");
		       break;
	    case 'd' :
	    case 'D' : if (btv_delete1(&k,a,np,w,intcmp) == NULL)
			   printf("\n   Error : Table empty or can't find.");
                       else
                           printf("\n   Successful delete.");
                       break;
            case 's' :
            case 'S' : if (btv_search(&k,a,np,w,intcmp) == NULL)
                           printf("\n   Error : Can'f find that key");
                       else
                           printf("\n   Ok! find ");
                       break;
            case 'l' :
            case 'L' : btv_list(a->left);
                       break;
            case 'o' :
            case 'O' : printf("\n");
                       btv_sort(a->left);
                       break;
            case 'b' :
            case 'B' : btv_balance(a, np, w);
		       break;
	    case 'g' :
	    case 'G' : btv_draw(a->left);
		       break;
	    }
	printf("  n = %d", *np);
	}
    }
/*
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
        btv_insert(v, a, n);
        }
    fclose(fp);
    }

#define LOOP 100

void btv_test(node *a, size_t n)
    {
    int i;
    int r;
    long t1, t2;
    t1 = get_tick();
    r = random(30000);
    for (i = 0; i < LOOP; i++)
        btv_search(r, a, &n);
    t2 = get_tick();
    printf("\n lv_search %d loops ellapse %ld ticks.", LOOP, diff_tick(t1,t2));
    }
*/
void main(void)
    {
    int *table;
    size_t nitem = 0;
    /* li_test(table, nitem); */
    init_list(&head);
    interpret(head, &nitem);
    btv_deleteall(head, &nitem);
    }






