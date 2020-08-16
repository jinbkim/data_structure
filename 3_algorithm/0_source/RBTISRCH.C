/*                                                           */
/*  RBTISRCH.C  :  Red-Black tree test  	             */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
#include <graphics.h>

#define NODE 1
#define LINK 2
#define TAIL 4

typedef struct _node
    {
    struct _node *left;
    struct _node *right;
    int red;
    int key;
    } node;

node *head;

void init_tree(node **p)
    {
    *p = (node*)malloc(sizeof(node));
    (*p)->left = NULL;
    (*p)->right = NULL;
    (*p)->red = 0;
    }

node *rbti_search(int key, node *base, size_t *num)
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

void rbti_draw(node *,int);

node *rotate(int key, node *pivot, node *base)
    {     /* single rotation */
    node *child, *gchild;
    if (key < pivot->key || pivot == base)
	child = pivot->left;
    else
	child = pivot->right;
    if (key < child->key)
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
    if (key < pivot->key || pivot == base)
	pivot->left = gchild;
    else
	pivot->right = gchild;
    return gchild;
    }

node *rbti_insert(int key, node *base, size_t *num)
    {
    node *t, *parent, *gparent, *ggparent;
    ggparent = gparent = parent = base;
    t = base->left;
    while (t != NULL)
	{
	if (t->left && t->right && t->left->red && t->right->red)
	    {
	    t->red = 1;        /* color flip */
	    t->left->red = t->right->red = 0;
	    if (parent->red)  /* rotation needed */
		{
		gparent->red = 1;
		if (key < gparent->key != key < parent->key)
		    parent = rotate(key, gparent, base);  /* double rotation */
		t = rotate(key, ggparent, base);
		t->red = 0;
		}
	    base->left->red = 0;
	    }
        ggparent = gparent;
	gparent = parent;
	parent = t;

	if (key < t->key)
	    t = t->left;
	else
	    t = t->right;
	}
    if ((t = (node*)malloc(sizeof(node))) == NULL)
	return NULL;
    t->key = key;
    t->left = NULL;
    t->right = NULL;
    if (key < parent->key || parent == base)
	parent->left = t;
    else
	parent->right = t;
    (*num)++;
    t->red = 1;        /* paint color */
    if (parent->red)  /* rotation needed */
	{
	gparent->red = 1;
	if (key < gparent->key != key < parent->key)
	    parent = rotate(key, gparent, base);  /* double rotation */
	t = rotate(key, ggparent, base);
	t->red = 0;
	}
    base->left->red = 0;
    return t;
    }

node *find_seed(int key, node *base)
    {
    node *del, *seed_parent, *parent;
    seed_parent = NULL;
    parent = base;
    del = base->left;
    while (del != NULL)
	{
	if (key < del->key)
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

void make_leaf_red(int key, node *base)
    {
    node *seed_parent, *seed, *seed_child;
    seed_parent = find_seed(key, base);
    if (seed_parent == NULL)
	{
	seed_parent = base;
	seed = seed_parent->left;
	seed->red = 1;
	}
    else
	{
	if (key < seed_parent->key || seed_parent == base)
	    seed = seed_parent->left;
	else seed = seed_parent->right;
	}
    if (!seed->red)   /* sibling is red, reverse rotation */
	{
	if (key < seed->key)
	    seed_child = seed->right;
	else
	    seed_child = seed->left;
	seed->red = 1;
	seed_child->red = 0;
	seed_parent = rotate(seed_child->key, seed_parent, base);
	}
    while (seed->left && seed->right)
	{
	seed->red = 0;
	seed->right->red = seed->left->red = 1;
	if (key < seed->key)
	    {
	    if ((seed->right->left || seed->right->right) &&
		(seed->right->left->red || seed->right->right->red))
		{   /* reverse rotation needed! */
		if (seed->right->left && seed->right->left->red)
		    {
		    seed->right->red = 0;
		    rotate(seed->right->left->key, seed, base);
		    }
		else
		    seed->right->right->red = 0;
		rotate(seed->right->key, seed_parent, base);
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
		    rotate(seed->left->right->key, seed, base);
		    }
		else
		    seed->left->left->red = 0;
		rotate(seed->left->key, seed_parent, base);
		}
	    seed_parent = seed;
	    seed = seed->right;
	    }
	}
    }

node *rbti_delete(int key, node *base, size_t *num)
    {
    node *parent, *del, *center, *pcenter, *son;
    int temp;
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
	del->key = center->key;
	del = center;
	parent = pcenter;
	key = del->key;
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
	if (!del->red) make_leaf_red(del->key, base);
	son = NULL;
	}
    base->left->red = 0;
    if (key < parent->key || parent == base)
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

node *rbti_deleteall(node *base, size_t *num)
    {
    node *t;
    t = base->left;
    _deleteall(t);
    base->left = NULL;
    base->right = NULL;
    *num = 0;
    return base;
    }

void rbti_list(node *p)
    {
    int i;
    static int x = 0;
    if (p != NULL)
        {
        x += 2;
	rbti_list(p->right);
	for (i = 2; i < x; i++) printf("   ");
	if (p->red)
	    printf("%c\n", tolower(p->key));
	else
	    printf("%c\n", toupper(p->key));
	rbti_list(p->left);
	x -= 2;
	}
    }

void rbti_sort(node *p)
    {
    if (p != NULL)
        {
	rbti_sort(p->left);
	printf("%c  ", p->key);
	rbti_sort(p->right);
        }
    }

#define DY  30

void _draw_node(node *p, int x1, int x2, int y, int mode)
    {
    char content[2];
    if (p != NULL)
	{
	_draw_node(p->left, x1, (x1+x2)/2, y+DY, mode);
	content[0] = p->key;
	content[1] = NULL;
	if (p->red) setcolor(LIGHTRED);
	else setcolor(WHITE);
	fillellipse((x1+x2)/2, y,
		    textwidth(content)/2+5, textheight(content)/2 + 3);
	outtextxy((x1+x2)/2, y, content);
	ellipse((x1+x2)/2, y, 0, 360,
		textwidth(content)/2+5, textheight(content)/2 + 3);
	if (p->red)
	    ellipse((x1+x2)/2, y, 0, 360,
		textwidth(content)/2+3, textheight(content)/2 + 1);
	setcolor(WHITE);
	_draw_node(p->right, (x1+x2)/2, x2, y+DY, mode);
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

void rbti_draw(node *p, int mode)
    {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    if (graphresult() != grOk)
	{
	printf("\n Graphic system error !");
	return;
	}
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setfillstyle(0, BLACK);
    moveto(getmaxx()/2, 10);
    if (mode & LINK)
	_draw_link(p, 5, getmaxx()-5, 10, mode);
    if (mode & NODE)
	_draw_node(p, 5, getmaxx()-5, 10, mode);
    outtextxy(getmaxx()/2, getmaxy()-10, "Press any key to return.");
    bioskey(0);
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
	    case 'I' : if (rbti_insert(k,a,np) == NULL)
			   printf("\n   Error : Out of memory.");
		       else
			   printf("\n   Successful insert.");
		       break;
	    case 'd' :
	    case 'D' : if (rbti_delete(k,a,np) == NULL)
			   printf("\n   Error : Table empty or can't find.");
		       else
			   printf("\n   Successful delete.");
		       break;
	    case 's' :
	    case 'S' : if (rbti_search(k,a,np) == NULL)
			   printf("\n   Error : Can'f find that key");
		       else
			   printf("\n   Ok! find ");
		       break;
	    case 'l' :
	    case 'L' : rbti_list(a->left);
		       break;
	    case 'o' :
            case 'O' : printf("\n");
		       rbti_sort(a->left);
		       break;
	    case 'g' :
	    case 'G' : rbti_draw(a->left, NODE|LINK|TAIL);
		       break;
	    }
	printf("  n = %d", *np);
	}
    }

void main(void)
    {
    int *table;
    size_t nitem = 0;
    /* li_test(table, nitem); */
    init_tree(&head);
    interpret(head, &nitem);
    rbti_deleteall(head, &nitem);
    }






