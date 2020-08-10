#include <stdio.h>

#define	BIT_SIZE	2
#define	BB_SIZE		(1 << BIT_SIZE)

void	show_arr(int *arr, int size)
{
	int i ;
	
	i = -1;
	while(++i < size)
		printf("%d ", arr[i]);
	printf("\n");
}

int		get_bits(int x, int bit, int size)
{
	return ((x >> bit) & (~(~0 << size))); 
}

void	radix_sort(int *arr, int n, int bit)
{
	int	data_bucket[n];
	int	bit_bucket[BB_SIZE];
	int	i;
	int	j;

	i = -1;
	while (++i < bit / BIT_SIZE)
	{
		j = -1;
		while (++j < BB_SIZE)
			bit_bucket[j] = 0;

		j = -1;
		while (++j < n)
			bit_bucket[get_bits(arr[j], i * BIT_SIZE, BIT_SIZE)]++;

		j = 0;
		while (++j < BB_SIZE)
			bit_bucket[j] = bit_bucket[j] + bit_bucket[j - 1];

		j = n;
		while (--j >= 0)
			data_bucket[--(bit_bucket[get_bits(arr[j], i * BIT_SIZE, BIT_SIZE)])] = arr[j];
		
		j = -1;
		while (++j < n)
			arr[j] = data_bucket[j];
	}
}



int		main(void)
{
	int	arr[] = {593, 9, 611, 86, 900, 55, 77, 302};
	show_arr(arr, sizeof(arr) / sizeof(int));
	radix_sort(arr, sizeof(arr) / sizeof(int), 16);
	show_arr(arr, sizeof(arr) / sizeof(int));
}