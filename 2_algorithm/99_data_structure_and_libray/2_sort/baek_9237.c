#include <stdio.h>
#include <stdlib.h>

#define	HEAP_SIZE	100001

typedef	struct	s_info
{
	char		name[11];
	int			korean;
	int			english;
	int			math;
}				t_info;

typedef	int	heap_data;

typedef	int		(*priority_comp_func)(heap_data, heap_data);  // function pointer

typedef	struct	s_p_queue
{
	int					data_num;  // number of data
	heap_data			heap_arr[HEAP_SIZE];	
	priority_comp_func	f;
}				t_p_queue;



int			comp_func(heap_data a, heap_data b)
{
	return (b - a);
}

void		p_queue_init(t_p_queue *pq, priority_comp_func f)
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

void	heap_sort(int *tree, int size, priority_comp_func f)
{
	t_p_queue	pq;
	int			i;
	
	p_queue_init(&pq, f);
	i = -1;
	while (++i < size)
		enter_p_queue(&pq, tree[i]);
	i = -1;
	while(++i < size)
		tree[i] = delete_p_queue(&pq);
}	



int			tree_planting(int size)
{
	int	tree[size];
	int	max;
	int i;
	
	i = -1;
	while (++i < size)
		scanf("%d", &tree[i]);
	
	heap_sort(tree, size, comp_func);
	
	max = tree[0] + 2;
	i = 0;
	while (++i < size)
		if (max < tree[i] + i + 2)
			max = tree[i] + i + 2;

	return (max);
} 



int			main(void)
{
	int		size;

	scanf("%d", &size);
	getchar();
	
	printf("%d\n", tree_planting(size));
}
