#include <stdio.h>

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
	return ((x >> bit) & ~(~0 << size)); 
}

void	ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	radix_sort(int *arr, int n, int bit)
{
	int i;
	int	j;
	int ret;

	if (n > 1 && bit >= 0)
	{
		i = 0;
		j = n - 1;
		while (1)
		{
			while (!(ret = get_bits(arr[i], bit, 1)) && i < j)
				i++;
			while ((ret = get_bits(arr[j], bit, 1)) && i < j)
				j--;
			if (j <= i)
				break ;
			ft_swap(&arr[i], &arr[j]);
		}
		if (!get_bits(arr[n-1], bit, 1))
			j++;
		radix_sort(arr, j, bit - 1);
		radix_sort(arr + j, n - j, bit - 1);
	}
}



int		main(void)
{
	int	arr[] = {593, 9, 611, 86, 900, 55, 77, 302};

	show_arr(arr, sizeof(arr) / sizeof(int));
	radix_sort(arr, sizeof(arr) / sizeof(int), 16);
	show_arr(arr, sizeof(arr) / sizeof(int));
}