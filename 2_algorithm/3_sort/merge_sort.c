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

void	merge(int *arr, int left, int mid, int right)
{
	int	*merge_arr;
	int	left_i;
	int	right_i;
	int	i;

	left_i = left;
	right_i = mid + 1;
	i = left - 1;
	merge_arr = (int *)malloc(sizeof(int) * (right + 1));

	while (left_i <= mid && right_i <= right)
	{
		if (arr[left_i] <= arr[right_i])
			merge_arr[++i] = arr[left_i++];
		else
			merge_arr[++i] = arr[right_i++];
	}

	if (mid < left_i)
		while (right_i <= right)
			merge_arr[++i] = arr[right_i++];
	else
		while (left_i <= mid)
			merge_arr[++i] = arr[left_i++];

	i = left - 1;
	while (++i <= right)
		arr[i] = merge_arr[i];

	free(merge_arr);
}

void	merge_sort(int *arr, int left, int right)
{
	int	mid;

	if (left < right)
	{
		mid = (left + right) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

int		main(void)
{
	int arr[] = {6, 3, 1, 7, 4, 2, 5};

	show_arr(arr, sizeof(arr) / sizeof(int));
	merge_sort(arr, 0, sizeof(arr) / sizeof(int) - 1);
	show_arr(arr, sizeof(arr) / sizeof(int));
}
