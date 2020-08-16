#include "printer.h"

void	t_printer::set_str(const char *s)
{
	strcpy(str, s);
}

void	t_printer::show_str(void)
{
	cout<<str<<endl;
}
