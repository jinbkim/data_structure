#include "employee.h"

int		main(void)
{
	emp_manage		emp;
	irregular_work	*alba;
	sales_work		*sales;

	emp.add_emp(new regular_work("kim", 1000));
	emp.add_emp(new regular_work("lee", 1500));

	alba = new irregular_work("jung", 700);
	alba->add_time(5);
	emp.add_emp(alba);

	sales = new sales_work("hong", 1000, 0.1);
	sales->add_sales(7000);
	emp.add_emp(sales);



}