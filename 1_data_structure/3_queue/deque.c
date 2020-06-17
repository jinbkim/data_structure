#include <stdio.h>
#include <stdlib.h> 

typedef	int	deque_data;

typedef struct		s_node
{
	deque_data		data;
	struct s_node	*next;
	struct s_node	*before;
}					t_node;

typedef	struct	s_deque
{
	t_node		*head;
	t_node		*tail;
}				t_deque;



void		deque_init(t_deque *deque)
{
	deque->head = NULL;
	deque->tail = NULL;
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
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	new_node->next = deque->head;
	new_node->before = NULL;
	if (deque->head)
		deque->head->before = new_node;
	else
		deque->tail = new_node;
	deque->head = new_node;
}

void		deque_add_tail(t_deque *deque, deque_data data)
{
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	new_node->next = NULL;
	new_node->before = deque->tail;
	if (deque->head)
		deque->tail->next = new_node;
	else
		deque->head = new_node;
	deque->tail = new_node;
}

deque_data	deque_remove_head(t_deque *deque)
{
	t_node		*remem_node;
	deque_data	remem_data;
	
	remem_node = deque->head;  // remember node to be deleted
	remem_data = deque->head->data;  // remember data to be deleted
	
	deque->head = deque->head->next;  // head reset
	
	if (deque->head)  // if deque has one more node
		deque->head->before = NULL;

	free(remem_node);
	return (remem_data);
}

deque_data	deque_remove_tail(t_deque *deque)
{
	t_node		*remem_node;
	deque_data	remem_data;
	
	remem_node = deque->tail;  // remember node to be deleted
	remem_data = deque->tail->data;  // remember data to be deleted
	
	deque->tail = deque->tail->before;  // tail reset
	
	if (deque->tail)
		deque->tail->next = NULL;
	else  // if deque has one node
		deque->head = NULL;
	
	free(remem_node);
	return (remem_data);
}



// 284page. queue
int			main(void)
{
	t_deque	dq;
	
	deque_init(&dq);  // deque reset
	
	deque_add_head(&dq, 1);
	deque_add_head(&dq, 2);
	deque_add_head(&dq, 3);
	
	deque_add_tail(&dq, 4);
	deque_add_tail(&dq, 5);
	deque_add_tail(&dq, 6);
	
	while (!deque_is_empty(&dq))
		printf("%d ", deque_remove_head(&dq));  // remove data from deque head
	printf("\n");
		
	deque_add_tail(&dq, 1);
	deque_add_tail(&dq, 2);
	deque_add_tail(&dq, 3);
	
	deque_add_head(&dq, 4);
	deque_add_head(&dq, 5);
	deque_add_head(&dq, 6);
	
	while (!deque_is_empty(&dq))
		printf("%d ", deque_remove_tail(&dq));  // remove data from deque tail
	printf("\n");
}
