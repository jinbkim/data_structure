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



void	queue_init(t_queue *q)
{
	q->front = NULL;
}

int			queue_is_empty(t_queue *q)
{
	if (q->front)
		return (0);
	return (1);
}

void	enter_queue(t_queue *q, queue_data data)
{
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	new_node->next = NULL;
	if (q->front)
		q->rear->next = new_node;
	else
		q->front = new_node;
	q->rear = new_node;
}

queue_data	delete_queue(t_queue *q)
{
	t_node		*remem_node;
	queue_data	remem_data;
	
	remem_node = q->front;  // remember node to be deleted
	remem_data = q->front->data;  // remember data to be deleted
	
	q->front = q->front->next;  // front reset

	free(remem_node);
	return (remem_data);
}



void	show_arr(int *arr, int size)
{
	int i ;
	
	i = -1;
	while(++i < size)
		printf("%d ", arr[i]);
	printf("\n");
}

int		ten_power(int n)
{
	int	result;
	
	result = 1;
	while (n-- > 0)
		result *= 10;
	return (result);  // return the power of 10
}

void	radix_sort(int *arr, int size, int max_len)
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
	while (++i < max_len)  // repeat by length of the longest data
	{
		j = -1;
		while (++j < size)  // repeat by number of data
		{
			radix = arr[j] / ten_power(i) % 10;  // extract (j + 1)th digit
			enter_queue(&bucket[radix], arr[j]);  // store extracted numbers in bucket
		}
		j = -1;
		k = -1;
		while (++j < BUCKET_LEN)  // repeat by size of bucket
			while (!queue_is_empty(&bucket[j]))  // repeat until the bucket is empty
				// save back to the array in the order they come out of the bucket
				arr[++k] = delete_queue(&bucket[j]);
	}
}



// 419page. sorting
int		main(void)
{
	int	arr[] = {13, 212, 14, 7141, 10987, 6, 15};
	int	size;
	
	size = sizeof(arr) / sizeof(int);
	show_arr(arr, size);
	radix_sort(arr, size, 5);  // 5 is digit of the largest number
	show_arr(arr, size);
} 
