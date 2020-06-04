#include <stdio.h>

void	arr_swap(int *a, int *b)
{
	int	temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort(int	*arr, int size)
{
	int i;
	int j;
	
	i = -1;
	while (++i < size)
	{
		j = -1;
		while(++j < size - i - 1)
			if (arr[j] > arr[j + 1])  // higher value is lower priority.
				arr_swap(&arr[j], &arr[j + 1]);
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



// 376page. sorting
int		main(void)
{
	int arr[] = {3, 2, 4, 1};

	show_arr(arr, sizeof(arr) / sizeof(int));
	bubble_sort(arr, sizeof(arr) / sizeof(int));
	show_arr(arr, sizeof(arr) / sizeof(int));
} 
