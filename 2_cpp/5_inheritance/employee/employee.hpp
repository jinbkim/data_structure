#include "employee.h"

information::information(char *name, int pay)
{
	strcpy(this->name, name);
	this->pay = pay;
}

void	information::show() const
{
	cout<<"name : "<<name<<endl;
	cout<<"pay : "<<pay<<endl;
}



employee::employee(void)
	: man_num(0) {}

void	employee::add_man(employee *man)
{
	mans[man_num++] = man;
}

void	employee::show(void) const
{
	int i;

	i = -1;
	while (++i < man_num)
		mans[i]->show();
}

employee::~employee(void)
{
	int i;

	i = -1;
	while(++i < man_num)
		delete mans[i];
}