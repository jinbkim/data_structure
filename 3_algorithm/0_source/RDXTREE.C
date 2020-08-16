/*                                                           */
/*  RDXTREE.C  :  Radix search tree test                     */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
#include <graphics.h>
#include "hardcopy.h"


typedef struct _node
    {
    struct _node *left;
    struct _node *right;
    int key;
    } node;

node *head;

unsigned bits(unsigned x, int k, int j)
    {
    return (x >> k) & ~(~0 << j);
    }

void init_tree(node **p)
    {
    *p = (node*)malloc(sizeof(node));
    (*p)->left = NULL;
    (*p)->right = NULL;
    }

node *rdx_search(int key, node *base, size_t *num)
    {
    node *t;
    int b = 0;
    t = base->left;
    while (key != t->key && t != NULL)
	t = bits(key, b++, 1) ? t->right : t->left;
    return t;
    }

node *rdx_insert(int key, node *base, size_t *num)
    {
    node *p, *t;
    int b = 0;
    p = base;
    t = base->left;
    while (t != NULL)
	{
	if (key == t->key) return NULL;  /* equal key */
	p = t;
	t = bits(key, b++, 1) ? t->right : t->left;
	}
    if ((t = (node*)malloc(sizeof(node))) == NULL)
	return NULL;
    t->key = key;
    t->left = NULL;
    t->right = NULL;
    if (bits(key, b-1, 1) && p != base) p->right = t;
    else p->left = t;
    (*num)++;
    return t;
    }

node *rdx_delete(int key, node *base, size_t *num)
    {
    node *parent, *son, *del, *center;
    int b = 0;
    parent = base;
    del = base->left;
    while (key != del->key && del != NULL)
        {
	parent = del;
	del = bits(key, b++, 1) ? del->right : del->left;
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
    if (bits(key, b-1, 1) && parent != base) parent->right = son;
    else parent->left = son;
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

node *rdx_deleteall(node *base, size_t *num)
    {
    node *t;
    t = base->left;
    _deleteall(t);
    base->left = NULL;
    base->right = NULL;
    *num = 0;
    return base;
    }

void rdx_list(node *p)
    {
    int i;
    static int x = 0;
    if (p != NULL)
        {
        x += 2;
	rdx_list(p->right);
	for (i = 2; i < x; i++) printf("   ");
	printf("%c\n", p->key);
	rdx_list(p->left);
	x -= 2;
	}
    }

#define DY  50

void _draw_node(node *p, int x1, int x2, int y)
    {
    char content[2];
    if (p != NULL)
	{
	_draw_node(p->left, x1, (x1+x2)/2, y+DY);
	content[0] = p->key;
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

void rdx_draw(node *p)
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
	    case 'I' : if (rdx_insert(k,a,np) == NULL)
			   printf("\n   Error : Out of memory.");
		       else
			   printf("\n   Successful insert.");
		       break;
	    case 'd' :
	    case 'D' : if (rdx_delete(k,a,np) == NULL)
			   printf("\n   Error : Table empty or can't find.");
		       else
			   printf("\n   Successful delete.");
		       break;
	    case 's' :
	    case 'S' : if (rdx_search(k,a,np) == NULL)
			   printf("\n   Error : Can'f find that key");
                       else
                           printf("\n   Ok! find ");
                       break;
            case 'l' :
	    case 'L' : rdx_list(a->left);
		       break;
	    case 'g' :
	    case 'G' : rdx_draw(a->left);
	    }
	printf("  n = %d", *np);
	}
    }

void main(void)
    {
    size_t nitem = 0;
    init_tree(&head);
    interpret(head, &nitem);
    rdx_deleteall(head, &nitem);
    }






