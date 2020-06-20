#include <iostream>

using std::cout;
using std::endl;



namespace AAA
{
	namespace BBB
	{
		namespace CCC
		{
			int num1;
			int num2;
		}
	}
}



int		main(void)
{
	namespace 	ABC = AAA::BBB::CCC;
	
	ABC::num1 = 20;
	ABC::num2 = 30;
	
	cout<<ABC::num1<<endl;
	cout<<ABC::num2<<endl;
}
