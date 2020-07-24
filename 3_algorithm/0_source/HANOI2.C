/*                                                           */
/*  HANOI2.C  :  Hanoi tower Nonrecursive version            */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>

#define MAX  500

int stack[MAX];
int top;

void init_stack(void)
    {
    top = -1;
    }

int push(int t)
    {
    if (top >= MAX - 1)
        {
        printf("\n    Stack overflow.");
        return -1;
        }
    stack[++top] = t;
    return t;
    }

int pop(void)
    {
    if (top < 0)
        {
        printf("\n    Stack underflow.");
        return -1;
        }
    return stack[top--];
    }

int is_stack_empty(void)
    {
    return (top == -1);
    }

void move(int from, int to)
    {
    printf("\nMove from %d to %d", from, to);
    }

void nr_hanoi(int n, int from, int by, int to)
    {
    int done = 0;
    init_stack();
    while (!done)
        {
        while (n > 1)
            {
            push(to);    /* save local var to stack */
            push(by);
            push(from);
            push(n);
            n--;         /* change local var for first recursion */
            push(to);
            to = by;
            by = pop();
            }
        move(from, to);  /* process when terminate condition */
        if (!is_stack_empty())
            {
            n = pop();   /* load local var from stack */
            from = pop();
            by = pop();
            to = pop();
            move(from, to);  /* process inorder */
            n--;         /* change local var for second recursion */
            push(from);
            from = by;
            by = pop();
            }
        else
            done = 1;    /* if stack is empty, then quit */
        }
    }

void main(void)
    {
    int i = 0;
    printf("\nIf you want to quit, enter minus integer.");
    while (1)
        {
        printf("\nEnter height of HANOI tower -> ");
        scanf("%d", &i);
        if (i <= 0) break;
        nr_hanoi(i, 1, 2, 3);
        }
    }

