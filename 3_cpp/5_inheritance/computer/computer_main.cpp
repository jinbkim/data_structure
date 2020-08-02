#include "computer.h"

int		main(void)
{
	notebook	nb("kim", 5);
	tablet		tab("kim", 5, "1234");

	nb.moving_cal();
	tab.write("1234");
}