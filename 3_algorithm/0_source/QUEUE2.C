/*                                                           */
/*  QUEUE2.C  :  Queue using Double linked list              */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>

typedef struct _dnode
    {
    int key;
    struct _dnode *prev;
    struct _dnode *next;
    } dnode;

dnode *head, *tail;

void init_queue(void)
    {
    head = (dnode*)malloc(sizeof(dnode));
    tail = (dnode*)malloc(sizeof(dnode));
    head->prev = head;
    head->next = tail;
    tail->prev = head;
    tail->next = tail;
    }

void clear_queue(void)
    {
    dnode *t;
    dnode *s;
    t = head->next;
    while (t != tail)
        {
        s = t;
        t = t->next;
        free(s);
        }
    head->next = tail;
    tail->prev = head;
    }

int put(int k)
    {
    dnode *t;
    if ((t = (dnode*)malloc(sizeof(dnode))) == NULL)
        {
        printf("\n    Out of memory.");
        return -1;
        }
    t->key = k;
    tail->prev->next = t;
    t->prev = tail->prev;
    tail->prev = t;
    t->next = tail;
    return k;
    }

int get(void)
    {
    dnode *t;
    int i;
    t = head->next;
    if (t == tail)
        {
        printf("\n    Queue underflow.");
        return -1;
        }
    i = t->key;
    head->next = t->next;
    t->next->prev = head;
    free(t);
    return i;
    }

void print_queue(void)
    {
    dnode *t;
    t = head->next;
    printf("\n  Queue contents : Front ----> Rear\n");
    while (t != tail)
        {
        printf("%-6d", t->key);
        t = t->next;
        }
    }

void main(void)
    {
    int i;
    init_queue();

    printf("\nPut 5, 4, 7, 8, 2, 1");
    put(5);
    put(4);
    put(7);
    put(8);
    put(2);
    put(1);
    print_queue();

    printf("\nGet");
    i = get();
    print_queue();
    printf("\n   getting value is %d", i);

    printf("\nPut 3, 2, 5, 7");
    put(3);
    put(2);
    put(5);
    put(7);
    print_queue();

    printf("\nPut 3");
    put(3);
    print_queue();

    printf("\nInitialize queue");
    clear_queue();
    print_queue();

    printf("\nNow queue is empty, get");
    i = get();
    print_queue();
    printf("\n   getting value is %d", i);
    }
















