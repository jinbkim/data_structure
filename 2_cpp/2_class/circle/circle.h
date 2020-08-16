#ifndef	CIRCLE_H
 #define CIRCLE_H

#include <iostream>

using std::cout;
using std::endl;

class	point
{
	int	x;
	int	y;

public:
	point(int my_x, int my_y)
		: x(my_x), y(my_y){}
		/*
	{
		x = my_x;
		y = my_y;
	}
	*/
	void	show(void) const;
};

class	circle
{
	point	po;
	int		rad;

public:
	circle(int x, int y, int r)
		: po(x,y), rad(r){}
	/*
	{
		po(x, y);
		rad = r;
	}
	*/
	void	show(void) const;
};

class	ring
{
	circle	c1;
	circle	c2;

public:
	ring(int x1, int y1, int r1, int x2, int y2, int r2)
		:c1(x1, y1, r1), c2(x2, y2, r2) {}
	void	show(void) const;
};

#endif
