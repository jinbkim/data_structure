#include <iostream>
#include <cstring>

using	std::cout;
using	std::endl;

class	book
{
	char	*title;
	char	*num;
	int		price;

public:
	book()
	{
		title = NULL;
		num = NULL;
	}
	book(const char *title, const char *num, int price)
	{
		this->title = new char[strlen(title) + 1];
		strcpy(this->title, title);
		this->num = new char[strlen(num) + 1];
		strcpy(this->num, num);
		this->price = price;
	}

	void	show_book()
	{
		cout<<"title : "<<title<<endl;
		cout<<"book number : "<<num<<endl;
		cout<<"price : "<<price<<endl;
	}

	~book()
	{
		delete []title;
		delete []num;
	}
};

class	ebook : public book
{
	book	b;
	int		key;

public:
	ebook(const char *title, const char *num, int price, int key)
		: b(title, num, price), key(key) {}

	void	show(void)
	{
		b.show_book();
		cout<<"key : "<<key<<endl;
	}
};



int		main(void)
{
	book	b("c book", "b-200", 5000);
	ebook	eb("c++ book", "a-100", 10000, 1);

	b.show_book();
	cout<<endl;
	eb.show();
}