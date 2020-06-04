#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 250



#define CUSOMER_ORDER_TERM	15

#define	CHESSE_BURGER		0
#define	BULGOGI_BURGER		1
#define	DOUBLE_BURGER		2

#define	CHESSE_BURGER_TERM	12
#define	BULGOGI_BURGER_TERM	15
#define	DOUBLE_BURGER_TERM	24



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
	q->rear = 0;
}

int		queue_is_full(t_queue *q)
{
	if (q->rear == QUEUE_SIZE - 1)  // if queueu is full
		return (1);
	return (0);
}

void	enter_queue(t_queue *q, queue_data data)
{
	if (queue_is_full(q))
	{
		printf("queue is full!\n");
		exit (-1);
	}
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
	{
		printf("queue is empty!\n");
		exit (-1);
	}
	return (q->q_arr[++(q->front)]);
}



// 275page. queue
int		main(void)
{
	t_queue	q;
	int		make_process;
	int		cheese_order, bulgogi_order, double_order;
	int		menu;
	int		sec;
	
	queue_init(&q);  // queue reset
	srand(time(NULL));  // initialize time for using random numbers
	cheese_order = bulgogi_order = double_order = 0;
	
	sec = -1;
	while (++sec < 3600)
	{
		if (sec % CUSOMER_ORDER_TERM == 0)  // hamburger orders come in every term
		{
			menu = rand() % 3;
			if (menu == CHESSE_BURGER && ++cheese_order)
				enter_queue(&q, CHESSE_BURGER_TERM);  // enter data to queue
			else if (menu == BULGOGI_BURGER && ++bulgogi_order)
				enter_queue(&q, BULGOGI_BURGER_TERM);
			else if (menu == DOUBLE_BURGER && ++double_order)
				enter_queue(&q, DOUBLE_BURGER_TERM);
		}
		if (make_process <= 0 && queue_is_empty(&q) == 0)
			make_process = delete_queue(&q);  // delete data from queue
		make_process--;
	}
	
	printf("----- one hour hamburger sell simulation -----\n");
	printf("cheese burger : %d\n", cheese_order);
	printf("bulgogi burger : %d\n", bulgogi_order);
	printf("double burger : %d\n", double_order);
	printf("waiting room size : %d\n", QUEUE_SIZE);
}
