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
	q->front = -1;
	q->rear = -1;
}

void		queue_put(t_queue *q, queue_data d)
{
	if ((q->rear + 1) % QUEUE_SIZE == q->front)
		printf("queue overflow!\n\n");
	else
		q->q_arr[++(q->rear) % QUEUE_SIZE] = d;
}

void		queue_print(t_queue q)
{
	int i;

	i = q.front;
	printf("----- front -> rear -----\n");
	while (i != q.rear)
	{
		printf("%d\n", q.q_arr[i]);
		i = (i + 1) % QUEUE_SIZE;
	}
	printf("%d\n", q.q_arr[i]);
}

int			queue_is_empty(t_queue *q)
{
	if (q->front == q->rear)
		return (1);
	return (0);
}

queue_data	queue_get(t_queue *q)
{
	return (q->q_arr[++(q->front)]);
}



int			main(void)
{
	t_queue	q;
	int		i;
	
	queue_init(&q);

	i = 0;
	while (++i < 6)
		queue_put(&q, i);
	queue_print(q);

	while (!queue_is_empty(&q))
		printf("%d ", queue_get(&q));
	printf("\n");
}