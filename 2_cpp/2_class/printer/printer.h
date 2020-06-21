#ifndef	PRINTER_H
 #define PRINTER_H

#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

#define STR_SIZE	100

class	t_printer
{
	char	str[STR_SIZE];
public:
	void	set_str(const char *s);
	void	show_str();
		
};

#endif
