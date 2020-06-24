#ifndef	FRUIT_SALE_H
 #define FRUIT_SALE_H

#include <iostream>

using std::cout;
using std::endl;

class	t_fruit_seller
{
	const int	apple_price;
	int			apple_num;
	int			my_money;
public:	
	t_fruit_seller(int price, int num);
	int		sale(int money);
	void	show_sale(void);
	
};

class	t_fruit_buyer
{
	int		apple_num;
	int		my_money;	
public:
	t_fruit_buyer(int money)
	{
		apple_num = 0;
		my_money = money;
	}
	void	buy(t_fruit_seller &fs, int money);
	void	show_buy(void);
};

#endif
