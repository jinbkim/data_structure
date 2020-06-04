#include <stdio.h>
#include <stdlib.h>

typedef	int	stack_data;

typedef struct	s_node
{
	stack_data		data;
	struct s_node	*next;  // next node address
}					t_node;

typedef struct	s_stack
{
	t_node		*head;  // head node of stack
}				t_stack;



void		stack_init(t_stack *stack)
{
	stack->head = NULL;
}

void		stack_push(t_stack *stack, stack_data data)
{
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	new_node->next = stack->head;
	stack->head = new_node;
}

int			stack_is_empty(t_stack *stack)
{
	if (stack->head)  // if stack is not empty
		return (0);
	return (1);
}

stack_data	stack_pop(t_stack *stack)
{
	t_node		*remem_node;
	stack_data	remem_data;
	
	if (stack_is_empty(stack))  // if stack is empty
	{
		printf("stack is empty!\n");
		exit (-1);
	}
	
	remem_node = stack->head;  // remember node to be deleted
	remem_data = stack->head->data;  // remember data to be deleted
	
	stack->head = stack->head->next;
	free(remem_node);
	return (remem_data);
}

stack_data	stack_peek(t_stack *stack)
{
	if (stack_is_empty(stack))  // if stack is empty
	{
		printf("stack is empty!\n");
		exit (-1);
	}
	return (stack->head->data);
}



// 217page. stack
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
}
