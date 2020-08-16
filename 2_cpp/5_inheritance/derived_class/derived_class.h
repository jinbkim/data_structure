#ifndef	DERIVED_CLASS_H
 #define DERIVED_CLASS_H

#include <iostream>
#include <cstring>

using	std::cout;
using	std::endl;

class	b_class
{
	int	b_num;

public:
	b_class();
	b_class(int);

	void	show_base();
};

class	d_class : public b_class
{
	int	d_num;

public:
	d_class();
	d_class(int);
	d_class(int, int);

	void	show_derived(void);
};

#endif