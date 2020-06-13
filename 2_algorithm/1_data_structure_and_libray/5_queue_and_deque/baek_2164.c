#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 1000000

typedef	int	queue_data;

typedef	struct	s_queue
{
	int			front;  // front of queue
	int			rear;  // rear of queue
	queue_data	q_arr[QUEUE_SIZE];
}				t_queue;



void	queue_init(t_queue *q)
{
	q->front = 0;
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
	if (queue_is_empty(q))
		return (-999);
	return (q->q_arr[(q->front)++]);
}



int			q_input(int size)
{
	t_queue	q;
	int		i;
	
	queue_init(&q);  // queue reset

	if (size == 1)
		return (1);

	i = 0;
	while (++i <= size)
		enter_queue(&q, i);
	
	// consider when size is even or odd
	while (q.front + 1 != q.rear)
	{
		delete_queue(&q);
		enter_queue(&q, delete_queue(&q));	
	}

	return (q.q_arr[q.rear]);
}



int			main(void)
{
	int	size;
	
	scanf("%d", &size);
	getchar();
	
	printf("%d\n", q_input(size));
}
