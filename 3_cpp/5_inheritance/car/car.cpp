#include "car.h"

car::car(int gas) : gas(gas) {}

int		car::get_gas()
{
	return (gas);
}



h_car::h_car(int gas, int elec) : car(gas), elec(elec) {}

int		h_car::get_elec()
{
	return (elec);
}



w_car::w_car(int gas, int elec, int water) : h_car(gas, elec), water(water) {}

int		w_car::get_water()
{
	return (water);
}

void	w_car::show()
{
	cout<<"gas : "<<gas<<endl;
	cout<<"electronic : "<<get_elec()<<endl;
	cout<<"water : "<<get_water()<<endl;
}
