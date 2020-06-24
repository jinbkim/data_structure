#include <iostream>
#include <cstring>

using	std::cout;
using	std::endl;

class	s_class
{
	int	num;

public:
	s_class(int n)
		: num(n)
	{
		cout<<"new obj : "<<this<<endl;
	}
	s_class (const s_class &copy)
		: num(copy.num)
	{
		cout<<"new copy obj : "<<this<<endl;
	}

	~s_class()
	{
		cout<<"destroy obj : "<<this<<endl;
	}
};

s_class	return_address(s_class obj)
{
	cout<<"obj address: "<<&obj<<endl;
	return (obj);
}



int		main(void)
{
	s_class	obj1(7);
	cout<<"----------1"<<endl;
	return_address(obj1);
	cout<<"----------2"<<endl;
	s_class	obj2 = return_address(obj1);
	cout<<"----------3"<<endl;
	cout<<"obj2 address : "<<&obj2<<endl;
	cout<<"----------4"<<endl;

}