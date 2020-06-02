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

int		partition(int *arr, int left, int right)
{
	int	pivot;
	int	low;
	int	high;
	
	pivot = arr[left];
	low = left + 1;
	high = right;
	while (low <= high)
	{
		// increase low until a value greater than pivot is found
		while (low <= high && arr[low] <= pivot)
			low++;
		// decrease high until a value less than the pivot is found	
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



// 406page. sorting
int		main(void)
{
	int arr[] = {3, 3, 3};

	show_arr(arr, sizeof(arr) / sizeof(int));
	quick_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
	show_arr(arr, sizeof(arr) / sizeof(int));
} 
