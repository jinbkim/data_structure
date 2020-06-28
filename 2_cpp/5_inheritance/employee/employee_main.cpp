#include "employee.h"

int		main(void)
{
	emp_manage		emp;
	foreign_work	*fsales;

	fsales = new foreign_work("hong", 1000, 0.1, RISC_A);
	fsales->add_sales(7000);
	emp.add_emp(fsales);

	fsales = new foreign_work("yoon", 1000, 0.1, RISC_B);
	fsales->add_sales(7000);
	emp.add_emp(fsales);

	fsales = new foreign_work("lee", 1000, 0.1, RISC_C);
	fsales->add_sales(7000);
	emp.add_emp(fsales);

	emp.show_all_info();

	/*
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

	emp.show_all_info();
	emp.show_all_pay();
	*/
}