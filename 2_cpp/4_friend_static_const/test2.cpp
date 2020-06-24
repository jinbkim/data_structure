#include <iostream>
#include <cstring>

using	std::cout;
using	std::endl;

class   temporary
{
    int num;

public:
    temporary(int n)
        : num(n)
    {
        cout<<"create obj : "<<num<<endl;
    }

    ~temporary()
    {
        cout<<"destory obj : "<<num<<endl;
    }

    void    show()
    {
        cout<<"num : "<<num<<endl;
    }
};


int		main(void)
{
    temporary(100);
    cout<<"----- after make -----"<<endl;
    temporary(200).show();
    cout<<"----- after make -----"<<endl;

    temporary ref = temporary(300);
    cout<<"----- after make -----"<<endl;

}