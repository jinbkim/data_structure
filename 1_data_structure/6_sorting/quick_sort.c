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
		ft_swap(&ex[1], &ex[0]);
	if (arr[ex[2]] < arr[ex[1]])
		ft_swap(&ex[2], &ex[1]);
	if (arr[ex[1]] < arr[ex[0]])
		ft_swap(&ex[1], &ex[0]);
	return (ex[1]);
}

int		partition(int *arr, int left, int right)
{
	int pivot_idx;
	int	pivot;
	int low;
	int high;
	
	// estimate index of element with median
	// that index is pivot index
	pivot_idx = median_pivot(arr, left, right);
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



// 411page. sorting
int		main(void)
{
	int arr[] = {5, 4, 3, 2, 1};
	//int	arr[] = {3, 3, 3};
	
	show_arr(arr, sizeof(arr) / sizeof(int));
	quick_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
	show_arr(arr, sizeof(arr) / sizeof(int));
} 
