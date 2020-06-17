#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 100

typedef	int	queue_data;

typedef	struct	s_queue
{
	int			front;
	int			rear;
	queue_data	q_arr[QUEUE_SIZE];
}				t_queue;



void	queue_init(t_queue *q)
{
	q->front = -1;
	q->rear = -1;
}

void	enter_queue(t_queue *q, queue_data data)
{
	q->q_arr[++(q->rear)] = data;
}

int			queue_is_empty(t_queue *q)
{
	if (q->front == q->rear)
		return (1);
	return (0);
}

queue_data	delete_queue(t_queue *q)
{
	return (q->q_arr[++(q->front)]);
}



// 262page. queue
int		main(void)
{
	t_queue	q;
	int		i;
	
	queue_init(&q);  // queue reset
	
	i = 0;
	while (++i < 5)
		enter_queue(&q, i);  // enter data to queue

	while (!queue_is_empty(&q))
		printf("%d ", delete_queue(&q));  // delete data from queue
	printf("\n");
}
