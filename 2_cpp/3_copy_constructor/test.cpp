#include <iostream>
#include <cstring>

#define	STR_SIZE	100

using	std::cout;
using	std::endl;

class	self_ref
{
	int num;

public:
	self_ref(int n)
	{
		num = n;
		cout<<"make object!"<<endl;
	}
	self_ref&	add(int n)
	{
		num += n;
		return (*this);
	}
	self_ref&	show_num()
	{
		cout<<"num : "<<num<<endl;
		return (*this);
	}
};


int		main(void)
{
	self_ref	obj(3);
	self_ref	&ref=obj.add(2);

	obj.show_num();
	ref.show_num();

	ref.add(1).show_num().add(2).show_num();
}