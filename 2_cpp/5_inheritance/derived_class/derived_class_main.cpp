#include "derived_class.h"

int		main(void)
{
	cout<<"----- case1 -----"<<endl;
	d_class	dc1;
	dc1.show_derived();

	cout<<"----- case2 -----"<<endl;
	d_class	dc2(12);
	dc2.show_derived();

	cout<<"----- case3 -----"<<endl;
	d_class	dc3(23, 24);
	dc3.show_derived();
}