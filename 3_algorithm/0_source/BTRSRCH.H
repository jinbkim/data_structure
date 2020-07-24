/*                                                           */
/*  BTRSRCH.H  :  Binary tree Searching Library header       */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#ifndef _BTRSRCH_H
#define _BTRSRCH_H

#define NODE 1
#define LINK 2
#define TAIL 4

typedef struct _node
    {
    struct _node *left;
    struct _node *right;
    } node;

typedef int (*FCMP)(const void*, const void*);

void init_tree(node **p);
void *btv_search(void *key, node *base, size_t *num, size_t width, FCMP fcmp);
void *btv_insert(void *key, node *base, size_t *num, size_t width, FCMP fcmp);
void *btv_delete(void *key, node *base, size_t *num, size_t width, FCMP fcmp);
void *btv_deleteall(node *base, size_t *num);
void btv_list(node *p, void (*fptr)(void*));
void btv_draw(node *p, void (*fptr)(void*,char*), int mode);
void btv_sort_list(node *p, void (*fpr)(void*));
void btv_balance(node *base, size_t *num, size_t width);

#endif










