/*                                                           */
/*  RBTRSRCH.H  :  Red-Black tree Libaray header             */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#ifndef _RBTRSRCH_H
#define _RBTRSRCH_H

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

void init_tree(node **p);
void *rbtr_search(void *key,node *base,size_t *num,size_t width,FCMP fcmp);
void *rbtr_insert(void *key,node *base,size_t *num,size_t width,FCMP fcmp);
void *rbtr_delete(void *key,node *base,size_t *num,size_t width,FCMP fcmp);
node *rbtr_deleteall(node *base, size_t *num);
void rbtr_list(node *p, void (*fprt)(void*,int));
void rbtr_sort(node *p, void (*fprt)(void*,int));
void rbtr_draw(node *p, int mode, void (*fnode)(void*,char*));

#endif






