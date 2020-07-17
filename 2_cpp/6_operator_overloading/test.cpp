#include <iostream>

using	std::cout;
using	std::cin;
using	std::endl;

class	class_a
{
	int	a;

public:
	class_a (int a) : a(a) {}

	void	show()
	{
		cout<<"a : "<<a<<endl;
	}
};

class	class_b
{
	class_a	*aa;
	int		bb;

public:
	class_b (int bb = 0) : bb(bb)
	{

	}
};


int		main(void)
{


}