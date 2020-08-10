#include <stdio.h>
#include <stdlib.h>

void	show_arr(int *arr, int size)
{
	int i ;
	
	i = -1;
	while(++i < size)
		printf("%d ", arr[i]);
	printf("\n");
}

void	merge_sort(int *arr, int n)
{
	int	bucket[n + 1];
	int	left;
	int	right;
	int	size;
	int	i;
	int	j;
	int	k;

	size = 1;
	while (size < n)
	{
		left = -2 * size;
		right = left + size;
		while (right + size <= n)
		{
			left = right + size;
			right = left + size;
			i = left - 1;
			j = right - 1;
			k = left - 1;
			while (++k < n)
			{
				if (arr[i + 1] <= arr[j + 1])
				{
					if (i + 1 < right)
						bucket[k] = arr[++i];
					else
						bucket[k] = arr[++j];
				}
				else
				{
					if ((j + 1 < right + size) && (j + 1 < n))
						bucket[k] = arr[++j];
					else
						bucket[k] = arr[++i];
				}
			}
		}
		i = -1;
		while (++i < n)
			arr[i] = bucket[i];
		size *= 2;
	}
}



int		main(void)
{
	int arr[8] = {6, 2, 4, 7, 1, 5, 3};

	show_arr(arr, sizeof(arr) / sizeof(int) - 1);
	merge_sort(arr, sizeof(arr) / sizeof(int) - 1);
	show_arr(arr, sizeof(arr) / sizeof(int) - 1);
} 