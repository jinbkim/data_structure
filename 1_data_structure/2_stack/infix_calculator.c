#include <stdio.h>
#include <stdlib.h>

typedef	int	stack_data;

typedef struct		s_node
{
	stack_data		data;
	struct s_node	*next;
}					t_node;

typedef struct	s_stack
{
	t_node		*head;
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
	if (stack->head)
		return (0);
	return (1);
}

stack_data	stack_pop(t_stack *stack)
{
	t_node		*remem_node;
	stack_data	remem_data;
	
	remem_node = stack->head;  // remember node to be deleted
	remem_data = stack->head->data;  // remember data to be deleted
	
	stack->head = stack->head->next;
	free(remem_node);
	return (remem_data);
}



int		ft_strlen(char *s)
{
	int		i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int			set_priority(char op)
{
	if (op == '(')
		return (1);
	else if (op == '+' || op =='-')
		return (2);
	else if (op == '*' || op == '/')
		return (3);
	return (0);
}

int			priority_comp(char op1, char op2)
{
	return (set_priority(op1) - set_priority(op2));	
}

char		*infix_to_postfix(char *exp)
{
	t_stack	stack;
	char	*postfix;
	char	data;
	int		post_i;
	int		i;
	
	stack_init(&stack);  // stack reset
	
	postfix = (char *)malloc(ft_strlen(exp) + 1);
	
	post_i = -1;
	i = -1;
	while (++i < ft_strlen(exp))
	{
		if (ft_isdigit(exp[i]))
			postfix[++post_i] = exp[i];
			
		else if (exp[i] == '(')
			stack_push(&stack, exp[i]);
		else if (exp[i] == ')')
		{
			while (1)
			{
				data = stack_pop(&stack);
				if (data == '(')
					break;
				postfix[++post_i] = data;
			}
		}
		
		// if priority is loswer than stack head, take it out of stack
		// after, put on stack  
		else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
		{
			while (!stack_is_empty(&stack) && priority_comp(stack.head->data, exp[i]) >= 0)
				postfix[++post_i] = stack_pop(&stack);
			stack_push(&stack, exp[i]);
		}
	}

	while (!stack_is_empty(&stack))
		postfix[++post_i] = stack_pop(&stack);
	postfix[++post_i] = '\0';	

	return (postfix);
}

int			postfix_cal(char *equ)
{
	t_stack	stack;
	char	op1;
	char	op2;
	int		i;
	
	stack_init(&stack);
	
	i = -1;
	while (++i < ft_strlen(equ))
	{
		if (ft_isdigit(equ[i]))
			stack_push(&stack, equ[i] - '0');  // data conversion for calculation
		else
		{
			op2 = stack_pop(&stack);  // the first retrieved value is the second operand
			op1 = stack_pop(&stack);
			
			if (equ[i] == '+')
				stack_push(&stack, op1 + op2);
			else if (equ[i] == '-')
				stack_push(&stack, op1 - op2);
			else if (equ[i] == '*')
				stack_push(&stack, op1 * op2);
			else if (equ[i] == '/')
				stack_push(&stack, op1 / op2);		
		}
	}

	return (stack_pop(&stack));
}

int			infix_cal(char *exp)
{
	char	*postfix;
	int		result;
	
	postfix = infix_to_postfix(exp);
	result = postfix_cal(postfix);
	
	free(postfix);
	return (result);
}



int 		main(void)
{
	char exp1[] = "1+2*3";
	char exp2[] = "(1+2)*3";
	char exp3[] = "((1-2)+3)*(5-2)";

	printf("%s = %d \n", exp1, infix_cal(exp1));
	printf("%s = %d \n", exp2, infix_cal(exp2));
	printf("%s = %d \n", exp3, infix_cal(exp3));
}
