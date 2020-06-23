#include "circle.h"

void	point::show(void) const
{
	cout<<"<"<<x<<", "<<y<<">"<<endl;
}



void	circle::show(void) const
{
	po.show();
	cout<<"radius : "<<rad<<endl;
}



void	ring::show(void) const
{
	cout<<"-----inner circle -----"<<endl;
	c1.show();

	cout<<"-----outter circle -----"<<endl;
	c2.show();
}