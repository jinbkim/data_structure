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



int		comp_func(pq_data a, pq_data b)
{
	return (b - a);
}

void	p_queue_init(t_p_queue *pq, priority_comp f)
{
	pq->data_num = 0;
	pq->f = f;
}

void	enter_p_queue(t_p_queue *pq, pq_data data)
{
	int	idx;
	
	// number of nodes stored in priority queue matches index of last node
	idx = ++(pq->data_num);
	
	// find index location
	while (idx != 1)
	{
		// break when priority of data is lower then parent node
		if (pq->f(data, pq->pq_arr[idx / 2]) <= 0)
			break ;
		else
		{
			pq->pq_arr[idx] = pq->pq_arr[idx / 2];
			idx /= 2;
		}
	}
	
	pq->pq_arr[idx] = data;
}

int		p_queue_is_empty(t_p_queue *pq)
{
	if (pq->data_num)
		return (0);
	return (1);
}

int			get_high_priority_child_idx(t_p_queue *pq, int idx)
{
	if (pq->data_num < idx * 2)  // if child node is not exist
		return (0);
	else if (pq->data_num == idx * 2)  // if left child node is last node
		return (idx * 2);
	else
	{
		// if left child node has a higher priority than right child node,
		if (pq->f(pq->pq_arr[idx * 2], pq->pq_arr[idx * 2 + 1]) > 0)
			return (idx * 2);
		else
			return (idx * 2 + 1);
	}
}

pq_data	delete_p_queue(t_p_queue *pq)
{
	pq_data	remem_data;
	pq_data	last_elem;
	int			parent_i;
	int			child_i;
	
	remem_data = pq->pq_arr[1]; // remember data to be deleted
	last_elem = pq->pq_arr[(pq->data_num)--];
	
	// starting root node, find place of last element by comparing priortiy
	parent_i = 1;
	while ((child_i = get_high_priority_child_idx(pq, parent_i)))
	{
		// break when priority of last element is higher then child node
		if (pq->f(last_elem, pq->pq_arr[child_i]) >= 0)  // if you find good location
			break ;
		pq->pq_arr[parent_i] = pq->pq_arr[child_i];
		parent_i = child_i;
	}
	
	pq->pq_arr[parent_i] = last_elem;
	return (remem_data);
}



void	heap_sort(int *arr, int size, priority_comp f)
{
	t_p_queue	pq;
	int			i;
	
	p_queue_init(&pq, f);  // priority queue reset

	i = -1;
	while (++i < size)
		enter_p_queue(&pq, arr[i]);

	i = -1;
	while(++i < size)
		arr[i] = delete_p_queue(&pq);
}

void	show_arr(int *arr, int size)
{
	int i ;
	
	i = -1;
	while(++i < size)
		printf("%d ", arr[i]);
	printf("\n");
}



// 386page. sorting
int		main(void)
{
	int arr[] = {3, 2, 4, 1};

	show_arr(arr, sizeof(arr) / sizeof(int));
	heap_sort(arr, sizeof(arr) / sizeof(int), comp_func);
	show_arr(arr, sizeof(arr) / sizeof(int));
} 
