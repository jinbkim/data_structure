#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

namespace	CAR_CONST
{
	enum
	{
		ID_SIZE = 20,
		DECREASE_FUEL = 2,
		INCREASE_ACCEL = 10,
		MAX_SPEED = 200,
		INCREASE_STOP = 10
	};
}

class	t_car
{
private:
	char	id[CAR_CONST::ID_SIZE];
	int		fuel;
	int		speed;
public:
	void	init_car(const char *new_id, int new_fuel);
	void	show_car();
	void	accel();
	void	stop();	
};



int			main(void)
{
	t_car	car;
	
	car.init_car("tayo", 100);
	car.accel();
	car.accel();
	car.accel();
	car.show_car();
	car.stop();
	car.show_car();
}



void		t_car::init_car(const char *new_id, int new_fuel)
{
	strcpy(id,new_id);
	fuel = new_fuel;
	speed = 0;
}

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
