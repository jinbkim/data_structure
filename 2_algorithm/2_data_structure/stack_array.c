#include <stdio.h>

#define STACK_LEN	5

typedef	int	stack_data;

typedef struct	s_stack
{
	stack_data	stack_arr[STACK_LEN];
	int			top_i;
}				t_stack;



void		stack_init(t_stack *stack)
{
	printf("\n----- stack init -----\n");
	stack->top_i = -1;
}

void		stack_push(t_stack *s, stack_data d)
{
	if (s->top_i == STACK_LEN - 1)
	{
		printf("current top index : %d\n", s->top_i);
		printf("stack overvlow!\n");
	}
	else
		s->stack_arr[++(s->top_i)] = d;
}

void		stack_print(t_stack s)
{
	int	i;

	i = s.top_i + 1;
	printf("\n----- stack -----\n");
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
	if (s->top_i == -1)
	{
		printf("current top index : %d\n", s->top_i);
		printf("stack underflow!\n");
		return (-1);
	}
	else
		return (s->stack_arr[(s->top_i)--]);
}




int			main(void)
{
	t_stack	s;
	int		i;

	stack_init(&s);

	i = 0;
	while (++i < 7)
		stack_push(&s, i);
	stack_print(s);

	i = -1;
	while (++i < 3)
		printf("stack pop : %d\n", stack_pop(&s));
	stack_print(s);

	stack_init(&s);
	stack_print(s);
}