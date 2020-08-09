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

void	ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int		median_pivot(int *arr, int left, int right)
{
	int	ex[] = {left, (left + right) / 2, right};

	if (arr[ex[1]] < arr[ex[0]])
		ft_swap(&ex[0], &ex[1]);
	if (arr[ex[2] < arr[ex[1]]])
		ft_swap(&ex[1], &ex[2]);
	if (arr[ex[1]] < arr[ex[0]])
		ft_swap(&ex[0], &ex[1]);
	return (ex[1]);
}

int		partition(int *arr, int left, int right)
{
	int	pivot;
	int pivot_i;
	int i;
	int j;
	
	pivot_i = median_pivot(arr, left, right);
	pivot = arr[pivot_i];
	i = left;
	j = right - 1;
	ft_swap(&arr[pivot_i], &arr[right]);
	while (i <= j)
	{
		while (i <= j && arr[i] <= pivot)
			i++;
		while (i <= j && pivot <= arr[j])
			j--;
		if (i <= j)
			ft_swap(&arr[i], &arr[j]);
	}
	ft_swap(&arr[right], &arr[i]);
	return (i);
}

void	quick_sort(int *arr, int left, int right)
{
	int pivot;

	if (left <= right)
	{
		pivot = partition(arr, left, right);
		quick_sort(arr, left, pivot - 1);
		quick_sort(arr, pivot + 1, right);
	}
}



int		main(void)
{
	int arr[] = {6, 3, 1, 7, 4, 2, 5};

	show_arr(arr, sizeof(arr) / sizeof(int));
	quick_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
	show_arr(arr, sizeof(arr) / sizeof(int));
}