#include "employee.h"

employee::employee(const char * name)
{
	strcpy(this->name, name);
}

void	employee::show_name() const
{
	cout<<"name: "<<name<<endl;
}

int		employee::get_pay() const
{
	return (0);
}

void	employee::show_info() const
{
	show_name();
	cout<<"pay : "<<get_pay()<<endl;
}



emp_manage::emp_manage() : emp_num(0) {}

void	emp_manage::add_emp(employee *emp)
{
	emp_list[emp_num++] = emp;
}

void	emp_manage::show_all_info() const
{
	int	i;

	i = -1;
	while (++i < emp_num)
		emp_list[i]->show_info();
}

void	emp_manage::show_all_pay() const
{
	int	sum;
	int	i;

	sum = 0;
	i = -1;
	while (++i < emp_num)
		sum += emp_list[i]->get_pay();

	cout<<"pay sum : "<<sum<<endl;
}

emp_manage::~emp_manage()
{
	int	i;

	i = -1;
	while(++i < emp_num)
		delete emp_list[i];
}



regular_work::regular_work(const char *name, int money)
	: employee(name), money(money) {}

int		regular_work::get_pay() const
{
	return (money);
}

void	regular_work::show_info() const
{
	show_name();
	cout<<"pay : "<<get_pay()<<endl;
}



irregular_work::irregular_work(const char *name, int hour_pay)
	: employee(name), hour_time(0), hour_pay(hour_pay) {}

void	irregular_work::add_time(int hour_time)
{
	this->hour_time += hour_time;
}

int		irregular_work::get_pay() const
{
	return (hour_pay * hour_time);
}

void	irregular_work::show_info() const
{
	show_name();
	cout<<"pay : "<<get_pay()<<endl;
}



sales_work::sales_work(const char *name, int money, double bonus_money)
	: regular_work(name, money), sales(0), bonus_money(bonus_money) {}

void	sales_work::add_sales(int sales)
{
	this->sales = sales;
}

int		sales_work::get_pay() const
{
	return (regular_work::get_pay() + sales * bonus_money);
}

void	sales_work::show_info() const
{
	show_name();
	cout<<"pay : "<<get_pay()<<endl;
}



foreign_work::foreign_work(const char *name, int money, double bonus_money, char risk)
	: sales_work(name, money, bonus_money), risk(risk) {}

int		foreign_work::get_pay() const
{
	return (sales_work::get_pay() * (((double)risk / 10) + 1));
}

void	foreign_work::show_info() const
{
	show_name();
	cout<<"pay : "<<sales_work::get_pay()<<endl;
	cout<<"risk pay : "<<(sales_work::get_pay() / 10 * risk)<<endl;
	cout<<"total pay : "<<get_pay()<<endl<<endl;
}