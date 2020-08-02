/*                                                           */
/*  SCHASH.H  :  Hashing Library  header                     */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#ifndef _SCHASH_H
#define _SCHASH_H

typedef int (*FCMP)(const void*, const void*);
typedef int (*HASH)(const void*);

typedef struct _node
    {
    struct _node *next;
    } node;

node *hsc_init(node **base, size_t *num, size_t N);
node *hsc_deleteall(node *base, size_t *num, size_t N);
void *hsc_search(void *key, node *base, size_t *num, size_t width,
		 FCMP fcmp, HASH hash);
void *hsc_insert(void *key, node *base, size_t *num, size_t width,
		 FCMP fcmp, HASH hash);
void *hsc_delete(void *key, node *base, size_t *num, size_t width,
		 FCMP fcmp, HASH hash);
void hsc_list(node *base, int N, void (*fprt)(void*));

#endif

