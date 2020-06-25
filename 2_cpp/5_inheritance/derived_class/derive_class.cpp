#include "derived_class.h"

b_class::b_class() : b_num(20)
{
	cout<<"base class()!"<<endl;
}

b_class::b_class(int n) : b_num(n)
{
	cout<<"base class(n)!"<<endl;
}

void	b_class::show_base()
{
	cout<<"base class : "<<b_num<<endl;
}



d_class::d_class() : d_num(30)
{
	cout<<"derived class()!"<<endl;
}

d_class::d_class(int n) : d_num(n)
{
	cout<<"derived class(n)!"<<endl;
}

d_class::d_class(int n1, int n2) : b_class(n1), d_num(n2)
{
	cout<<"derived class(n)!"<<endl;
}

void	d_class::show_derived(void)
{
	show_base();
	cout<<"derived class : "<<d_num<<endl;
}