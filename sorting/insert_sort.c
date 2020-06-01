#include <stdio.h>

void	arr_swap(int *a, int *b)
{
	int	temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	insert_sort(int *arr, int size)
{
	int i;
	int j;
	
	i = 0;
	while(++i < size)
	{
		j = i;
		while(--j >= 0)
		{
			if (arr[j + 1] < arr[j])
				arr_swap(&arr[j], &arr[j + 1]);
			else
				break ;
		}
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
	insert_sort(arr, sizeof(arr) / sizeof(int));
	show_arr(arr, sizeof(arr) / sizeof(int));
} 
