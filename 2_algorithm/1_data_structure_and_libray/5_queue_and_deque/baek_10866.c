#include <stdio.h>
#include <stdlib.h> 

typedef	int	deque_data;

typedef struct		s_node
{
	deque_data		data;
	struct s_node	*next;  // next node address
	struct s_node	*before;  // before node address
}					t_node;

typedef	struct	s_deque
{
	t_node		*head;  // head node of deque
	t_node		*tail;  // tail node of deque
}				t_deque;



void		deque_init(t_deque *deque)
{
	deque->head = NULL;
}

int			deque_is_empty(t_deque *deque)
{
	if (deque->head)
		return (0);
	return (1);
}

void		deque_add_head(t_deque *deque, deque_data data)
{
	t_node	*new_node;
	
	// data set
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	// add node to head
	new_node->before = NULL;
	if (deque_is_empty(deque))
	{
		new_node->next = NULL;
		deque->tail = new_node;
	}
	else
	{
		new_node->next = deque->head;
		deque->head->before = new_node;
	}
	deque->head = new_node;
}

void		deque_add_tail(t_deque *deque, deque_data data)
{
	t_node	*new_node;
	
	// data set
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	// add node to tail
	new_node->next = NULL;
	if (deque_is_empty(deque))
	{
		new_node->before = NULL;
		deque->head = new_node;
	}
	else
	{	new_node->before = deque->tail;
		deque->tail->next = new_node;
	}
	deque->tail = new_node;
}

deque_data	deque_remove_head(t_deque *deque)
{
	t_node		*remem_node;
	deque_data	remem_data;
	
	remem_node = deque->head;  // remember node to be deleted
	remem_data = deque->head->data;  // remember data to be deleted
	
	if (deque_is_empty(deque))
	{
		printf("deque is empty!\n");
		exit (-1);
	}
	deque->head = deque->head->next;  // head node move
	if (deque->head)
		deque->head->before = NULL;
	else  // if one remaining node
		deque->tail = NULL;
	free(remem_node);
	return (remem_data);
}

deque_data	deque_remove_tail(t_deque *deque)
{
	t_node		*remem_node;
	deque_data	remem_data;
	
	remem_node = deque->tail;  // remember node to be deleted
	remem_data = deque->tail->data;  // remember data to be deleted
	
	if (deque_is_empty(deque))
	{
		printf("deque is empty!\n");
		exit (-1);
	}
	deque->tail = deque->tail->before;  // tail node move
	if (deque->tail)
		deque->tail->next = NULL;
	else  // if one remaining node
		deque->head = NULL;
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

void		dq_push_front(t_deque *dq)
{
	int	data;
	
	scanf("%d", &data);
	getchar();
	
	deque_add_head(dq, data);
}

void		dq_push_back(t_deque *dq)
{
	int	data;
	
	scanf("%d", &data);
	getchar();
	
	deque_add_tail(dq, data);
}

void		dq_pop_front(t_deque *dq)
{
	if (deque_is_empty(dq))
	{
		printf("-1\n");
		return ;
	}

	printf("%d\n", deque_remove_head(dq));
}

void		dq_pop_back(t_deque *dq)
{
	if (deque_is_empty(dq))
	{
		printf("-1\n");
		return ;
	}

	printf("%d\n", deque_remove_tail(dq));	
}

void		dq_size(t_deque *dq)
{
	t_node	*cur;
	int		size;
	
	if (!(dq->head))
	{
		printf("0\n");
		return ;
	}
	
	cur = dq->head;  // head : starting point	
	size = 1;
	while (cur != dq->tail && size++)
		cur = cur->next;
	
	printf("%d\n", size);	
}

void		dq_empty(t_deque *dq)
{
	if (deque_is_empty(dq))
		printf("1\n");
	else
		printf("0\n");
}

void		dq_front(t_deque *dq)
{
	if (deque_is_empty(dq))
	{
		printf("-1\n");
		return ;
	}
	
	printf("%d\n", dq->head->data);
}

void		dq_back(t_deque *dq)
{
	if (deque_is_empty(dq))
	{
		printf("-1\n");
		return ;
	}
	
	printf("%d\n", dq->tail->data);	
}

void		free_all(t_deque *dq)
{
	t_node	*cur;
	
	if (deque_is_empty(dq))
		return ;

	cur = dq->head;  // head : starting point
	while (cur != dq->tail)
	{
		cur = cur->next;
		free(cur->before);
	}
	free(cur);
}

void		dq_input(int size)
{
	t_deque	dq;
	char	command[11];
	int		i;

	deque_init(&dq);  // deque reset
	
	i = -1;
	while (++i < size)
	{
		scanf("%s", command);
		getchar();

		if (!ft_strcmp(command, "push_front"))
			dq_push_front(&dq);
		else if (!ft_strcmp(command, "push_back"))
			dq_push_back(&dq);
		else if (!ft_strcmp(command, "pop_front"))
			dq_pop_front(&dq);
		else if (!ft_strcmp(command, "pop_back"))
			dq_pop_back(&dq);
		else if (!ft_strcmp(command, "size"))
			dq_size(&dq);
		else if (!ft_strcmp(command, "empty"))
			dq_empty(&dq);
		else if (!ft_strcmp(command, "front"))
			dq_front(&dq);
		else if (!ft_strcmp(command, "back"))
			dq_back(&dq);
	}
	
	free_all(&dq);
}



int			main(void)
{
	int	size;
	
	scanf("%d", &size);
	getchar();
	
	dq_input(size);
}
