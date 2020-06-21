#include "car.h"

int		main(void)
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
