/*                                                           */
/*  EXTBTREE.C  :  External B-tree Libaray                   */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <mem.h>
#include "\tc\extbtree.h"

#define MM (M*2+1)

#define KEY(t, i)  (char*)(t+1) + (i)*width
#define NILL  -1L
#define NUM  0L
#define FREE 2L
#define BASE 6L
#define NODESIZE (sizeof(Bnode)+width*MM)
#define isBASE   -2

Bnode *pbowl, *tbowl;
long ppos, tpos;

long getdw(FILE *fp, long pos)
    {
    long r1, r2;
    if (pos != NILL) fseek(fp, pos, SEEK_SET);
    r1 = getw(fp);
    r2 = getw(fp);
    return (r2<<16) | r1;
    }

void putdw(long l, FILE *fp, long pos)
    {
    if (pos != NILL) fseek(fp, pos, SEEK_SET);
    putw(l & 0x0000ffff, fp);
    putw(l >> 16, fp);
    }

FILE *init_Btree(char *fname, size_t *num, size_t width)
    {
    FILE *fp;
    pbowl = (Bnode*)calloc(1, NODESIZE);
    tbowl = (Bnode*)calloc(1, NODESIZE);
    ppos = tpos = NILL;
    if (!(pbowl && tbowl)) return NULL;  /* memory allocation error */
    if ((fp = fopen(fname, "rb+")) == NULL)
	{
	if ((fp = fopen(fname, "wb+")) == NULL) return NULL;
	putw(0, fp);   /* num = 0 */
	putdw(NILL, fp, NILL);
	pbowl->n = isBASE;
	pbowl->ptr[0] = NILL;
	fwrite(pbowl, NODESIZE, 1, fp);
	*num = 0;
	}
    else
	*num = getw(fp);
    tbowl->n = pbowl->n = 0;
    return fp;
    }

void close_Btree(FILE *fp, size_t *num)
    {
    rewind(fp);
    putw(*num, fp);
    fclose(fp);
    }

long load_Bnode(Bnode *p, FILE *fp, size_t width, long pos)
    {
    long r;
    if (pos != NILL) fseek(fp, pos, SEEK_SET);
    else
	{
	p->n = -1;
	return NILL;
	}
    r = ftell(fp);
    fread(p, NODESIZE, 1, fp);
    return r;
    }

long save_Bnode(Bnode *p, FILE *fp, size_t width, long pos)
    {
    Bnode *fr;
    long r;
    fr = (Bnode*)calloc(1, NODESIZE);
    if (pos != NILL)
	fseek(fp, pos, SEEK_SET);
    else
	{
	if (getdw(fp, FREE) == NILL)  /* if no free list */
	    fseek(fp, 0, SEEK_END);
	else  /* if free node exist */
	    {
	    r = load_Bnode(fr, fp, width, getdw(fp, FREE));
	    putdw(fr->ptr[0], fp, FREE);
	    fseek(fp, r, SEEK_SET);
	    }
	}
    r = ftell(fp);
    fwrite(p, NODESIZE, 1, fp);
    free(fr);
    return r;
    }

int in_Bnode(void *key, Bnode *t, size_t width, FCMP fcmp)
    {
    int i;
    for (i = 0; i < t->n; i++)
	if (fcmp(key, KEY(t, i)) == 0) return i;
    return -1;
    }

void *Btree_search(FILE *fp, void *key, size_t *num, size_t width, FCMP fcmp)
    {
    int i;
    int pos;
    tpos = load_Bnode(tbowl, fp, width, BASE);
    tpos = load_Bnode(tbowl, fp, width, tbowl->ptr[0]);
    while (tbowl->n >= 0 && (pos = in_Bnode(key, tbowl, width, fcmp)) == -1)
	{
	for (i = 0; i < tbowl->n && fcmp(key, KEY(tbowl, i)) >= 0; i++);
	tpos = load_Bnode(tbowl, fp, width, tbowl->ptr[i]);
	}
    if (tbowl->n < 0) return NULL;
    return KEY(tbowl, pos);
    }

void insert_key(Bnode *t, void *key, size_t width, long left, long right,
		FCMP fcmp)
    {
    int i;
    i = t->n;
    while (fcmp(KEY(t, i-1), key) > 0 && i > 0)
	{
	memcpy(KEY(t, i), KEY(t, i-1), width);
	t->ptr[i+1] = t->ptr[i];
	i--;
	}
    t->n++;
    memcpy(KEY(t, i), key, width);
    t->ptr[i] = left;
    t->ptr[i+1] = right;
    }

long split(FILE *fp, void *key, size_t width, FCMP fcmp)
    {    /* pbowl must be pivot of split & tbowl is pbowl's child */
    Bnode *left, *right;
    int i;
    long r;
    if ((right = (Bnode*)calloc(1, NODESIZE)) == NULL) return NILL;
    if (pbowl->n == isBASE)
	{
	if ((left = (Bnode*)calloc(1, NODESIZE)) == NULL) return NILL;
	for (i = 0; i < M; i++)   /* left node create */
	    {
	    memcpy(KEY(left, i), KEY(tbowl, i), width);
	    left->ptr[i] = tbowl->ptr[i];
	    }
	left->ptr[i] = tbowl->ptr[i];
	left->n = M;
	for (i = M+1; i < MM; i++)  /* right node create */
	    {
	    memcpy(KEY(right, i-M-1), KEY(tbowl, i), width);
	    right->ptr[i-M-1] = tbowl->ptr[i];
	    }
	right->ptr[i-M-1] = tbowl->ptr[i];
	right->n = M;

	tbowl->n = 0;   /* root node create */

	insert_key(tbowl, KEY(tbowl, M), width,
		   save_Bnode(left, fp, width, NILL),
		   save_Bnode(right, fp, width, NILL), fcmp);
	r = save_Bnode(tbowl, fp, width, tpos);
	free(left);
	}
    else
	{
	for (i = 0; i < pbowl->n && fcmp(key, KEY(pbowl, i)) >= 0; i++);
	tbowl->n = M;  /* left already created */
	for (i = M+1; i < MM; i++)  /* right node create */
	    {
	    memcpy(KEY(right, i-M-1), KEY(tbowl, i), width);
	    right->ptr[i-M-1] = tbowl->ptr[i];
	    }
	right->ptr[i-M-1] = tbowl->ptr[i];
	right->n = M;

	insert_key(pbowl, KEY(tbowl, M), width,
		   save_Bnode(tbowl, fp, width, tpos),
		   save_Bnode(right, fp, width, NILL), fcmp);  /* pivot update */
	save_Bnode(pbowl, fp, width, ppos);
	r = ppos;
	}
    free(right);
    return r;
    }

void *Btree_insert(FILE *fp, void *key, size_t *num, size_t width, FCMP fcmp)
    {
    int i;
    ppos = load_Bnode(pbowl, fp, width, BASE);
    tpos = load_Bnode(tbowl, fp, width, pbowl->ptr[0]);
    if (tbowl->n < 0)
	{  /* if not exist root node, then create */
	tbowl->n = 0;
	tbowl->ptr[0] = NILL;
	tpos = save_Bnode(tbowl, fp, width, NILL);
	pbowl->ptr[0] = tpos;
	ppos = save_Bnode(pbowl, fp, width, BASE);
	ppos = tpos;
	memcpy(pbowl, tbowl, NODESIZE);
	}
    while (tbowl->n >= 0)
	{
	if (in_Bnode(key, tbowl, width, fcmp) >= 0) return NULL; /* equal key */
	if (tbowl->n == MM)
	    tpos = load_Bnode(tbowl, fp, width, split(fp, key, width, fcmp));
	memcpy(pbowl, tbowl, NODESIZE);
	ppos = tpos;
	for (i = 0; i < tbowl->n && fcmp(key, KEY(tbowl, i)) >= 0; i++);
	tpos = load_Bnode(tbowl, fp, width, tbowl->ptr[i]);
	}
    insert_key(pbowl, key, width, NILL, NILL, fcmp);
    ppos = save_Bnode(pbowl, fp, width, ppos);
    (*num)++;
    return KEY(pbowl, in_Bnode(key, pbowl, width, fcmp));
    }

void delete_key(Bnode *t, int index, size_t width)
    {
    int i;
    for (i = index+1; i < t->n; i++)
	{
	memcpy(KEY(t, i-1), KEY(t, i), width);
	t->ptr[i-1] = t->ptr[i];
	}
    t->ptr[i-1] = t->ptr[i];
    t->n--;
    }

void delete_node(FILE *fp, size_t width, long pos)
    {
    Bnode *fr;
    fr = (Bnode*)calloc(1, NODESIZE);
    load_Bnode(fr, fp, width, pos);
    fr->ptr[0] = getdw(fp, FREE);
    fr->n = -1;  /* mark deleted */
    putdw(pos, fp, FREE);
    save_Bnode(fr, fp, width, pos);
    }

int borrow_key(FILE *fp, int index, size_t width, FCMP fcmp)
    {
    Bnode *p1, *p2;
    int from, to;
    long ip1, ip2;
    if (index == pbowl->n)
	{  /* right most */
	from = index-1;
	to = index;
	}
    else
	{
	from = index+1;
	to = index;
	}
    p1 = (Bnode*)calloc(1, NODESIZE);
    p2 = (Bnode*)calloc(1, NODESIZE);
    ip1 = load_Bnode(p1, fp, width, pbowl->ptr[from]);
    ip2 = load_Bnode(p2, fp, width, pbowl->ptr[to]);
    if (p1->n <= M)
	{
	free(p1);
	free(p2);
	return 0;
	}
    if (from > to)
	{
	insert_key(p2, KEY(pbowl, to), width,
		   p2->ptr[p2->n], p1->ptr[0], fcmp);
	memcpy(KEY(pbowl, to), KEY(p1, 0), width);
	delete_key(p1, 0, width);
	}
    else
	{
	insert_key(p2, KEY(pbowl, from), width,
		   p1->ptr[p1->n], p2->ptr[0], fcmp);
	memcpy(KEY(pbowl, from), KEY(p1, p1->n - 1), width);
	delete_key(p1, p1->n - 1, width);
	}
    save_Bnode(p1, fp, width, ip1);
    save_Bnode(p2, fp, width, ip2);
    save_Bnode(pbowl, fp, width, ppos);
    free(p1);
    free(p2);
    return 1;
    }

long bind_node(FILE *fp, int index, size_t width)
    {
    Bnode *left, *right;
    long r;
    int i;
    long ileft, iright;
    left = (Bnode*)calloc(1, NODESIZE);
    right = (Bnode*)calloc(1, NODESIZE);
    if (index == pbowl->n) index--;
    ileft = load_Bnode(left, fp, width, pbowl->ptr[index]);
    iright = load_Bnode(right, fp, width, pbowl->ptr[index+1]);
    memcpy(KEY(left, left->n++), KEY(pbowl, index), width);
    for (i = 0; i < right->n; i++)
	{
	memcpy(KEY(left, left->n), KEY(right, i), width);
	left->ptr[left->n++] = right->ptr[i];
	}
    left->ptr[left->n] = right->ptr[i];
    delete_key(pbowl, index, width);
    pbowl->ptr[index] = ileft;
    delete_node(fp, width, iright);
    free(right);
    if (pbowl->n == 0)
	{
	delete_node(fp, width, ppos);
	ppos = load_Bnode(pbowl, fp, width, BASE);
	pbowl->ptr[0] = ileft;
	}
    save_Bnode(pbowl, fp, width, ppos);
    save_Bnode(left, fp, width, ileft);
    free(left);
    return ileft;
    }

void make_swap(FILE *fp, void *key, size_t width, int index)
    {
    Bnode *center, *pcenter;
    long ic, ipc;
    center = (Bnode*)calloc(1, NODESIZE);
    pcenter = (Bnode*)calloc(1, NODESIZE);
    ipc = tpos;
    memcpy(pcenter, tbowl, NODESIZE);
    ic = load_Bnode(center, fp, width, tbowl->ptr[index+1]);
    while (center->ptr[0] != NILL)
	{
	memcpy(pcenter, center, width);
	ipc = ic;
	ic = load_Bnode(center, fp, width, center->ptr[0]);
	}
    memcpy(KEY(tbowl, index), KEY(center, 0), width);
    save_Bnode(tbowl, fp, width, tpos);
    memcpy(key, KEY(center, 0), width);
    free(center);
    free(pcenter);
    }

void *Btree_delete(FILE *fp, void *key, size_t *num, size_t width, FCMP fcmp)
    {
    int pi = 0;
    int ti;
    ppos = load_Bnode(pbowl, fp, width, BASE);
    tpos = load_Bnode(tbowl, fp, width, pbowl->ptr[0]);
    while (tbowl->n >= 0)
	{
	if (tbowl->n <= M && pbowl->n != isBASE)
	    {
	    if (!borrow_key(fp, pi, width, fcmp))
		tpos = load_Bnode(tbowl, fp, width,
				  bind_node(fp, pi, width));
	    else
		tpos = load_Bnode(tbowl, fp, width, tpos);
	    }
	if ((ti = in_Bnode(key, tbowl, width, fcmp)) >= 0)
	    {
	    if (tbowl->ptr[0] == NILL) break;  /* found */
	    else   /* found but internal */
		make_swap(fp, key, width, ti);
	    }
	memcpy(pbowl, tbowl, NODESIZE);
	ppos = tpos;
	for (pi = 0; pi < pbowl->n && fcmp(key, KEY(pbowl, pi)) >= 0; pi++);
	tpos = load_Bnode(tbowl, fp, width, pbowl->ptr[pi]);
	}
    if (tbowl->n < 0) return NULL;  /* can't find */
    
    if (tbowl->n <= M && pbowl->n != isBASE)  /* external but less M */
	{
	if (!borrow_key(fp, pi, width, fcmp))
	    tpos = load_Bnode(tbowl, fp, width,
			      bind_node(fp, pi, width));
	else
	    tpos = load_Bnode(tbowl, fp, width, tpos);
	}
    delete_key(tbowl, in_Bnode(key, tbowl, width, fcmp), width);
    save_Bnode(tbowl, fp, width, tpos);
    (*num)--;
    return tbowl;
    }

void _list(FILE *fp, long ptr, size_t width, void (*fprt)(void*,int))
    {
    int i;
    static int x = 0;
    load_Bnode(tbowl, fp, width, ptr);
    if (tbowl->n > 0)
	{
	x += 2;
	for (i = 2; i < x; i++) printf("   ");
	for (i = 0; i < tbowl->n; i++)
	    fprt(KEY(tbowl, i), i==tbowl->n-1 ? 1 : 0);
	for (i = 0; i < tbowl->n+1; i++)
	    {
	    _list(fp, tbowl->ptr[i], width, fprt);
	    load_Bnode(tbowl, fp, width, ptr);
	    }
	x -= 2;
	}
    }

void Btree_list(FILE *fp, size_t width, void (*fprt)(void*,int))
    {
    load_Bnode(tbowl, fp, width, BASE);
    _list(fp, tbowl->ptr[0], width, fprt);
    }

void _sort(FILE *fp, long ptr, size_t width, void (*fprt)(void*))
    {
    int i, j;
    load_Bnode(tbowl, fp, width, ptr);
    if (tbowl->n > 0)
	{
	for (i = 0; i < tbowl->n; i++)
	    {
	    _sort(fp, tbowl->ptr[i], width, fprt);
	    load_Bnode(tbowl, fp, width, ptr);
	    fprt(KEY(tbowl, i));
	    _sort(fp, tbowl->ptr[i+1], width, fprt);
	    load_Bnode(tbowl, fp, width, ptr);
	    }
	}
    }

void Btree_sort(FILE *fp, size_t width, void (*fprt)(void*))
    {
    load_Bnode(tbowl, fp, width, BASE);
    _sort(fp, tbowl->ptr[0], width, fprt);
    }

