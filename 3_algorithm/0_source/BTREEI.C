/*                                                           */
/*  BTREEI.C  :  B-tree test version		             */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <mem.h>

#define M  1
#define MM M*2+1

typedef struct _Bnode
    {
    int n;
    struct _Bnode *ptr[MM+1];
    int key[MM];
    } Bnode;

Bnode *head;

void init_Btree(int *num)
    {
    head = (Bnode*)malloc(sizeof(Bnode));
    head->ptr[0] = NULL;
    head->n = 0;
    *num = 0;
    }

int in_Bnode(int key, Bnode *t)
    {
    int i;
    for (i = 0; i < t->n; i++)
	if (key == t->key[i]) return i;
    return -1;
    }

Bnode *Btree_search(int key, Bnode *base, int *num)
    {
    Bnode *t;
    int i;
    t = base->ptr[0];
    while (t != NULL && in_Bnode(key, t) == -1)
	{
	for (i = 0; i < t->n && key >= t->key[i]; i++);
	t = t->ptr[i];
	}
    return t;
    }

void insert_key(Bnode *t, int key, Bnode *left, Bnode *right)
    {
    int i;
    i = t->n;
    while (t->key[i-1] > key && i > 0)
	{
	t->key[i] = t->key[i-1];
	t->ptr[i+1] = t->ptr[i];
	i--;
	}
    t->n++;
    t->key[i] = key;
    t->ptr[i] = left;
    t->ptr[i+1] = right;
    }

Bnode *split(int key, Bnode *pivot, Bnode *base)
    {
    Bnode *left, *right;
    Bnode *child;
    int i;
    if ((right = (Bnode*)malloc(sizeof(Bnode))) == NULL) return NULL;
    if (pivot == base)
	{
	child = pivot->ptr[0];
	if ((left = (Bnode*)malloc(sizeof(Bnode))) == NULL) return NULL;
	for (i = 0; i < M; i++)   /* left node create */
	    {
	    left->key[i] = child->key[i];
	    left->ptr[i] = child->ptr[i];
	    }
	left->ptr[i] = child->ptr[i];
	left->n = M;
	for (i = M+1; i < MM; i++)  /* right node create */
	    {
	    right->key[i-M-1] = child->key[i];
	    right->ptr[i-M-1] = child->ptr[i];
	    }
	right->ptr[i-M-1] = child->ptr[i];
	right->n = M;

	child->n = 0;   /* root node create */
	insert_key(child, child->key[M], left, right);
	}
    else
	{
	for (i = 0; i < pivot->n && key >= pivot->key[i]; i++);
	left = pivot->ptr[i];
	left->n = M;  /* left already created */
	for (i = M+1; i < MM; i++)  /* right node create */
	    {
	    right->key[i-M-1] = left->key[i];
	    right->ptr[i-M-1] = left->ptr[i];
	    }
	right->ptr[i-M-1] = left->ptr[i];
	right->n = M;

	insert_key(pivot, left->key[M], left, right);  /* pivot update */
	child = pivot;
	}
    return child;
    }

Bnode *Btree_insert(int key, Bnode *base, int *num)
    {
    Bnode *t, *parent;
    int i;
    parent = base;
    t = base->ptr[0];
    if (t == NULL)
	{
	if ((t = (Bnode*)malloc(sizeof(Bnode))) == NULL) return NULL;
	t->n = 0;
	t->ptr[0] = NULL;
	base->ptr[0] = t;
	}
    while (t != NULL)
	{
	if (in_Bnode(key, t) >= 0) return NULL;  /* equal key */
	if (t->n == MM)
	    {
	    t = split(key, parent, base);
	    if (t == NULL) return NULL;
	    }
	parent = t;
	for (i = 0; i < t->n && key >= t->key[i]; i++);
	t = t->ptr[i];
	}
    insert_key(parent, key, NULL, NULL);
    (*num)++;
    return parent;
    }

void delete_key(Bnode *t, int index)
    {
    int i;
    for (i = index+1; i < t->n; i++)
	{
	t->key[i-1] = t->key[i];
	t->ptr[i-1] = t->ptr[i];
	}
    t->ptr[i-1] = t->ptr[i];
    t->n--;
    }

int borrow_key(Bnode *p, int index)
    {
    int from, to;
    Bnode *p1, *p2;
    if (index == p->n)
	{  /* right most */
	from = index-1;
	to = index;
	}
    else
	{
	from = index+1;
	to = index;
	}
    p1 = p->ptr[from];
    p2 = p->ptr[to];
    if (p1->n <= M) return 0;
    if (from > to)
	{
	insert_key(p2, p->key[to], p2->ptr[p2->n], p1->ptr[0]);
	p->key[to] = p1->key[0];
	delete_key(p1, 0);
	}
    else
	{
	insert_key(p2, p->key[from], p1->ptr[p1->n], p2->ptr[0]);
	p->key[from] = p1->key[p1->n - 1];
	delete_key(p1, p1->n - 1);
	}
    return 1;
    }

Bnode *bind_node(Bnode *p, int index, Bnode *base)
    {
    Bnode *left, *right;
    int i;
    if (index == p->n) index--;
    left = p->ptr[index];
    right = p->ptr[index+1];
    left->key[left->n++] = p->key[index];
    for (i = 0; i < right->n; i++)
	{
	left->key[left->n] = right->key[i];
	left->ptr[left->n++] = right->ptr[i];
	}
    left->ptr[left->n] = right->ptr[i];
    delete_key(p, index);
    p->ptr[index] = left;
    free(right);
    if (p->n == 0)
	{
	free(p);
	base->ptr[0] = left;
	}
    return left;
    }

void make_swap(Bnode *p, Bnode *t, int *key, int index)
    {
    Bnode *center, *pcenter;
    pcenter = t;
    center = pcenter->ptr[index+1];
    while (center->ptr[0] != NULL)
	{
	pcenter = center;
	center = center->ptr[0];
	}
    t->key[index] = center->key[0];
    *key = center->key[0];
    }

Bnode *Btree_delete(int key, Bnode *base, int *num)
    {
    Bnode *t, *parent;
    int pi = 0;
    int ti;
    parent = base;
    t = base->ptr[0];
    while (t != NULL)
	{
	if (t->n <= M && parent != base)
	    if (!borrow_key(parent, pi)) t = bind_node(parent, pi, base);
	if ((ti = in_Bnode(key, t)) >= 0)
	    {
	    if (t->ptr[0] == NULL) break;  /* if external break */
	    else make_swap(parent, t, &key, ti);
	    }
	parent = t;
	for (pi = 0; pi < t->n && key >= t->key[pi]; pi++);
	t = t->ptr[pi];
	}
    if (t == NULL) return NULL;  /* can't find */
    if (t->n <= M && parent != base)  /* external but less M */
	if (!borrow_key(parent, pi)) t = bind_node(parent, pi, base);
    delete_key(t, in_Bnode(key, t));
    (*num)--;
    return t;
    }

void _deleteall(Bnode *t)
    {
    int i;
    if (t != NULL)
	{
	for (i = 0; i < t->n+1; i++)
	    _deleteall(t->ptr[i]);
	free(t);
	}
    }

Bnode *Btree_deleteall(Bnode *base, int *num)
    {
    _deleteall(base->ptr[0]);
    base->ptr[0] = NULL;
    *num = 0;
    return base;
    }

void _list(Bnode *t)
    {
    int i;
    static int x = 0;
    if (t != NULL)
	{
	x += 2;
	for (i = 2; i < x; i++) printf("   ");
	for (i = 0; i < t->n; i++) printf("%c", t->key[i]);
	printf("\n");
	for (i = 0; i < t->n+1; i++) _list(t->ptr[i]);
	x -= 2;
	}
    }

void Btree_list(Bnode *base)
    {
    _list(base->ptr[0]);
    }

void _sort(Bnode *t)
    {
    int i, j;
    if (t != NULL)
	{
	for (i = 0; i < t->n; i++)
	    {
	    _sort(t->ptr[i]);
	    printf("%c\n", t->key[i]);
	    _sort(t->ptr[i+1]);
	    }
	}
    }

void Btree_sort(Bnode *base)
    {
    _sort(base->ptr[0]);
    }

void interpret(Bnode *a, int *np)
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
	    case 'I' : if (Btree_insert(k,a,np) == NULL)
			   printf("\n   Error : Equal key inputted.");
		       else
			   printf("\n   Successful insert.");
		       break;
	    case 'd' :
	    case 'D' : if (Btree_delete(k,a,np) == NULL)
			   printf("\n   Error : Table empty or can't find.");
		       else
			   printf("\n   Successful delete.");
		       break;
	    case 's' :
	    case 'S' : if (Btree_search(k,a,np) == NULL)
			   printf("\n   Error : Can'f find that key");
		       else
			   printf("\n   Ok! find ");
		       break;
	    case 'l' :
	    case 'L' : Btree_list(a);
		       break;
	    case 'o' :
            case 'O' : printf("\n");
		       Btree_sort(a);
		       break;
	    }
	printf("  n = %d", *np);
	}
    }

void main(void)
    {
    int num;
    init_Btree(&num);
    interpret(head, &num);
    Btree_deleteall(head, &num);
    }

