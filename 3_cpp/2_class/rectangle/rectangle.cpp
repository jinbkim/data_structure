#include "rectangle.h"

t_point::t_point(int new_x, int new_y)
{
	x = new_x;
	y = new_y;	
}

int		t_point::get_x(void) const
{
	return(x);
}

int		t_point::get_y(void) const
{
	return(y);
}



t_rectangle::t_rectangle(int x1, int y1, int x2, int y2)
				:up_left(x1, y1), low_right(x2, y2) 
{
	
}

void	t_rectangle::show_rect(void) const
{
	cout<<"up_left : <"<<up_left.get_x()<<", "<<up_left.get_y()<<">"<<endl;
	cout<<"low_right : <"<<low_right.get_x()<<", "<<low_right.get_y()<<">"<<endl;
}
