/*                                                           */
/*  FILL1.C   :   Recursive fill algorithm                   */
/*                                                           */
/*                Programmed By Lee jaekyu                   */
/*                                                           */

#include <stdio.h>
#include <bios.h>
#include <graphics.h>
#include <stdlib.h>

#define MAX  8000

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

void recur_fill(int x, int y, int color, int border)
    {   /* recursive fill by pixel algorithm */
    if (getpixel(x, y) == color || getpixel(x, y) == border)
	return;
    else
	{
	putpixel(x, y, color);
	recur_fill(x - 1, y, color, border);
	recur_fill(x + 1, y, color, border);
	recur_fill(x, y - 1, color, border);
	recur_fill(x, y + 1, color, border);
	}
    }

void stack_fill(int x, int y, int color, int border)
    {   /* iterative fill by pixel algorithm using stack */
    init_stack();
    push(y);
    push(x);
    while (!is_stack_empty())
	{
	x = pop();
	y = pop();
	if (getpixel(x, y) == color || getpixel(x, y) == border)
	    continue;
	putpixel(x, y,color);
	push(y + 1);
	push(x);
	push(y - 1);
	push(x);
	push(y);
	push(x + 1);
	push(y);
	push(x - 1);
	}
    }

void main(void)
    {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    if (graphresult() != grOk)
	{
	printf("\nGraphic system error!");
	exit(1);
	}
    outtextxy(50, 150, "Recusive pixel fill");
    circle(100, 200, 20);
    recur_fill(100, 200, getcolor(), getcolor());
    outtextxy(350, 150, "Iterative pixel fill using stack");
    circle(400, 200, 20);
    stack_fill(400, 200, getcolor(), getcolor());
    bioskey(0);
    }






