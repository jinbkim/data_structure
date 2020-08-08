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
	return (a - b);
}



void	p_queue_init(t_p_queue *pq, priority_comp f)
{
	pq->data_num = 0;
	pq->f = f;
}

void	enter_p_queue(t_p_queue *pq, pq_data data)
{

	int	i;
	
	i = ++(pq->data_num);
	while (i != 1)
	{
		if (pq->f(pq->pq_arr[i / 2], data) < 0)
			break ;
		else
		{
			pq->pq_arr[i] = pq->pq_arr[i / 2];
			i /= 2;
		}
	}
	pq->pq_arr[i] = data;
}

int		get_high_priority_child_i(t_p_queue *pq, int i)
{
		if (pq->data_num < i * 2)
			return (0);
		else if (pq->data_num == i * 2)
			return (i * 2);
		else
		{
			if (pq->f(pq->pq_arr[i * 2], pq->pq_arr[i * 2 + 1]) < 0)
				return (i * 2);
			else
				return (i * 2 + 1);
		}
}

pq_data	delete_p_queue(t_p_queue *pq)
{
	pq_data		remem_data;
	pq_data		last_data;
	int			parent_i;
	int			child_i;

	remem_data = pq->pq_arr[1];
	last_data = pq->pq_arr[(pq->data_num)--];
	parent_i = 1;
	while ((child_i = get_high_priority_child_i(pq, parent_i)))
	{
		if (pq->f(last_data, pq->pq_arr[child_i]) < 0)
			break ;
		pq->pq_arr[parent_i] = pq->pq_arr[child_i];
		parent_i = child_i;
	}
	pq->pq_arr[parent_i] = last_data;
	return (remem_data);
}

void	heap_sort(int *arr, int size, priority_comp f)
{
	t_p_queue	pq;
	int			i;

	p_queue_init(&pq, f);
	
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

int		main(void)
{
	int arr[] = {6, 3, 1, 7, 4, 2, 5};

	show_arr(arr, sizeof(arr) / sizeof(int));
	heap_sort(arr, sizeof(arr) / sizeof(int), comp_func);
	show_arr(arr, sizeof(arr) / sizeof(int));
}