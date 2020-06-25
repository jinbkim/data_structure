#ifndef	EMPLOYEE_H
 #define EMPLOYEE_H

#include <iostream>
#include <cstring>

using	std::cout;
using	std::endl;
using	std::size_t;

class	information
{
	char	name[100];
	int		pay;

public:
	information(const char *name, int pay);

	void	show() const;
};

class	employee
{
	information	*mans[100];
	int			man_num;

public:
	employee();

	void	add_man(information *man);
	void	show(void) const;

	~employee(void);
};

#endif