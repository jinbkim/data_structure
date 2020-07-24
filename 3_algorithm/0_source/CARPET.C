/*                                                           */
/*  CARPET.C  :  Fractal carpet by recursion                 */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <bios.h>

void box(int x, int y, int r)
    {
    int i;
    setcolor(WHITE);
    for (i = y-r/3; i <= y+r/3; i++)
	line(x-r/3, i, x+r/3, i);
    }

void carpet1(int x, int y, int r)
    {
    if (r > 0)
        {
	carpet1(x - 2*r, y + 2*r, r/3);
	carpet1(x - 2*r, y      , r/3);
	carpet1(x - 2*r, y - 2*r, r/3);
	carpet1(x      , y + 2*r, r/3);
	carpet1(x      , y - 2*r, r/3);
	carpet1(x + 2*r, y + 2*r, r/3);
	carpet1(x + 2*r, y      , r/3);
	carpet1(x + 2*r, y - 2*r, r/3);
	box(x, y, r);
        }
    }

void carpet2(int x, int y, int r)
    {
    if (r > 0)
	{
	box(x, y, r);
	carpet2(x - 2*r, y + 2*r, r/2);
	carpet2(x - 2*r, y      , r/2);
	carpet2(x - 2*r, y - 2*r, r/2);
	carpet2(x      , y + 2*r, r/2);
	carpet2(x      , y - 2*r, r/2);
	carpet2(x + 2*r, y + 2*r, r/2);
	carpet2(x + 2*r, y      , r/2);
	carpet2(x + 2*r, y - 2*r, r/2);
	}
    }

void carpet3(int x, int y, int r)
    {
    if (r > 0)
	{
	carpet3(x - r, y + r, r/2);
	carpet3(x + r, y + r, r/2);
	carpet3(x - r, y - r, r/2);
	carpet3(x + r, y - r, r/2);
	box(x, y, r);
	}
    }

void main(void)
    {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    if (graphresult() != grOk)
        {
        printf("\nGraphic system error ! ");
        exit(1);
	}
    carpet1(getmaxx()/2, getmaxy()/2, 60);
    bioskey(0);
    cleardevice();
    carpet2(getmaxx()/2, getmaxy()/2, 50);
    bioskey(0);
    cleardevice();
    carpet3(getmaxx()/2, getmaxy()/2, 100);
    bioskey(0);
    closegraph();
    }

