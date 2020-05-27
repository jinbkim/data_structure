#include <stdio.h>
#include <stdlib.h>

typedef	int	stack_data;

typedef int	list_data;

typedef struct	s_node
{
	stack_data		data;
	struct s_node	*next;  // next node address
}					t_node;

typedef	struct	s_list
{
	t_node		*cur;  // current node of list
	t_node		*before;  // before node of list
	t_node		*tail;  // tail node of list
	int			data_num;  // number of data
}				t_list;

typedef struct	s_stack
{
	t_list		*top;  // head node of stack
}				t_stack;



void		list_init(t_list *list)
{
	list->tail = NULL;
	list->data_num = 0;
}

void		stack_init(t_stack *stack)
{
	stack->top = (t_list *)malloc(sizeof(t_list));
	list_init(stack->top);
}

void		list_insert_front(t_list *list, list_data data)
{	
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	if (!list->tail)  // if list is empty
		list->tail = new_node;
	else
		new_node->next = list->tail->next;
	list->tail->next = new_node;
	(list->data_num)++;
}

void	stack_push(t_stack *stack, stack_data data)
{
	list_insert_front(stack->top, data);
}

int			stack_is_empty(t_stack *stack)
{
	if (stack->top->data_num)  // if stack is not empty
		return (0);
	return (1);
}

int			list_first_node(t_list *list, list_data *data)
{
	if (!list->tail)  // if list is empty
		return (0);
	list->before = list->tail;
	list->cur = list->tail->next;
	*data = list->cur->data;
	return (1);
}

list_data	list_remove(t_list *list)
{
	t_node		*remem_node;
	list_data	remem_data;

	remem_node = list->cur;  // remember node to be deleted
	remem_data = list->cur->data;  // remember data to be deleted
	if (remem_node == list->tail)
	{
		if (list->tail == list->tail->next)  // if remaining one node
			list->tail = NULL;
		else
			list->tail = list->before;
	}
	list->before->next = list->cur->next;
	list->cur = list->before;
	free(remem_node);
	(list->data_num)--;
	return (remem_data);
}

stack_data	stack_pop(t_stack *stack)
{
	stack_data	data;
	
	list_first_node(stack->top, &data);
	list_remove(stack->top);
	return (data);
}



int			main(void)
{
	t_stack	stack;
	int		i;
	
	stack_init(&stack);  // stack reset
	
	i = 0;
	while (++i < 5)
		stack_push(&stack, i);  // push data to stack
	
	while (!stack_is_empty(&stack))  // if stack is not empty
		printf("%d ", stack_pop(&stack));  // pop data from stack
	printf("\n");
	
	free(stack.top);
}
