/*                                                           */
/*  HARDCOPY.C :  Hardcopy routine for graphics mode         */
/*                                                           */
/*                Programmed By Lee jaekyu                   */
/*                                                           */

#include <graphics.h>
#include <bios.h>
#include "\tc\HARDCOPY.H"

#define ESC  0x1b

void wait_hardcopy(int port)
    {
    int key;
    key = bioskey(0) & 0x00ff;
    switch (key)
	{
	case '1' : hardcopy1(port);
		   break;
	case '2' : hardcopy2(port);
		   break;
	case '3' : hardcopy3(port);
		   break;
	}
    }

int hardcopy1(int port)
    {
    int mx, my;
    int x, y;
    int i, j;
    int col;
    int byte;

    if ((biosprint(2, 0, port) & 0x80) == 0)
	return 0;    /* printer is not ready */

    mx = getmaxx();
    my = getmaxy();

    biosprint(0, ESC, port);
    biosprint(0, '@', port);

    for (y = 0; y < my; y += 24)
	{
	biosprint(0, ESC, port);   /* set graphic mode */
	biosprint(0, '*', port);
	biosprint(0,  39, port);   /* 24 pin triple density */

	col = mx + 1;
	biosprint(0, col % 256, port);   /* set number of data */
	biosprint(0, col / 256, port);

	for (x = 0; x <= mx; x++)
	    {
	    for (i = 0; i < 24; i += 8)
		{
		byte = 0;
		for (j = 0; j < 8; j++)
		    {
                    byte <<= 1;
		    byte |= (getpixel(x, y + i + j) ? 1 : 0);
		    }
		biosprint(0, byte, port);  /* output image */
		}
	    }
        biosprint(0, ESC, port);
        biosprint(0, '3', port);
        biosprint(0, 24, port);

        biosprint(0, '\n', port);  /* line feed */
        biosprint(0, '\r', port);  /* carriage return */
	}
    biosprint(0, 0x0c, port);   /* form feed */
    return 1;   /* successful */
    }

int hardcopy2(int port)
    {
    int mx, my;
    int x, y;
    int i, j;
    int col;
    int byte;

    if ((biosprint(2, 0, port) & 0x80) == 0)
	return 0;    /* printer is not ready */

    mx = getmaxx();
    my = getmaxy();

    biosprint(0, ESC, port);
    biosprint(0, '@', port);

    for (y = 0; y < my; y += 12)
	{
	biosprint(0, ESC, port);   /* set graphic mode */
	biosprint(0, '*', port);
	biosprint(0,  33, port);   /* 24 pin double density */

	col = mx + 1;
	biosprint(0, col % 256, port);   /* set number of data */
	biosprint(0, col / 256, port);

	for (x = 0; x <= mx; x++)
	    {
	    for (i = 0; i < 12; i += 4)
		{
		byte = 0;
		for (j = 0; j < 4; j++)
		    {
                    byte <<= 2;
		    byte |= (getpixel(x, y + i + j) ? 3 : 0);
		    }
		biosprint(0, byte, port);  /* output image */
		}
	    }
        biosprint(0, ESC, port);
        biosprint(0, '3', port);
        biosprint(0, 24, port);

        biosprint(0, '\n', port);  /* line feed */
        biosprint(0, '\r', port);  /* carriage return */
	}
    biosprint(0, 0x0c, port);   /* form feed */
    return 1;   /* successful */
    }


int hardcopy3(int port)
    {
    int mx, my;
    int x, y;
    int i, j;
    int col;
    int byte;

    if ((biosprint(2, 0, port) & 0x80) == 0)
	return 0;    /* printer is not ready */

    mx = getmaxx();
    my = getmaxy();

    biosprint(0, ESC, port);
    biosprint(0, '@', port);

    for (y = 0; y < my; y += 8)
	{
	biosprint(0, ESC, port);   /* set graphic mode */
	biosprint(0, '*', port);   /* 8 pin single density mode */
        biosprint(0,   0, port);

	col = mx + 1;
	biosprint(0, col % 256, port);   /* set number of data */
	biosprint(0, col / 256, port);

	for (x = 0; x <= mx; x++)
	    {
            byte = 0;
	    for (j = 0; j < 8; j++)
                {
                byte <<= 1;
		byte |= (getpixel(x, y + j) ? 1 : 0);
		}
	    biosprint(0, byte, port);  /* output image */
	    }
        biosprint(0, ESC, port);
        biosprint(0, '3', port);
        biosprint(0, 24, port);

        biosprint(0, '\n', port);  /* line feed */
        biosprint(0, '\r', port);  /* carriage return */
	}
    biosprint(0, 0x0c, port);   /* form feed */
    return 1;   /* successful */
    }


