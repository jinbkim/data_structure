/*                                                           */
/*  LINE.C  :   Recusive line drawing                        */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <bios.h>
#include <graphics.h>

void recursive_line(int x1, int y1, int x2, int y2, int color)
    {
    if (x1-x2 <= 1 && x1-x2 >= -1 && y1-y2 <= 1 && y1-y2 >= -1)

        return;
    else
        {
        putpixel((x1 + x2)/2, (y1 + y2)/2, color);
        recursive_line(x1, y1, (x1 + x2)/2, (y1 + y2)/2, color);
        recursive_line(x2, y2, (x1 + x2)/2, (y1 + y2)/2, color);
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

    recursive_line(10, 10, 600, 350, WHITE);
    bioskey(0);
    }