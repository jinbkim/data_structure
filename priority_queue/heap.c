#include <stdio.h>

#define	HEAP_SIZE	100

typedef	int		priority;
typedef	char	heap_data;

typedef struct	s_heap_element
{
	priority	p;  // small value is high priority.
	heap_data	data;
}				t_heap_element;

typedef	struct		s_heap
{
	int				data_num;  // number of data
	t_heap_element	heap_arr[HEAP_SIZE];
}					t_heap;



void		heap_init(t_heap *heap)
{
	heap->data_num = 0;
}

void		heap_insert(t_heap *heap, heap_data data, priority p)
{
	t_heap_element	h_elem;
	int				idx;
	
	h_elem.p = p;
	h_elem.data = data;
	idx = ++(heap->data_num);
	
	// find index location
	while (idx != 1)
	{
		if (p < heap->heap_arr[idx / 2].p)  // compare priority of parent node
		{
			heap->heap_arr[idx] = heap->heap_arr[idx / 2];  // change location
			idx /= 2;
		}
		else
			break ;
	}
	heap->heap_arr[idx] = h_elem;
}

int			get_high_priority_child_idx(t_heap *heap, int idx)
{
	if (idx * 2 > heap->data_num)  // if child node is not exist
		return (0);
	else if (idx * 2 == heap->data_num)  // if lef child node is last node
		return (idx * 2);
	else
	{
		// if left child node has a higher priority than right child node,
		if (heap->heap_arr[idx * 2].p < heap->heap_arr[idx * 2 + 1].p)
			return (idx * 2);
		else
			return (idx * 2 + 1);
	}
}

heap_data	heap_delete(t_heap *heap)
{
	heap_data		remem_data;
	t_heap_element	last_elem;
	int				parent_i;
	int				child_i;
	
	remem_data = heap->heap_arr[1].data;  // remember data to be deleted
	last_elem = heap->heap_arr[(heap->data_num)--];
	parent_i = 1;
	
	// store index to child_i (high priority child node)
	// compare priority of the last data from the root node to ~
	while ((child_i = get_high_priority_child_idx(heap, parent_i)))
	{
		if (last_elem.p <= heap->heap_arr[child_i].p)  // if you find good location
			break ;
		heap->heap_arr[parent_i] = heap->heap_arr[child_i];
		parent_i = child_i;
	}
	
	heap->heap_arr[parent_i] = last_elem;
	return (remem_data);
}

int			heap_is_empty(t_heap *heap)
{
	if (heap->data_num)
		return (0);
	return (1);
}



int			main(void)
{
	t_heap	heap;
	
	heap_init(&heap);  // heap reset
	
	heap_insert(&heap, 'A', 1);  // insert data to heap
	heap_insert(&heap, 'B', 2);
	heap_insert(&heap, 'C', 3);
	
	printf("%c \n", heap_delete(&heap));  // delete the data with the highest priority
	
	heap_insert(&heap, 'A', 1);
	heap_insert(&heap, 'B', 2);
	heap_insert(&heap, 'C', 3);
	
	printf("%c \n", heap_delete(&heap));
	
	while (!heap_is_empty(&heap))  // repeat until the heap is empty
		printf("%c \n", heap_delete(&heap));
}
