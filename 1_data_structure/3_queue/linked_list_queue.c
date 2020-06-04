#include <stdio.h>
#include <stdlib.h>

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
	q->rear = NULL;
}

int			queue_is_empty(t_queue *q)
{
	if (!q->front)
		return (1);
	return (0);
}

void	enter_queue(t_queue *q, queue_data data)
{
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	new_node->next = NULL;
	
	if (queue_is_empty(q))
	{
		q->front = new_node;
		q->rear = new_node;
	}
	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
}

queue_data	delete_queue(t_queue *q)
{
	t_node		*remem_node;
	queue_data	remem_data;
	
	if (queue_is_empty(q))
	{
		printf("queue is empty!\n");
		exit (-1);
	}
	
	remem_node = q->front;  // remember node to be deleted
	remem_data = q->front->data;// remember data to be deleted
	
	q->front = q->front->next;
	free(remem_node);
	return (remem_data);
}



// 271page. queue
int		main(void)
{
	t_queue	q;
	int		i;
	
	queue_init(&q);  // queue reset
	
	i = 0;
	while (++i < 5)
		enter_queue(&q, i);  // enter data to queue

	while (!queue_is_empty(&q))  // if queue is not empty
		printf("%d ", delete_queue(&q));  // delete data from queue
	printf("\n");
}
