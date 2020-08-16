#ifndef	CAR_H
 #define CAR_H

#include <iostream>
#include <cstring>

using std::cout;
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
	char	id[CAR_CONST::ID_SIZE];
	int		fuel;
	int		speed;
public:
	void	init_car(const char *new_id, int new_fuel);
	void	show_car();
	void	accel();
	void	stop();	
};

#endif
