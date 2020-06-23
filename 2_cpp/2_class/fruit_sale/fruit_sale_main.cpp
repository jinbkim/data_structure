#include "fruit_sale.h"

int		main(void)
{
	t_fruit_seller	fs(1000, 20);
	t_fruit_buyer	fb(5000);

	fb.buy(fs, 2000);

	fs.show_sale();
	fb.show_buy();
}
