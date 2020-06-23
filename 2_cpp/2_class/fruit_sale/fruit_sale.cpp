#include "fruit_sale.h"

t_fruit_seller::t_fruit_seller(int price, int num)
				: apple_price(price), apple_num(num), my_money(0)
{
	
}

int		t_fruit_seller::sale(int money)
{
	int		sale_count;
	
	sale_count = money / apple_price;
	apple_num -= sale_count;
	my_money += money;
	return (sale_count);
}

void	t_fruit_seller::show_sale(void)
{
	cout<<"----- sale result -----"<<endl;
	cout<<"leftover apples : "<<apple_num<<endl;
	cout<<"sales revenue : "<<my_money<<endl;	
}



void	t_fruit_buyer::buy(t_fruit_seller &fs, int money)
{
	apple_num += fs.sale(money);
	my_money -= money;
}

void	t_fruit_buyer::show_buy(void)
{
	cout<<"----- buy result -----"<<endl;
	cout<<"purchased apples : "<<apple_num<<endl;
	cout<<"leftover money : "<<my_money<<endl;	
}
