/*                                                           */
/*  HCDEMO.C  :  Demonstration for Hardcopy routine          */
/*                                                           */
/*                Programmed By Lee jaekyu                   */
/*                                                           */

#include <stdio.h>
#include <graphics.h>
#include <bios.h>
#include "hardcopy.h"

void main(void)
    {
    int gd = DETECT, gm;
    int i;
    int mx, my;

    initgraph(&gd, &gm, "\\tc\\bgi");  /* initialize graphics mode */
    if (graphresult() != grOk)
	{
	puts("\nGraphics Error!");
	return;
	}

    mx = getmaxx();
    my = getmaxy();
    for (i = 0; i <= mx; i += 5)
        {
        line(320, 200, i, 0);
        line(320, 200, i, my);
        }
    for (i = 0; i <= my; i += 5)
        {
        line(320, 200, 0, i);
        line(320, 200, mx, i);
        }
    outtextxy(10, 300, "Hit any key to print screen...");
    bioskey(0);

    if (!hardcopy2(LPT1))
	{
	outtextxy(10, 320, "Printer is not ready...");
	bioskey(0);
	}
    }


