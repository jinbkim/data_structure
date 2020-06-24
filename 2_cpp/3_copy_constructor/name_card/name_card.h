#ifndef	NAME_CARD_H
 #define NAMECARD_H

#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

namespace COMP_POSS
{
    enum {iron, bronze, silver, gold};
}

class   name_card
{
    char    *name;
    char    *company;
    char    *phone;
	char	*pos;

public:
    name_card(const char *my_name, const char *my_company, const char *my_phone, int my_position);
    name_card(name_card &copy);
    void    show_info(void);

	~name_card();

};

#endif