/*                                                           */
/*  RDXTRIE.C  :  Radix search trie test                     */
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

node *trie_search(int key, node *base, size_t *num)
    {
    node *t, *p;
    int b = 0;
    p = base;
    t = base->left;
    while (t != NULL)
	{
	p = t;
	t = bits(key, b++, 1) ? t->right : t->left;
	}
    if (p->key == key) return p;
    else return NULL;
    }

node *trie_insert(int key, node *base, size_t *num)
    {
    node *gp, *p, *t;
    int b = 0;
    gp = p = base;
    t = base->left;
    while (t != NULL)
	{
	if (key == t->key) return NULL;  /* equal key */
	gp = p;
	p = t;
	t = bits(key, b++, 1) ? t->right : t->left;
	}
    b--;
    if (p->left || p->right)
	{  /* if internal */
	if ((t = (node*)malloc(sizeof(node))) == NULL)
	    return NULL;
	t->left = t->right = NULL;
	t->key = key;
	if (bits(key, b, 1)) p->right = t;
	else p->left = t;
	}
    else  /* if external */
	{
	if (p == base)   /* if root */
	    {
	    if ((t = (node*)malloc(sizeof(node))) == NULL)
		return NULL;
	    t->left = t->right = NULL;
	    t->key = key;
	    p->left = t;
	    }
	else /* if not root */
	    {
	    do
		{
		if ((t = (node*)malloc(sizeof(node))) == NULL)
		    return NULL;
		t->left = t->right = NULL;  /* branch node */
		t->key = -1;
		if (gp != base && bits(key, b-1, 1))
		    gp->right = t;
		else
		    gp->left = t;
		gp = t;
		b++;
		} while (bits(key, b-1, 1) == bits(p->key, b-1, 1));
	    if ((t = (node*)malloc(sizeof(node))) == NULL)
		return NULL;
	    t->key = key;
	    t->left = t->right = NULL;
	    if (bits(key, b-1, 1))
		{
		gp->right = t;
		gp->left = p;
		}
	    else
		{
		gp->left = t;
		gp->right = p;
		}
	    }
	}
    (*num)++;
    return t;
    }

node *trie_delete(int key, node *base, size_t *num)
    {
    node *gpdel, *pdel, *del, *sib, *start;
    int b = 0, sb;
    start = gpdel = pdel = base;
    del = base->left;
    while (del != NULL)
	{
	gpdel = pdel;
	pdel = del;
	if (del->left && del->right &&
	    (del->left->key == -1 || del->right->key == -1))
	    {
	    start = del;
	    sb = b;
	    }
	del = bits(key, b++, 1) ? del->right : del->left;
	}
    if (pdel->key != key) return NULL;  /* can't find */
    b--;
    free(pdel);
    if (gpdel != base && bits(key, b-1, 1))
	{
	gpdel->right = NULL;
	sib = gpdel->left;
	}
    else
	{
	gpdel->left = NULL;
	sib = gpdel->right;
	}
    if (sib && sib->key != -1)
	{  /* sibling is info node */
	pdel = start;
	del = bits(key, sb, 1) ? pdel->right : pdel->left;
	b = sb+1;
	while (del != NULL)
	    {
	    pdel = del;
	    del = bits(key, b++, 1) ? pdel->right : pdel->left;
	    free(pdel);
	    }
	if (start != base && bits(key, sb, 1)) start->right = sib;
	else start->left = sib;
	}
    (*num)--;
    return gpdel;
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

node *trie_deleteall(node *base, size_t *num)
    {
    node *t;
    t = base->left;
    _deleteall(t);
    base->left = NULL;
    base->right = NULL;
    *num = 0;
    return base;
    }

void trie_list(node *p)
    {
    int i;
    static int x = 0;
    if (p != NULL)
        {
        x += 2;
	trie_list(p->right);
	for (i = 2; i < x; i++) printf("   ");
	if (p->key != -1) printf("%c\n", p->key);
	else printf("%c\n", '*');
	trie_list(p->left);
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
	if (p->key == -1) fillellipse((x1+x2)/2, y, 5, 5);
	else
	    {
	    content[0] = p->key;
	    content[1] = NULL;
	    fillellipse((x1+x2)/2, y,
		    textheight(content)/2+5, textheight(content)/2+5);
	    outtextxy((x1+x2)/2, y-3, content);
	    }
	_draw_node(p->right, (x1+x2)/2, x2, y+DY);
	}
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
    }

void trie_draw(node *p)
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
	    case 'I' : if (trie_insert(k,a,np) == NULL)
			   printf("\n   Error : equal key or out of memory");
		       else
			   printf("\n   Successful insert.");
		       break;
	    case 'd' :
	    case 'D' : if (trie_delete(k,a,np) == NULL)
			   printf("\n   Error : Table empty or can't find.");
		       else
			   printf("\n   Successful delete.");
		       break;
	    case 's' :
	    case 'S' : if (trie_search(k,a,np) == NULL)
			   printf("\n   Error : Can'f find that key");
                       else
                           printf("\n   Ok! find ");
                       break;
            case 'l' :
	    case 'L' : trie_list(a->left);
		       break;
	    case 'g' :
	    case 'G' : trie_draw(a->left);
		       break;
	    }
	printf("  n = %d", *np);
	}
    }

void main(void)
    {
    size_t nitem = 0;
    init_tree(&head);
    interpret(head, &nitem);
    trie_deleteall(head, &nitem);
    }






