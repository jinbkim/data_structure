#include "employee.h"

employee::employee(const char * name)
{
	strcpy(this->name, name);
}

void employee::show() const
{
	cout<<"name: "<<name<<endl;
}


emp_manage::emp_manage() : emp_num(0) {}

void	emp_manage::add_emp(employee *emp)
{
	emp_list[emp_num++] = emp;
}



regular_work::regular_work(const char *name, int money)
	: employee(name), money(money) {}



irregular_work::irregular_work(const char *name, int hour_pay)
	: employee(name), hour_time(0), hour_pay(hour_pay) {}

void	irregular_work::add_time(int hour_time)
{
	this->hour_time += hour_time;
}



sales_work::sales_work(const char *name, int money, double bonus_money)
	: regular_work(name, money), sales(0), bonus_money(bonus_money) {}

void	sales_work::add_sales(int sales)
{
	this->sales = sales;
}
