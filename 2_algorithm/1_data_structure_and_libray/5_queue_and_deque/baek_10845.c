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



void		queue_init(t_queue *q)
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

void		enter_queue(t_queue *q, queue_data data)
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
		return (-999);
	
	remem_node = q->front;  // remember node to be deleted
	remem_data = q->front->data;// remember data to be deleted
	
	q->front = q->front->next;
	free(remem_node);
	return (remem_data);
}



int			ft_strcmp(char *s1, char *s2)
{
	int	i;
	
	i = -1;
	while(s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

void		q_push(t_queue *q)
{
	int	data;
	
	scanf("%d", &data);
	getchar();
	
	enter_queue(q, data);
}

void		q_pop(t_queue *q)
{
	int	data;
	
	data = delete_queue(q);
	
	if (data == -999)
		printf("-1\n");
	else
		printf("%d\n", data);
}

void		q_size(t_queue *q)
{
	t_node	*cur;
	int		size;
	
	if (!q->front)
	{
		printf("0\n");
		return ;
	}
	
	cur = q->front;  // front : starting point;	
	size = 1;
	while (cur != q->rear && size++)
		cur = cur->next;
	
	printf("%d\n", size);
}

void		q_empty(t_queue *q)
{
	if (queue_is_empty(q))
		printf("1\n");
	else
		printf("0\n");
}

void		q_front(t_queue *q)
{
	if (queue_is_empty(q))
	{
		printf("-1\n");
		return ;
	}
	
	printf("%d\n", q->front->data);
}

void		q_back(t_queue *q)
{
	if (queue_is_empty(q))
	{
		printf("-1\n");
		return ;
	}
	
	printf("%d\n", q->rear->data);
}

void		free_all(t_queue *q)
{
	t_node	*cur;
	t_node	*before;
	
	if (queue_is_empty(q))
		return ;

	cur = q->front;  // front : starting point
	while (cur != q->rear)
	{
		before = cur;
		cur = cur->next;
		free(before);
	}
	free(cur);
}

void		q_input(int size)
{
	t_queue	q;
	char	command[6];
	int		i;
	
	queue_init(&q);  // queue reset
	
	i = -1;
	while (++i < size)
	{
		scanf("%s", command);
		getchar();
		if (!ft_strcmp(command, "push"))
			q_push(&q);
		else if (!ft_strcmp(command, "pop"))
			q_pop(&q);
		else if (!ft_strcmp(command, "size"))
			q_size(&q);
		else if (!ft_strcmp(command, "empty"))
			q_empty(&q);
		else if (!ft_strcmp(command, "front"))
			q_front(&q);
		else if (!ft_strcmp(command, "back"))
			q_back(&q);
	}
	
	free_all(&q);
}



int			main(void)
{
	int	size;
	
	scanf("%d", &size);
	getchar();
	
	q_input(size);
}
