#include <stdio.h>
#include <stdlib.h>

#define BUCKET_LEN	10

typedef	int	queue_data;

typedef struct	s_node
{
	queue_data		data;
	struct s_node	*next;
}					t_node;

typedef	struct	s_queue
{
	t_node		*front;
	t_node		*rear;
}				t_queue;



void	show_arr(int *arr, int size)
{
	int i ;
	
	i = -1;
	while(++i < size)
		printf("%d ", arr[i]);
	printf("\n");
}

void	queue_init(t_queue *q)
{
	q->front = NULL;
}

void	enqueue(t_queue *q, queue_data d)
{
	t_node	*node;
	
	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;
	node->next = NULL;
	
	if (q->front)
		q->rear->next = node;
	else
		q->front = node;
	q->rear = node;
}

int			queue_is_empty(t_queue *q)
{
	if (q->front)
		return (0);
	return (1);
}

queue_data	dequeue(t_queue *q)
{
	t_node		*del_n;
	queue_data	del_d;
	
	del_n = q->front;
	del_d = q->front->data;
	
	q->front = q->front->next;
	free(del_n);
	return (del_d);
}

void	radix_sort(int *arr, int size, int len)
{
	t_queue	bucket[BUCKET_LEN];
	int		radix;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < BUCKET_LEN)
		queue_init(&bucket[i]);
	
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < size)
		{
			radix = arr[j];
			k = -1;
			while (++k < i)
				radix /= 10;
			radix = radix % 10;
			enqueue(&bucket[radix], arr[j]);
		}
		j = -1;
		k = -1;
		while (++j < BUCKET_LEN)
			while (!queue_is_empty(&bucket[j]))
				arr[++k] = dequeue(&bucket[j]);
	}
}

int		main(void)
{
	int	arr[] = {13, 212, 14, 7141, 10987, 6, 15};

	show_arr(arr, sizeof(arr) / sizeof(int));
	radix_sort(arr, sizeof(arr) / sizeof(int), 5);
	show_arr(arr, sizeof(arr) / sizeof(int));
}