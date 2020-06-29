#include <iostream>

using	std::cout;
using	std::endl;
class	point
{
	int	x;
	int	y;

public:
	point(int x = 0, int y = 0) : x(x), y(y) {}

	void	show() const
	{
		cout<<"<"<<x<<", "<<y<<">"<<endl;
	}
	point	operator*(int times)
	{
		point	p(x * times, y * times);
		return (p);
	}
	friend point operator*(int times, point p);
};

point operator*(int times, point p)
{
	return (p * times);
}



int main(void)
{
	point	p1(1, 2);
	point	p2;

	p2 = 3 * p1;
	p2.show();

	p2 = 2 * p1 * 3;
	p2.show();
}