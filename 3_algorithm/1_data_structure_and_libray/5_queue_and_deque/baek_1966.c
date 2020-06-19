#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 1000

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



int			find_max(t_queue *q)
{
	int 	max;
	int		i;

	max = q->q_arr[q->front];  // front : starting point
	
	i = q->front;
	while (++i <= q->rear)
		if (max < q->q_arr[i])
			max = q->q_arr[i];
	
	return (max);
}

int			when_print(t_queue *q, int idx)
{
	int	count;  // output order
	int max;
	int	i;
	
	i = q->front;  // front : starting point
	
	count = 1;
	while(1)
	{
		max = find_max(q);
		
		if (i == idx && q->q_arr[i] == max)  // data found
			break ;
		if (i == idx)
			idx = q->rear + 1;  // change index of data to find
		if (q->q_arr[i] == max)
			count++;
		else
			enter_queue(q, q->q_arr[i]);
		
		delete_queue(q);
		max = find_max(q);
		i++;
	}
	
	return (count);
}

void		q_input(int size)
{
	t_queue	q;
	int		data;
	int		num;
	int		idx;
	int		i;
	int		j;
	
	i = -1;
	while(++i < size)
	{
		queue_init(&q);  // queue reset
		scanf("%d %d", &num, &idx);
		getchar();
		
		j = -1;
		while (++j < num)
		{
			scanf("%d", &data);
			enter_queue(&q, data);
		}
		
		printf("%d\n", when_print(&q, idx));
	}
}



int			main(void)
{
	int	size;
	
	scanf("%d", &size);
	getchar();
	
	q_input(size);
}
