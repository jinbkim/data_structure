#ifndef	EMPLOYEE_H
 #define EMPLOYEE_H

#include <iostream>
#include <cstring>

using	std::cout;
using	std::endl;

enum
{
	RISC_C = 1,
	RISC_B = 2,
	RISC_A = 3
};

class	employee
{
	char	name[100];

public:
	employee(const char * name);

	void show_name() const;
	virtual int	get_pay() const;
	virtual void show_info() const;
};

class	emp_manage
{
	employee	*emp_list[100];
	int			emp_num;

public:
	emp_manage();

	void	add_emp(employee *emp);
	void	show_all_info() const;
	void	show_all_pay() const;

	~emp_manage();
};

class	regular_work : public employee
{
	int	money;

public:
	regular_work(const char *name, int money);

	int		get_pay() const;
	void	show_info() const;
};

class	irregular_work : public employee
{
	int	hour_time;
	int	hour_pay;

public:
	irregular_work(const char *name, int hour_pay);

	void	add_time(int hour_time);
	int		get_pay() const;
	void	show_info() const;
};

class	sales_work : public regular_work
{
	int		sales;
	double	bonus_money;

public:
	sales_work(const char *name, int money, double bonus_money);

	void	add_sales(int sales);
	int		get_pay() const;
	void	show_info() const;
};

class	foreign_work : public sales_work
{
	char	risk;
public:
	foreign_work(const char *name, int money, double bonus_money, char risk);

	int		get_pay() const;
	void	show_info() const;
};
#endif