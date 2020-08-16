/*                                                           */
/*  RBTRSRCH.C  :  Red-Black tree Libaray  	             */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
#include <graphics.h>
#include "hardcopy.h"

#define NODE 1
#define LINK 2
#define TAIL 4

typedef struct _node
    {
    struct _node *left;
    struct _node *right;
    int red;
    } node;

typedef int (*FCMP)(const void*,const void*);

void init_tree(node **p)
    {
    *p = (node*)malloc(sizeof(node));
    (*p)->left = NULL;
    (*p)->right = NULL;
    (*p)->red = 0;
    }

void *rbtr_search(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
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

node *rotate(void *key, node *pivot, node *base, FCMP fcmp)
    {     /* single rotation */
    node *child, *gchild;
    if (fcmp(key, pivot+1) < 0 || pivot == base)
	child = pivot->left;
    else
	child = pivot->right;
    if (fcmp(key, child+1) < 0)
	{
	gchild = child->left;
	child->left = gchild->right;
	gchild->right = child;
	}
    else
	{
	gchild = child->right;
	child->right = gchild->left;
	gchild->left = child;
	}
    if (fcmp(key, pivot+1) < 0 || pivot == base)
	pivot->left = gchild;
    else
	pivot->right = gchild;
    return gchild;
    }

void *rbtr_insert(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    node *t, *parent, *gparent, *ggparent;
    ggparent = gparent = parent = base;
    t = base->left;
    while (t != NULL)
	{
	if (fcmp(key, t+1) == 0) return NULL; /* equal key */
	if (t->left && t->right && t->left->red && t->right->red)
	    {
	    t->red = 1;        /* color flip */
	    t->left->red = t->right->red = 0;
	    if (parent->red)  /* rotation needed */
		{
		gparent->red = 1;
		if (fcmp(key, gparent+1) < 0 != fcmp(key, parent+1) < 0)
		    parent = rotate(key, gparent, base, fcmp);  /* double rotation */
		t = rotate(key, ggparent, base, fcmp);
		t->red = 0;
		}
	    base->left->red = 0;
	    }
        ggparent = gparent;
	gparent = parent;
	parent = t;

	if (fcmp(key, t+1) < 0)
	    t = t->left;
	else
	    t = t->right;
	}
    if ((t = (node*)malloc(sizeof(node)+width)) == NULL)
	return NULL;
    memcpy(t+1, key, width);
    t->left = NULL;
    t->right = NULL;
    if (fcmp(key, parent+1) < 0 || parent == base)
	parent->left = t;
    else
	parent->right = t;
    (*num)++;
    t->red = 1;        /* paint color */
    if (parent->red)  /* rotation needed */
	{
	gparent->red = 1;
	if (fcmp(key, gparent+1) < 0 != fcmp(key, parent+1) < 0)
	    parent = rotate(key, gparent, base, fcmp);  /* double rotation */
	t = rotate(key, ggparent, base, fcmp);
	t->red = 0;
	}
    base->left->red = 0;
    return t+1;
    }

node *find_seed(void *key, node *base, FCMP fcmp)
    {
    node *del, *seed_parent, *parent;
    seed_parent = NULL;
    parent = base;
    del = base->left;
    while (del != NULL)
	{
	if (fcmp(key, del+1) < 0)
	    {
	    if (del->red || (del->right && del->right->red))
		seed_parent = parent;
	    parent = del;
	    del = del->left;
	    }
	else
	    {
	    if (del->red || (del->left && del->left->red))
		seed_parent = parent;
	    parent = del;
	    del = del->right;
	    }
	}
    return seed_parent;
    }

void make_leaf_red(void *key, node *base, FCMP fcmp)
    {
    node *seed_parent, *seed, *seed_child;
    seed_parent = find_seed(key, base, fcmp);
    if (seed_parent == NULL)
	{
	seed_parent = base;
	seed = seed_parent->left;
	seed->red = 1;
	}
    else
	{
	if (fcmp(key, seed_parent+1) < 0 || seed_parent == base)
	    seed = seed_parent->left;
	else
	    seed = seed_parent->right;
	}
    if (!seed->red)   /* sibling is red, reverse rotation */
	{
	if (fcmp(key, seed+1) < 0)
	    seed_child = seed->right;
	else
	    seed_child = seed->left;
	seed->red = 1;
	seed_child->red = 0;
	seed_parent = rotate(seed_child+1, seed_parent, base, fcmp);
	}
    while (seed->left && seed->right)
	{
	seed->red = 0;
	seed->right->red = seed->left->red = 1;
	if (fcmp(key, seed+1) < 0)
	    {
	    if ((seed->right->left || seed->right->right) &&
		(seed->right->left->red || seed->right->right->red))
		{   /* reverse rotation needed! */
		if (seed->right->left && seed->right->left->red)
		    {
		    seed->right->red = 0;
		    rotate(seed->right->left+1, seed, base, fcmp);
		    }
		else
		    seed->right->right->red = 0;
		rotate(seed->right+1, seed_parent, base, fcmp);
		}
	    seed_parent = seed;
	    seed = seed->left;
	    }
	else
	    {
	    if ((seed->left->left || seed->left->right) &&
		(seed->left->left->red || seed->left->right->red))
		{
		if (seed->left->right && seed->left->right->red)
		    {
		    seed->left->red = 0;
		    rotate(seed->left->right+1, seed, base, fcmp);
		    }
		else
		    seed->left->left->red = 0;
		rotate(seed->left+1, seed_parent, base, fcmp);
		}
	    seed_parent = seed;
	    seed = seed->right;
	    }
	}
    }

void *rbtr_delete(void *key, node *base, size_t *num, size_t width, FCMP fcmp)
    {
    node *parent, *del, *center, *pcenter, *son;
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
    if (del == NULL) return NULL;  /* can't find */

    if (del->right && del->left)
	{
	pcenter = del;
	center = del->right;
	while (center->left != NULL)
	    {
	    pcenter = center;
	    center = center->left;
	    }
	memcpy(del+1, center+1, width);
	del = center;
	parent = pcenter;
	memcpy(key, del+1, width);
	}
    if (del->left || del->right)
	{  /* one child must be red */
	if (del->left)
	    son = del->left;
	else
	    son = del->right;
	son->red = 0;
	}
    else if (del->left == NULL && del->right == NULL)
	{  /* leaf node */
	if (!del->red) make_leaf_red(del+1, base, fcmp);
	son = NULL;
	}
    base->left->red = 0;
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

node *rbtr_deleteall(node *base, size_t *num)
    {
    node *t;
    t = base->left;
    _deleteall(t);
    base->left = NULL;
    base->right = NULL;
    *num = 0;
    return base;
    }

void rbtr_list(node *p, void (*fprt)(void*,int))
    {
    int i;
    static int x = 0;
    if (p != NULL)
        {
        x += 2;
	rbtr_list(p->right, fprt);
	for (i = 2; i < x; i++) printf("   ");
	fprt(p+1, p->red);
	rbtr_list(p->left, fprt);
	x -= 2;
	}
    }

void rbtr_sort(node *p, void (*fprt)(void*,int))
    {
    if (p != NULL)
        {
	rbtr_sort(p->left, fprt);
	fprt(p+1, p->red);
	rbtr_sort(p->right, fprt);
	}
    }

#define DY  50

void _draw_node(node *p, int x1, int x2, int y, int mode,
		void (*fnode)(void*,char*))
    {
    char content[25];
    if (p != NULL)
	{
	_draw_node(p->left, x1, (x1+x2)/2, y+DY, mode, fnode);
	fnode(p+1, content);
	if (p->red) setcolor(LIGHTRED);
	else setcolor(WHITE);
	fillellipse((x1+x2)/2, y,
		    textwidth(content)/2+4, textheight(content)/2+5);
	outtextxy((x1+x2)/2, y, content);
	ellipse((x1+x2)/2, y, 0, 360,
		textwidth(content)/2+4, textheight(content)/2+5);
	if (p->red)
	    ellipse((x1+x2)/2, y, 0, 360,
		textwidth(content)/2+2, textheight(content)/2+3);
	setcolor(WHITE);
	_draw_node(p->right, (x1+x2)/2, x2, y+DY, mode, fnode);
	}
    else if (mode & TAIL)
	{
	fillellipse((x1+x2)/2, y, 3, 3);
	ellipse((x1+x2)/2, y, 0, 360, 3, 3);
	}
    }

void _draw_link(node *p, int x1, int x2, int y, int mode)
    {
    if (p != NULL)
	{
	lineto((x1+x2)/2, y);
	_draw_link(p->left, x1, (x1+x2)/2, y+DY, mode);
	moveto((x1+x2)/2, y);
	_draw_link(p->right, (x1+x2)/2, x2, y+DY, mode);
	lineto((x1+x2)/2, y);
	}
    else if (mode & TAIL)
	{
	lineto((x1+x2)/2, y);
	moveto((x1+x2)/2, y);
	}
    }

void rbtr_draw(node *p, int mode, void (*fnode)(void*,char*))
    {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    if (graphresult() != grOk)
	{
	printf("\n Graphic system error !");
	return;
	}
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setfillstyle(0, BLACK);
    moveto(getmaxx()/2, 10);
    if (mode & LINK)
	_draw_link(p, 7, getmaxx()-7, 15, mode);
    if (mode & NODE)
	_draw_node(p, 7, getmaxx()-7, 15, mode, fnode);
    wait_hardcopy(LPT1);
    closegraph();
    }







