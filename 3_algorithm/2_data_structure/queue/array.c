#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 5

typedef	int	queue_data;

typedef	struct	s_queue
{
	int			front;
	int			rear;
	queue_data	q_arr[QUEUE_SIZE];
}				t_queue;



void		queue_init(t_queue *q)
{
	printf("\n----- queue init -----\n");
	q->front = -1;
	q->rear = -1;
}

void		queue_put(t_queue *q, queue_data d)
{
	if (q->front + QUEUE_SIZE == q->rear)
		printf("queue overflow!\n");
	else
		q->q_arr[++(q->rear) % QUEUE_SIZE] = d;
}

void		queue_print(t_queue q)
{
	int i;

	i = q.front;
	printf("\n----- queue front -> rear -----\n");
	while (++i <= q.rear)
		printf("%d\n", q.q_arr[i % QUEUE_SIZE]);
}

int			queue_is_empty(t_queue *q)
{
	if (q->front == q->rear)
		return (1);
	return (0);
}

queue_data	queue_get(t_queue *q)
{
	if (q->front == q->rear)
	{
		printf("queue underflow!\n");
		return (-1);
	}
	else
		return (q->q_arr[++(q->front) % QUEUE_SIZE]);
}



int			main(void)
{
	t_queue	q;
	int		i;
	
	queue_init(&q);

	i = 0;
	while (++i <= QUEUE_SIZE + 1)
		queue_put(&q, i);
	queue_print(q);

	queue_init(&q);

	i = -1; 
	while (++i < 3)
		queue_put(&q, i);
	queue_print(q);

	i = -1;
	while (++i <= 4)
		printf("get : %d\n", queue_get(&q));
	queue_print(q);
}