#include <stdio.h>

int		i_search(int *arr, int first, int last, int target)
{
	int mid;
	
	// when target is not included in scope of array
	if (target < arr[first] || arr[last] < target)
		return (-1);

	// approximate the position of mid
	mid = ((double)target - arr[first]) * (last - first) / (arr[last] - arr[first]) + first;

	if (arr[mid] == target)
		return (mid);
	else if (target < arr[mid])
		return (i_search(arr, first, mid - 1, target));
	else
		return (i_search(arr, mid + 1, last, target));
}



int		main(void)
{
	int arr[] = {1, 3, 5, 7, 9};
	int i;

	i = i_search(arr, 0, sizeof(arr) / sizeof(int) - 1, 7);
	if (i == -1)
		printf("search fail\n");
	else
		printf("target index : %d\n", i);
	
	i = i_search(arr, 0, sizeof(arr) / sizeof(int) - 1, 2);
	if (i == -1)
		printf("search fail\n");
	else
		printf("target index : %d\n", i);
}
