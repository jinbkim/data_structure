#include <stdio.h>

#define	HEAP_SIZE	100000

typedef	int	heap_data;
typedef	int	(*priority_comp)(heap_data, heap_data);  // function pointer

typedef	struct		s_heap
{
	int				data_num;  // number of data
	heap_data		heap_arr[HEAP_SIZE];	
	priority_comp	f;
}					t_heap;

typedef	t_heap	t_p_queue;



void		p_queue_init(t_p_queue *pq, priority_comp f)
{
	pq->data_num = 0;
	pq->f = f;
}

void		enter_p_queue(t_p_queue *pq, heap_data data)
{
	int	idx;
	
	// number of nodes stored in heap matches index of last node
	idx = ++(pq->data_num);
	
	// find index location
	while (idx != 1)
	{
		if (pq->f(data, pq->heap_arr[idx / 2]) > 0)  // compare priority of parent node
			break ;
		else
		{
			pq->heap_arr[idx] = pq->heap_arr[idx / 2];
			idx /= 2;
		}
	}
	pq->heap_arr[idx] = data;
}

int			get_high_priority_child_idx(t_p_queue *pq, int idx)
{
	if (idx * 2 > pq->data_num)  // if child node is not exist
		return (0);
	else if (idx * 2 == pq->data_num)  // if lef child node is last node
		return (idx * 2);
	else
	{
		// if left child node has a higher priority than right child node,
		if (pq->f(pq->heap_arr[idx * 2], pq->heap_arr[idx * 2 + 1]) > 0)
			return (idx * 2 + 1);
		else
			return (idx * 2);
	}
}

heap_data	delete_p_queue(t_p_queue *pq)
{
	heap_data	remem_data;
	heap_data	last_elem;
	int			parent_i;
	int			child_i;
	
	remem_data = pq->heap_arr[1]; // remember data to be deleted
	last_elem = pq->heap_arr[(pq->data_num)--];
	parent_i = 1;
	
	// store index to child_i (high priority child node)
	// compare priority of the last data from the root node to ~
	while ((child_i = get_high_priority_child_idx(pq, parent_i)))
	{
		if (pq->f(last_elem, pq->heap_arr[child_i]) <= 0)  // if you find good location
			break ;
		pq->heap_arr[parent_i] = pq->heap_arr[child_i];
		parent_i = child_i;
	}
	
	pq->heap_arr[parent_i] = last_elem;
	return (remem_data);
}



int			comp_func(heap_data a, heap_data b)
{
	return (a - b);
}

void		heap_input(int size)
{
	t_p_queue	pq;
	int			data;
	int			i;
	
	p_queue_init(&pq, comp_func);  // priority queue reset
	
	i = -1;
	while (++i < size)
	{
		scanf ("%d", &data);
		getchar();

		if (data)
			enter_p_queue(&pq, data);
		else
		{
			if (!pq.data_num)
				printf("0\n");
			else
				printf("%d\n", delete_p_queue(&pq));
		}
	}
}



int			main(void)
{
	int size;
	
	scanf("%d", &size);
	getchar();
	
	heap_input(size);
}
