#include "name_card.h"

int		main(void)
{
    name_card   man1("kim", "naver", "010-1111-1111", COMP_POSS::iron);
    name_card   man2 = man1;
    man1.show_info();
    man2.show_info();
}
