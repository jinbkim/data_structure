#include "calculator.h"

int		main(void)
{
	t_cal	cal;
	
	cal.init();
	cout<<"1.1 + 2.2 = "<<cal.cal_add(1.1, 2.2)<<endl;
	cout<<"3.3 + 2.2 = "<<cal.cal_add(3.3, 2.2)<<endl;
	cout<<"3.3 - 2.2 = "<<cal.cal_min(3.3, 2.2)<<endl;
	cout<<"3.3 * 2.2 = "<<cal.cal_mul(3.3, 2.2)<<endl;
	cout<<"3.3 / 2.2 = "<<cal.cal_div(3.3, 2.2)<<endl;
	cal.show_cal_count();
}
