/*                                                           */
/*  SORT.H   :   Sorting Library Header                      */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#ifndef _SORT_H
#define _SORT_H

extern int top;
extern int far *stack;

typedef int (*FCMP)(const void*, const void*);

#define init_stack()      (top = -1)
#define push(t)           (stack[++top] = t)
#define pop()             (stack[top--])
#define is_stack_empty()  (top < 0)

int make_stack(void);
void remove_stack(void);

void select_sort(void *base, size_t nelem, size_t width, FCMP fcmp);
void insert_sort(void*base, size_t nelem, size_t width, FCMP fcmp);
void bubble_sort(void *base, size_t nelem, size_t width, FCMP fcmp);

void shell_sort(void *base, size_t nelem, size_t width, FCMP fcmp);

void quick_sort1(void *base, size_t nelem, size_t width, FCMP fcmp);
void quick_sort2(void *base, size_t nelem, size_t width, FCMP fcmp);

void merge_sort(void *base, size_t nelem, size_t width, FCMP fcmp);

void downheap(void *base, size_t nelem, size_t width, FCMP fcmp, int k);
void heap_sort(void *base, size_t nelem, size_t width, FCMP fcmp);

void external_sort(FILE *src, FILE *dst, size_t width,
                   void *buf, size_t buflen, FCMP fcmp);

#endif


