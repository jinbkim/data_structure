/*                                                           */
/*  QUEUE1.C  :  Circular Queue using array                  */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>

#define MAX  10

int queue[MAX];
int front, rear;

void init_queue(void)
    {
    front = rear = 0;
    }

void clear_queue(void)
    {
    front = rear;
    }

int put(int k)
    {
    if ((rear + 1) % MAX == front)   /* queue is full */
        {
        printf("\n    Queue overflow.");
        return -1;
        }
    queue[rear] = k;
    rear = ++rear % MAX;
    return k;
    }

int get(void)
    {
    int i;
    if (front == rear)   /* queue is empty */
        {
        printf("\n    Queue underflow.");
        return -1;
        }
    i = queue[front];
    front = ++front % MAX;
    return i;
    }

void print_queue(void)
    {
    int i;
    printf("\n  Queue contents : Front ----> Rear\n");
    for (i = front; i != rear; i = ++i % MAX)  /* caution */
        printf("%-6d", queue[i]);
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

    printf("\nNow queue is full, put 3");
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













