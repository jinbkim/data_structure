#include <stdio.h>
#include <stdlib.h>

#define STACK_LEN	100

typedef	int	stack_data;

typedef struct	s_stack
{
	stack_data	stack_arr[STACK_LEN];
	int			top_idx;
}				t_stack;



void		stack_init(t_stack *stack)
{
	stack->top_idx = -1;
}

void		stack_push(t_stack *stack, stack_data data)
{
	stack->stack_arr[++(stack->top_idx)] = data;
}

int			stack_is_empty(t_stack *stack)
{
	if (stack->top_idx >= 0)  // if stack is not empty
		return (0);
	return (1);
}

stack_data	stack_pop(t_stack *stack)
{
	return (stack->stack_arr[(stack->top_idx)--]);
}


// 212page. stack
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
