#include "calculator.h"

void	t_cal::show_cal_count(void)
{
	cout<<"plus : "<<count[0]<<endl;
	cout<<"minus : "<<count[1]<<endl;
	cout<<"multiple : "<<count[2]<<endl;
	cout<<"division : "<<count[3]<<endl;
}
void	t_cal::init(void)
{
	int i;
	
	i = -1;
	while (++i < 4)
		count[i] = 0;
}

double	t_cal::cal_add(double n1, double n2)
{
	count[0]++;
	return (n1 + n2);
}

double	t_cal::cal_min(double n1, double n2)
{
	count[1]++;
	return (n1 - n2);
}

double	t_cal::cal_mul(double n1, double n2)
{
	count[2]++;
	return (n1 * n2);
}

double	t_cal::cal_div(double n1, double n2)
{
	count[3]++;
	return (n1 / n2);
}
