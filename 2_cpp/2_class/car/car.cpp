#include "car.h"

void		t_car::accel()
{
	if (fuel <= 0)
		return ;
	else
		fuel -= CAR_CONST::DECREASE_FUEL;
		
	if (speed + CAR_CONST::INCREASE_ACCEL >= CAR_CONST::MAX_SPEED)
	{
		speed = CAR_CONST::MAX_SPEED;
		return ;
	}
	
	speed += CAR_CONST::INCREASE_ACCEL;
}

void		t_car::show_car(void)
{
	cout<<"id : "<<id<<endl;
	cout<<"fuel : "<<fuel<<endl;
	cout<<"speed : "<<speed<<endl;
}

void		t_car::stop(void)
{
	if (speed < CAR_CONST::INCREASE_STOP)
	{
		speed = 0;
		return ;
	}
	
	speed -= CAR_CONST::INCREASE_STOP;
}
