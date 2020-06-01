#include <stdio.h>

void	arr_swap(int *a, int *b)
{
	int	temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	select_sort(int *arr, int size)
{
	int i;
	int j;
	int	max_idx;
	
	i = -1;
	while (++i < size)
	{
		max_idx = i;
		j = i;
		while (++j < size)
			if (arr[j] < arr[max_idx])  // higher value is lower priority.
				max_idx = j;
		arr_swap(&arr[i], &arr[max_idx]);
	}
}

void	show_arr(int *arr, int size)
{
	int i ;
	
	i = -1;
	while(++i < size)
		printf("%d ", arr[i]);
	printf("\n");
}



int		main(void)
{
	int arr[] = {3, 2, 4, 1};

	show_arr(arr, sizeof(arr) / sizeof(int));
	select_sort(arr, sizeof(arr) / sizeof(int));
	show_arr(arr, sizeof(arr) / sizeof(int));
}
