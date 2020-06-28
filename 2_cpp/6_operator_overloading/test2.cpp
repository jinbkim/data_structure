#include <iostream>

using	std::cout;
using	std::endl;

typedef	struct	s_data
{
	int			data;
	void	(*show_data)(struct s_data *);
	void	(*add)(struct s_data *, int);
}				t_data;



void	show_data(t_data *THIS)
{
	cout<<"data : "<<THIS->data<<endl;
}

void	add(t_data *THIS, int num)
{
	THIS->data += num;
}



int main(void)
{
	t_data	obj1 = {15, show_data, add};
	t_data	obj2 = {7, show_data, add};

	obj1.add(&obj1, 17);
	obj2.add(&obj2, 9);
	obj1.show_data(&obj1);
	obj2.show_data(&obj2);

}