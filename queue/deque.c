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



// 284page. queue
int			main(void)
{
	t_deque	dq;
	
	deque_init(&dq);
	
	deque_add_head(&dq, 1);  // add data to deque head
	deque_add_head(&dq, 2);
	deque_add_head(&dq, 3);
	
	deque_add_tail(&dq, 4);  // add data to deque tail
	deque_add_tail(&dq, 5);
	deque_add_tail(&dq, 6);
	
	while (!deque_is_empty(&dq))  // repeat until deque is empty
		printf("%d ", deque_remove_head(&dq));  // remove data from deque head
	printf("\n");
		
	deque_add_head(&dq, 1);
	deque_add_head(&dq, 2);
	deque_add_head(&dq, 3);
	
	deque_add_tail(&dq, 4);
	deque_add_tail(&dq, 5);
	deque_add_tail(&dq, 6);
	
	while (!deque_is_empty(&dq))
		printf("%d ", deque_remove_tail(&dq));  // remove data from deque tail
}
