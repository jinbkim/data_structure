#include <stdio.h>
#include <limits.h>

typedef	int	(*priority_comp)(int, int);



void	show_arr(int *arr, int size)
{
	int i ;
	
	i = 0;
	while(++i < size)
		printf("%d ", arr[i]);
	printf("\n");
}

int		comp_func(int a, int b)
{
	return (a - b);
}

void	heap_put(int *arr, int idx, priority_comp f)
{
	int	input;

	input = arr[idx];
	while (f(arr[idx / 2], input) < 0)
	{
		arr[idx] = arr[idx / 2];
		idx /= 2;
	}
	arr[idx] = input;
}

int		heap_get(int *arr, int i, priority_comp f)
{
	int last_data;
	int	output;
	int	parent_i;
	int	child_i;

	output = arr[1];
	arr[1] = arr[(i)];
	last_data = arr[(i)];
	parent_i = 1;
	while (parent_i <= i / 2)
	{
		child_i = parent_i * 2;
		if (child_i < i && (f(arr[child_i], arr[child_i + 1]) < 0))
			child_i++;
		if (f(arr[child_i], last_data) < 0)
			break ;
		arr[parent_i] = arr[child_i];
		parent_i = child_i;
	}
	arr[parent_i] = last_data;
	return (output);
}

void	heap_sort(int *arr, int n, priority_comp f)
{
	int	i;

	i = 0;
	while (++i <= n)
		heap_put(arr, i, f);

	while (0 < --i)
		arr[i] = heap_get(arr, i, f);
}



int		main(void)
{
	int arr[] = {INT_MAX, 3, 2, 1, 99, 88, 77};

	show_arr(arr, sizeof(arr) / sizeof(int));
	heap_sort(arr, sizeof(arr) / sizeof(int) - 1, comp_func);
	show_arr(arr, sizeof(arr) / sizeof(int));
}