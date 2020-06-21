#include "printer.h"

int		main(void)
{
	t_printer	pnt;
	
	pnt.set_str("hello!");
	pnt.show_str();
	
	pnt.set_str("bye!");
	pnt.show_str();
}
