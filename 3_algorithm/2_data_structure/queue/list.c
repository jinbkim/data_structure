#include <stdio.h>
#include <stdlib.h>

typedef	int	queue_data;

typedef struct		s_node
{
	queue_data		data;
	struct s_node	*next;
	struct s_node	*before;
}					t_node;

typedef	struct	s_queue
{
	t_node		*front;
	t_node		*rear;
}				t_queue;



void	queue_init(t_queue *q)
{
	printf("\n----- queue init -----\n");
	q->front = (t_node *)malloc(sizeof(t_node));
	q->rear = (t_node *)malloc(sizeof(t_node));
	q->front->next = q->rear;
	q->front->before = q->front;
	q->rear->next = q->rear;
	q->rear->before = q->front;
}

void	queue_put(t_queue *q, queue_data d)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;

	node->next = q->rear;
	node->before = q->rear->before;
	q->rear->before->next = node;
	q->rear->before = node;
}

void	queue_print(t_queue q)
{
	t_node	*cur;

	cur = q.front;
	printf("\n----- queue front -> rear -----\n");
	while (cur->next != q.rear)
	{
		cur = cur->next;
		printf("%d\n", cur->data);
	}
}

void		free_all(t_queue *q)
{
	t_node	*cur;

	cur = q->front;
	while (cur != q->rear)
	{
		cur = cur->next;
		free(cur->before);
	}
	free(q->rear);
}

void		clear_queue(t_queue *q)
{
	free_all(q);
	queue_init(q);
}

queue_data	queue_get(t_queue *q)
{
	t_node		*del_n;
	queue_data	del_d;

	if (q->front->next == q->rear)
	{
		printf("queue underflow!\n");
		return (-1);
	}

	del_n = q->front->next;
	del_d = q->front->next->data;

	q->front->next = del_n->next;
	del_n->next->before = q->front;
	free(del_n);
	return (del_d);
}



int		main(void)
{
	t_queue	q;
	int		i;

	queue_init(&q);

	i = 0;
	while (++i < 4)
		queue_put(&q, i);
	queue_print(q);

	clear_queue(&q);

	i = 0;
	while (++i < 4)
		queue_put(&q, i);
	queue_print(q);

	printf("get : %d\n", queue_get(&q));
	queue_print(q);

	free_all(&q);
}