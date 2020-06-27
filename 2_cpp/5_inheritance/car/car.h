#ifndef	CAR_H
 #define CAR_H

#include <iostream>

using	std::cout;
using	std::endl;

class	car
{
	int	gas;

public:
	car(int gas);

	int		get_gas();
};

class	h_car : public car
{
	int	elec;

public:
	h_car(int gas, int elec);

	int		get_elec();
};

class	w_car : public h_car
{
	int water;

public:
	w_car(int gas, int elec, int water);

	int		get_water();
	void	show();
};

#endif