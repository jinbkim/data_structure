#include <stdio.h>
#include <stdlib.h>

void	arr_swap(int *a, int *b)
{
	int	temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	merge(int *arr, int left, int mid, int right)
{
	int		*merge_arr;
	int		left_idx;
	int		right_idx;
	int		idx;
	
	left_idx = left;
	right_idx = mid + 1;
	idx = left;
	merge_arr = (int *)malloc(sizeof(int) * (right + 1));  // the index of the array approaches until right + 1.
	
	// sort by priority
	while (left_idx <= mid && right_idx <= right)
	{
		if (arr[left_idx] <= arr[right_idx])
			merge_arr[idx++] = arr[left_idx++];
		else
			merge_arr[idx++] = arr[right_idx++];
	}	
	if (mid < left_idx)
		while(right_idx <= right)
			merge_arr[idx++] = arr[right_idx++];
	else
		while(left_idx <= mid)
			merge_arr[idx++] = arr[left_idx++];

	// move back to the original array
	idx = left - 1;
	while (++idx <= right)
		arr[idx] = merge_arr[idx];
	free(merge_arr);
}

void	merge_sort(int *arr, int left, int right)
{
	int	mid;
	
	if (left < right)
	{
		mid = (left + right) / 2;
		
		// divide into two and sort each
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		merge(arr, left, mid, right);  // Merge sorted two arrays
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



// 393page. sorting
int		main(void)
{
	int arr[] = {3, 2, 4, 1};

	show_arr(arr, sizeof(arr) / sizeof(int));
	merge_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
	show_arr(arr, sizeof(arr) / sizeof(int));
} 
