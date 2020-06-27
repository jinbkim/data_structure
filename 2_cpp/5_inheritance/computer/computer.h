#ifndef COMPUTER_H
 #define COMPUTER_H

#include <iostream>
#include <cstring>

using	std::cout;
using	std::endl;

#define STR_SIZE	100

class	computer
{
	char	name[STR_SIZE];

public:
	computer(const char *name);

	void	cal();
};

class	notebook : public computer
{
	int		battary;

public:
	notebook(const char *name, int battary);

	void	charging();
	void	use_battary();
	void	moving_cal();
	int		get_battary();
};

class	tablet : public notebook
{
	char	pen[STR_SIZE];

public:
	tablet(const char *name, int battary, const char *pen);

	void	write(const char *pen);
};


#endif