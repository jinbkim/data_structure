#ifndef	RECTANGLE_H
 #define RECTANGLE_H

#include <iostream>

using std::cout;
using std::endl;

class	t_point
{
	int	x;
	int	y;

public:
	t_point(int new_x, int new_y);
	int		get_x(void) const;
	int		get_y(void) const;
};

class	t_rectangle
{
	t_point	up_left;
	t_point	low_right;

public:	
	t_rectangle(int	x1, int y1, int x2, int y2);
	void	show_rect(void) const;
};

#endif
