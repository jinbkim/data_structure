/*                                                           */
/*  LINSRCH.H  :   Linear Searching Library Header           */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#ifndef _LINSRCH_H
#define _LINSRCH_H

typedef int (*FCMP)(const void*, const void*);

int lv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int lfv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);

#endif





