/*                                                           */
/*  LLINSRCH.C  :   Linear Search Linked list version header */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#ifndef _LLINSRCH_H
#define _LLINSRCH_H

typedef struct _node { struct _node *next; } node;
typedef int (*FCMP)(const void*, const void*);

void init_list(node **p, node **q);
void *llv_search(void *key, node *base, size_t *num, size_t width, FCMP fcmp);
void *llv_insert(void *key, node *base, size_t *num, size_t width, FCMP fcmp);
void *llv_delete(void *key, node *base, size_t *num, size_t width, FCMP fcmp);
void *llfv_search(void *key, node *base, size_t *num, size_t width, FCMP fcmp);
void *llv_deleteall(node *base, node *end);

#endif






