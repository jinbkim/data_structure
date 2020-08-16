#ifndef	EMPLOYEE_H
 #define EMPLOYEE_H

#include <iostream>
#include <cstring>

#define STR_MAX	100

using	std::cout;
using	std::endl;

class	person
{
	char	name[STR_MAX];
	int		age;

public:
	person(const char *name, int age);

	void	show_name(void) const;
	void	show_age(void) const;
};

class	university : public person
{
	char	major[STR_MAX];

public:
	university(const char *name, int age, const char *major);
	void	show_all(void) const;
};

#endif