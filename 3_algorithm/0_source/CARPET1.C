/*                                                           */
/*  CARPET1.C  :  Fractal carpet                             */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <bios.h>
#include "c:\tc\hardcopy.h"

void box(int x, int y, int r, int color)
    {
    int i;
    setcolor(color);
    for (i = y-r; i <= y+r; i++)
	line(x-r, i, x+r, i);
    }

void carpet1(int x, int y, int r, int order)
    {
    if (order > 0)
	{
	carpet1(x - 2*r/3, y + 2*r/3, r/3, order-1);
	carpet1(x - 2*r/3, y        , r/3, order-1);
	carpet1(x - 2*r/3, y - 2*r/3, r/3, order-1);
	carpet1(x        , y + 2*r/3, r/3, order-1);
	carpet1(x        , y - 2*r/3, r/3, order-1);
	carpet1(x + 2*r/3, y + 2*r/3, r/3, order-1);
	carpet1(x + 2*r/3, y        , r/3, order-1);
	carpet1(x + 2*r/3, y - 2*r/3, r/3, order-1);
	box(x, y, r/3, BLACK);
        }
    }

void main(void)
    {
    int i;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    if (graphresult() != grOk) exit(1);
    for (i = 1; i < 6; i++)
	{
	box(getmaxx()/2, getmaxy()/2, 240, WHITE);
	carpet1(getmaxx()/2, getmaxy()/2, 240, i);
	wait_hardcopy(LPT1);
	cleardevice();
	}
    closegraph();
    }

