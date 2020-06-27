#ifndef	EMPLOYEE_H
 #define EMPLOYEE_H

#include <iostream>
#include <cstring>

using	std::cout;
using	std::endl;
using	std::size_t;

class	employee
{
	char	name[100];

public:
	employee(const char * name);

	void show() const;
};

class	emp_manage
{
	employee	*emp_list[100];
	int			emp_num;

public:
	emp_manage();

	void	add_emp(employee *emp);
};

class	regular_work : public employee
{
	int	money;

public:
	regular_work(const char *name, int money);
};

class	irregular_work : public employee
{
	int	hour_time;
	int	hour_pay;

public:
	irregular_work(const char *name, int hour_pay);

	void	add_time(int hour_time);
};

class	sales_work : public regular_work
{
	int		sales;
	double	bonus_money;

public:
	sales_work(const char *name, int money, double bonus_money);

	void	add_sales(int sales);
};

#endif