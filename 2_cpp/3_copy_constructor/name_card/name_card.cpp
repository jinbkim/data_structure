#include "name_card.h"

name_card::name_card(const char *my_name, const char *my_company, const char *my_phone, int my_pos)
{
    const char  *str[] = {"iron", "bronze", "silver", "gold"};

    name = new char[strlen(my_name) + 1];
    company = new char[strlen(my_company) + 1];
    phone = new char[strlen(my_phone) + 1];
    pos = new char[strlen(str[my_pos]) + 1];

    strcpy(name, my_name);
    strcpy(company, my_company);
    strcpy(phone, my_phone);
    strcpy(pos, str[my_pos]);
}

name_card::name_card(name_card &copy)
{
    name = new char[strlen(copy.name) + 1];
    company = new char[strlen(copy.company) + 1];
    phone = new char[strlen(copy.phone) + 1];
    pos = new char[strlen(copy.pos) + 1];

    strcpy(name, copy.name);
    strcpy(company, copy.company);
    strcpy(phone, copy.phone);
    strcpy(pos, copy.pos);
}



void    name_card::show_info(void)
{
    cout<<"name : "<<name<<endl;
    cout<<"company : "<<company<<endl;
    cout<<"phone number : "<<phone<<endl;
    cout<<"position : "<<pos<<endl<<endl;
}

name_card::~name_card()
{
    delete []name;
    delete []company;
    delete []phone;
    delete []pos;
}