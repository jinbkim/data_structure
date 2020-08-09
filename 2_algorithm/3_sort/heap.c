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

// void	comp_get(int *arr, int i, priority_comp f)
// {
// 	int v;
// 	int	ii;
// 	int	j;

// 	v = arr[1];
// 	ii = 1;
// 	while (ii <= i / 2)
// 	{
// 		j = ii * 2;
// 		if (j < i && arr[j] < arr[j + 1])
// 			j++;
// 		if (f(arr[j], v) < 0)
// 			break ;
// 		arr[ii] = arr[j];
// 		ii = j; 
// 	}
// 	arr[ii] = v;
// }

int		heap_get(int *arr, int i, priority_comp f)
{
	int last_data;
	int	output;
	int	parent_i;
	int	child_i;

	printf("----- show0 -----\n");
	show_arr(arr, 8);
	output = arr[1];
	// printf("--------------------\n");
	// printf("arr[1] : %d, i : %d\n", arr[1], i);
	arr[1] = arr[(i)];
	// printf("arr[1] : %d, i : %d\n", arr[1], i);
	// comp_get(arr, i, f);
	last_data = arr[1];
	// printf("last_data : %d\n", last_data);
	parent_i = 1;
	// printf("i : %d\n", i);
	printf("----- show1 -----\n");
	show_arr(arr, 8);
	while (parent_i <= i / 2)
	{
		child_i = parent_i * 2;
		printf("i : %d, child_i : %d, arr[child_i] : %d, arr[child_i + 1] : %d\n", i, child_i, arr[child_i], arr[child_i + 1]);
		if (child_i < i && (f(arr[child_i], arr[child_i + 1]) < 0))
			child_i++;\
		if (f(arr[child_i], last_data) < 0)
			break ;
		arr[parent_i] = arr[child_i];
		parent_i = child_i;
		printf("----- show2 -----\n");
		show_arr(arr, 8);
	}

	arr[parent_i] = last_data;
	printf("----- show3 -----\n");
	show_arr(arr, 8);
	printf("i : %d, child_i : %d, arr[child_i] : %d, arr[child_i + 1] : %d\n", i, child_i, arr[child_i], arr[child_i + 1]);
	return (output);
}

void	heap_sort(int *arr, int n, priority_comp f)
{
	int	i;
	// int	i;

	i = 0;
	// i = 0;
	while (++i <= n)
	{
		heap_put(arr, i, f);

		// heap_put(arr, ++i, f);
		// printf("i : %d, i : %d\n", i , i);
	}
	// i = i + 1;
	// i = (--i) + 1;
	// i++;
	// printf("i : %d, i: %d\n", i , i);
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