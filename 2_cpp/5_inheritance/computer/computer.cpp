#include "computer.h"

computer::computer(const char *name)
{
	strcpy(this->name, name);
}

void	computer::cal()
{
	cout<<"calculating!"<<endl;
}



notebook::notebook(const char *name, int battary)
	: computer(name), battary(battary) {}

void	notebook::charging()
{
	battary += 5;
}

void	notebook::use_battary()
{
	battary -= 1;
}

void	notebook::moving_cal()
{
	if (get_battary() < 1)
	{
		cout<<"need charging"<<endl;
		return ;
	}

	cout<<"moving, ";
	cal();
	use_battary();
}

int		notebook::get_battary()
{
	return (battary);
}




tablet::tablet(const char *name, int battary, const char *pen)
	: notebook(name, battary)
{
	strcpy(this->pen, pen);
}

void	tablet::write(const char *pen)
{
	if (get_battary() < 1)
	{
		cout<<"need charging"<<endl;
		return ;
	}

	if (strcmp(this->pen, pen))
	{
		cout<<"not pen registered!"<<endl;
		return ;
	}

	cout<<"pen is using!"<<endl;
	use_battary();
}
