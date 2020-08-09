#include <stdio.h>

#define	PQ_SIZE	100

typedef	int	pq_data;
typedef	int	(*priority_comp)(pq_data, pq_data);

typedef	struct		s_p_queue
{
	int				data_num;
	pq_data			pq_arr[PQ_SIZE];	
	priority_comp	f;
}					t_p_queue;



void	show_arr(int *arr, int size)
{
	int i ;
	
	i = 0;
	while(++i < size)
		printf("%d ", arr[i]);
	printf("\n");
}

int		comp_func(pq_data a, pq_data b)
{
	return (a - b);
}


void	comp_put(int *arr, int node_n, priority_comp f)
{
	int	v;

	v = arr[node_n];
	arr[0] = 9999;
	while (f(arr[node_n / 2], v) < 0)
	{
		arr[node_n] = arr[node_n / 2];
		node_n /= 2;
	}
	arr[node_n] = v;
}
void	heap_put(int *arr, int *node_n, int v, priority_comp f)
{
	arr[++(*node_n)] = v;
	comp_put(arr, *node_n, f);
}

void	comp_get(int *arr, int node_n, priority_comp f)
{
	int v;
	int	i;
	int	j;

	v = arr[1];
	i = 1;
	while (i <= node_n / 2)
	{
		j = i * 2;
		if (j < node_n && arr[j] < arr[j + 1])
			j++;
		if (f(arr[j], v) < 0)
			break ;
		arr[i] = arr[j];
		i = j; 
	}
	arr[i] = v;
}

int		heap_get(int *arr, int *node_n, priority_comp f)
{
	int	v;
	
	v = arr[1];
	arr[1] = arr[(*node_n)--];
	comp_get(arr, *node_n, f);
	return (v);
}

void	heap_sort(int *arr, int n, priority_comp f)
{
	int	node_n;
	int	i;

	node_n = 0;
	i = 0;
	while (++i <= n)
		heap_put(arr, &node_n, arr[i], f);
	
	printf("node_n : %d\n", node_n);
	i = node_n + 1;
	while (1 <= --i)
	{
		printf("arr[%d] : %d\n", i, arr[i] = heap_get(arr, &node_n, f));
	}
}





int		main(void)
{
	int arr[8] = {9999, 6, 3, 1, 7, 4, 2, 5};

	show_arr(arr, sizeof(arr) / sizeof(int));
	heap_sort(arr, sizeof(arr) / sizeof(int) - 1, comp_func);
	show_arr(arr, sizeof(arr) / sizeof(int));
}