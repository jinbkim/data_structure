#include <stdio.h>
#include <stdlib.h>

#define STACK_LEN	10

typedef	char	stack_data;

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

int			stack_is_empty(t_stack s)
{
	if (s.top_i >= 0)
		return (0);
	return (1);
}



int		is_operator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (1);
	else
		return (0);
}

int		priority(char c)
{
	if (c == '(' || c == ')')
		return (1);
	else if (c == '+' || c == '-')
		return (2);
	else if (c == '*' || c == '/')
		return (3);
	else
		return (4);
}

int		is_num(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

void	in_to_post(char *in, char *post)
{
	t_stack	s;
	int		i;
	int		j;

	stack_init(&s);
	i = -1;
	j = -1;
	while (in[++i])
	{
		if (in[i] == '(')
			stack_push(&s, in[i]);
		else if (in[i] == ')')
		{
			while (s.stack_arr[s.top_i] != '(')
				post[++j] = stack_pop(&s);
			stack_pop(&s);
		}
		else if (is_operator(in[i]))
		{
			while (!stack_is_empty(s) && (priority(in[i]) <= priority(s.stack_arr[s.top_i])))
				post[++j] = stack_pop(&s);
			stack_push(&s, in[i]);
		}
		else if (is_num(in[i]))
			stack_push(&s, in[i]);
	}

	while (!stack_is_empty(s))
		post[++j] = stack_pop(&s);
	post[++j] = '\0';
}

int		calculator(char *post)
{
	t_stack	s;
	int		i;
	int		op1;
	int		op2;

	stack_init(&s);
	i = -1;
	while (post[++i])
	{
		if (is_num(post[i]))
			stack_push(&s, post[i] - '0');
		else
		{
			op2 = stack_pop(&s);
			op1 = stack_pop(&s);
			if (post[i] == '+')
				stack_push(&s, op1 + op2);
			else if (post[i] == '-')
				stack_push(&s, op1 - op2);
			else if (post[i] == '*')
				stack_push(&s, op1 * op2);
			else if (post[i] == '/')
				stack_push(&s, op1 / op2);
		}	
	}
	return (stack_pop(&s));
}



int		main(int argc, char **argv)
{
	char	post[32];

	if (argc != 2)
	{
		printf("argc is not 2!\n");
		return (0);
	}

	in_to_post(argv[1], post);
	printf("postfix : %s\n", post);
	printf("result : %d\n", calculator(post));
}