#include "employee.h"

int		main(void)
{
	employee	emp;

	emp.add_man(new information("kim", 100));
	emp.add_man(new information("jin", 200));
	emp.add_man(new information("bum", 300));

	emp.show();
}