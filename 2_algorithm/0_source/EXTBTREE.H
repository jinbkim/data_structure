/*                                                           */
/*  EXTBTREE.H  :  External B-tree Libaray Header            */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#ifndef _EXTBTREE_H
#define _EXTBTREE_H

#define M   2

typedef int (*FCMP)(const void*, const void*);
typedef struct _Bnode
    {
    int n;
    long ptr[M*2+2];
    } Bnode;

FILE *init_Btree(char *fname, size_t *num, size_t width);
void close_Btree(FILE *fp, size_t *num);
void *Btree_search(FILE *fp, void *key, size_t *num, size_t width, FCMP fcmp);
void *Btree_insert(FILE *fp, void *key, size_t *num, size_t width, FCMP fcmp);
void *Btree_delete(FILE *fp, void *key, size_t *num, size_t width, FCMP fcmp);
void Btree_list(FILE *fp, size_t width, void (*fprt)(void*,int));
void Btree_sort(FILE *fp, size_t width, void (*fprt)(void*));

#endif
