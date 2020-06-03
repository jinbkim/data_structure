#include <stdio.h>
#include <stdlib.h>

void	arr_swap(int *a, int *b)
{
	int	temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
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
	int	example[] = {left, (left + right) / 2, right};
	
	if (arr[1] < arr[0])
		ft_swap(&example[1], &example[0]);
	if (arr[2] < arr[1])
		ft_swap(&example[2], &example[1]);
	if (arr[1] < arr[0])
		ft_swap(&example[1], &example[0]);
	return (example[1]);
}

int		partition(int *arr, int left, int right)
{
	int pivot_idx;
	int	pivot;
	int low;
	int high;

	pivot_idx = median_pivot(arr, left, right);  // store median index
	pivot = arr[pivot_idx];
	low = left + 1;
	high = right;
	ft_swap(&arr[pivot_idx], &arr[left]);  // move pivot to left
	
	while (low <= high)
	{
		// keeping low <= high, increase low 
		// until we find low value bigger than pivot
		while (low <= right && arr[low] <= pivot)
			low++;
		// keeping pivot < high, decrease high
		// until we find high value smaller than pivot
		while (left < high && pivot <= arr[high])
			high--;
		if (low <= high)  // change location if not crossed
			ft_swap(&arr[low], &arr[high]);	
	}
	ft_swap(&arr[left], &arr[high]);
	return (high);
}

void	quick_sort(int *arr, int left, int right)
{
	int pivot;

	if (left <= right)
	{
		// pivot is already in the right place
		// devide by pivot and sort
		pivot = partition(arr, left, right);
		quick_sort(arr, left, pivot - 1);
		quick_sort(arr, pivot + 1, right);
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



// 411page. sorting
int		main(void)
{
	int arr[] = {3, 2, 4, 1};

	show_arr(arr, sizeof(arr) / sizeof(int));
	quick_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
	show_arr(arr, sizeof(arr) / sizeof(int));
} 
