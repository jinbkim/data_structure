#ifndef CALCULATOR_H
 #define CALCULATOR_H

#include <iostream>

using	std::cout;
using	std::endl;



class	t_cal
{
	// 0 : +, 1 : -, 2 : *, 3 : /
//private:
	int		count[4];

public:	
	void	show_cal_count();
	void	init();
	
	double	cal_add(double n1, double n2);
	double	cal_min(double n1, double n2);
	double	cal_mul(double n1, double n2);
	double	cal_div(double n1, double n2);
};

#endif
