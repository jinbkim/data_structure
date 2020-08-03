#include <stdio.h>

#define STACK_LEN	100

typedef	int	stack_data;

typedef struct	s_stack
{
	stack_data	stack_arr[STACK_LEN];
	int			top_i;
}				t_stack;



void		stack_init(t_stack *stack)
{
	stack->top_i = -1;
}

void		stack_push(t_stack *s, stack_data d)
{
	if (s->top_i < STACK_LEN - 1)
		s->stack_arr[++(s->top_i)] = d;
}

void		print_stack(t_stack s)
{
	int	i;

	i = s.top_i + 1;
	printf("----- stack -----\n");
	if (s.top_i == -1)
		printf("empty!\n");
	else
	{
		while (--i >= 0)
			printf("index %d value : %d\n", i, s.stack_arr[i]);
	}
	printf("\n");
}

int			stack_is_empty(t_stack s)
{
	if (s.top_i >= 0)
		return (0);
	return (1);
}

stack_data	stack_pop(t_stack *s)
{
	if (s->top_i >=0)
		return (s->stack_arr[(s->top_i)--]);
	return (-1);
}



// 212page. stack
int			main(void)
{
	t_stack	s;
	int		i;

	stack_init(&s);  // stack reset

	i = 0;
	while (++i < 6)
		stack_push(&s, i);  // push data to stack
	print_stack(s);

	while (!stack_is_empty(s))  // if stack is not empty
		printf("stack pop : %d\n", stack_pop(&s));  // pop data from stack
	printf("\n");
	print_stack(s);
}