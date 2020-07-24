/*                                                           */
/*  BINSRCH.H  :   General Binary Searching Library header   */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#ifndef _BINSRCH_H
#define _BINSRCH_H

typedef int (*FCMP)(const void*, const void*);

int bv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int bv_insert(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int bv_delete(void *key, void *base, size_t *num, size_t width, FCMP fcmp);
int biv_search(void *key, void *base, size_t *num, size_t width, FCMP fcmp);




