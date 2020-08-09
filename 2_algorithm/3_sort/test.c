#include <stdio.h>

int		get_bits(int x, int bit, int size)
{
	printf("x : %d, bit : %d, x>>bit : %d, size : %d, ~(~0 << size) : %d, ", x, bit, x >> bit, size, (~(~0 << size)));
	return ((x >> bit) & ~(~0 << size)); 
}

int	main(void)
{
	int	i;

	i = 11;
	while (--i >= 0)
		printf("result :%d\n", get_bits(593, i, 1));
}