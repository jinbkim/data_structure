#include "person.h"

person::person(const char *name, int age)
{
	strcpy(this->name, name);
	this->age = age;
}

void	person::show_name(void) const
{
	cout<<"name : "<<name<<endl;
}

void	person::show_age(void) const
{
	cout<<"age : "<<age<<endl;
}



university::university(const char *name, int age, const char *major)
	: person(name, age)
{
	strcpy(this->major, major);
}

void	university::show_all(void) const
{
	show_name();
	show_age();
	cout<<"major : "<<major<<endl;
}
