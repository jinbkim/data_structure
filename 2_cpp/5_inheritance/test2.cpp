#include <iostream>
#include <cstring>

using	std::cout;
using	std::endl;

class	s_class
{
	int			num1;
	mutable int	num2;

public:
	s_class(int n1, int n2)
		: num1(n1), num2(n2) {}

	void	show()
	{
		cout<<"<"<<num1<<", "<<num2<<">"<<endl;
	}

	void	num1_to_num2() const
	{
		num2 = num1;
	}
};



int		main(void)
{
	s_class	sc(1, 2);

	sc.show();
	sc.num1_to_num2();
	sc.show();
}