#include <stdio.h>
#include <stdlib.h>

#define STACK_LEN	101

typedef	double	stack_data;

typedef struct	s_stack
{
	stack_data	stack_arr[STACK_LEN];  // array type stack
	int			top_idx;  // top index of stack
}				t_stack;



void		stack_push(t_stack *stack, stack_data data)
{
	stack->stack_arr[++(stack->top_idx)] = data;
}

stack_data	stack_pop(t_stack *stack)
{
	int		remem_idx;
	
	remem_idx = (stack->top_idx)--;
	return (stack->stack_arr[remem_idx]);
}



int			ft_is_alpha(char c)
{
	if ('A' <= c && c <= 'Z')
		return (1);
	return (0);
}

void		pop_cal_push(t_stack *stack, char oper)
{
	double	op1;
	double	op2;
	
	op2	= stack_pop(stack);
	op1 = stack_pop(stack);
	
	if (oper == '+')
		stack_push(stack, op1 + op2);
	else if (oper == '-')
		stack_push(stack, op1 - op2);
	else if (oper == '*')
		stack_push(stack, op1 * op2);
	else if (oper == '/')
		stack_push(stack, op1 / op2);
}

double		postfix_cal(char *postfix, int *operand)
{
	t_stack	stack;
	int		i;
	
	stack.top_idx = -1;  // stack reset
	
	i = -1;
	while(postfix[++i])
	{
		// if operand, push on stack
		if (ft_is_alpha(postfix[i]))
			stack_push(&stack, operand[postfix[i] - 'A']);
		// if operator, calculate operand from the stack
		else
			pop_cal_push(&stack, postfix[i]);
	}
	
	return (stack_pop(&stack));
}

double		input_postfix(char *postfix, int size)
{
	int	operand[26];
	int	i;
	
	i = -1;
	while (++i < size)
	{
		scanf("%d", &operand[i]);
		getchar();
	}
	return (postfix_cal(postfix, operand));
}



int			main(void)
{
	char	postfix[101];
	int		size;
	
	scanf("%d", &size);
	getchar();
	
	scanf("%s", postfix);
	getchar();
	
	printf("%.2f\n", input_postfix(postfix, size));
}
