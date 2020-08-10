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
	int	bucket[n];
	int	first;
	int	second;
	int	size;
	int	i;
	int	j;
	int	k;

	size = 1;
	while (size < n)
	{
		first = -2 * size;
		second = first + size;
		while (second + size * 2 < n)
		{
			first = second + size;
			second = first + size;
			i = first;
			j = second;
			k = first;
			printf("size : %d, first : %d, second : %d, i : %d, j : %d, k : %d\n", size, first, second, i, j, k);
			while (i < first + size || (j < second + size && j < n))
			{
				printf("k : %d\n", k);
				if (arr[i] <= arr[j])
				{
					if (i < first + size)
						bucket[k++] = arr[i++];
					else
						bucket[k++] = arr[j++];
				}
				else
				{
					if ((j < second + size) && j < n)
						bucket[k++] = arr[j++];
					else
						bucket[k++] = arr[i++];
				}
			}
		}
		show_arr(bucket, 7);
		i = -1;
		while (++i < n)
			arr[i] = bucket[i];
		size *= 2;
	}
}


int		main(void)
{
	int arr[] = {6, 3, 1, 7, 4, 2, 5};

	show_arr(arr, sizeof(arr) / sizeof(int));
	merge_sort(arr, sizeof(arr) / sizeof(int));
	show_arr(arr, sizeof(arr) / sizeof(int));
} 