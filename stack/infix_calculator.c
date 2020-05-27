#include <stdio.h>
#include <stdlib.h>

typedef	char	stack_data;

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
	if ('0' <= c && c <= '9')  // if c is natural number
		return (1);
	return (0);
}

int		set_priority(char oper)
{
	if (oper == '(')
		return (1);
	else if (oper == '+' || oper == '-')
		return (2);
	else if (oper == '*' || oper == '/')
		return (3);
	return (0);
}

int		comp_priority(char op1, char op2)
{
	if (set_priority(op1) >= set_priority(op2))  // if op1 is bigger than op2(priority)
		return (1);
	else
		return (0);
}

char	*use_stack(t_stack *stack, char *postfix, char oper)
{
	char	data;

	if (oper == '(')
		stack_push(stack, oper);
	else if (oper == ')')
		while (1)
		{
			data = stack_pop(stack);
			if (data == '(')
				break;
			*postfix++ = data;
		}
	else if(oper == '+' || oper == '-' || oper == '*' || oper == '/')
	{
		while (!stack_is_empty(stack) && comp_priority(stack_peek(stack), oper))  // stack is not empty, top of stack is bigger than oper(priority)
			*postfix++ = stack_pop(stack);
		stack_push(stack, oper);
	}
	return (postfix);  // new postfix adress return
}

char	*ft_strcpy(char *s1, char *s2)
{
	int i;
	
	i = -1;
	while (s2[++i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

void	infix_to_postfix(char *equ)
{
	t_stack	stack;
	char	*postfix;
	char	*remem_postfix;  // remember postfix adress
	int		i;
	
	stack_init(&stack);
	postfix = (char *)malloc(ft_strlen(equ) + 1);
	postfix[ft_strlen(equ)] = '\0';
	remem_postfix = postfix;  // remember postfix adress
	
	i = -1;
	while (++i < ft_strlen(equ))  // repeat equ_len
	{
		if (ft_isdigit(equ[i]))
			*postfix++ = equ[i];
		else
			postfix = use_stack(&stack, postfix, equ[i]);
	}
	while (!stack_is_empty(&stack))  // until the stack is empty, repeat
		*postfix++ = stack_pop(&stack);
	*postfix = '\0';  // because of braces, the length of equ changes, so pull '\0' at the end 
	ft_strcpy(equ, remem_postfix);
	free(remem_postfix);
}



void	pop_cal_push(t_stack *stack, char oper)
{
	char	op1;  // operand1
	char	op2;  // operand2
	
	op2 = stack_pop(stack);
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

int		postfix_cal(char *equ)
{
	t_stack	stack;
	int		i;
	int 	result;
	
	stack_init(&stack);
	i = -1;
	while (++i < ft_strlen(equ))  // repeat equ_len
	{
		if(ft_isdigit(equ[i]))
			stack_push(&stack, equ[i] - '0');  // data conversion for calculation
		else
			pop_cal_push(&stack, equ[i]);  // pop data, calculate, push data 
	}
	result = stack_pop(&stack);
	return (result);
}

int		infix_cal(char *equ)
{
	infix_to_postfix(equ);  // conversion infinx to postfix
	return (postfix_cal(equ));  // return calculation result
}



// 246page. stack
int		main(void)
{
	char equ1[] = "1+2*3";
	char equ2[] = "(1+2)*3";
	char equ3[] = "((1-2)+3)*(5-2)";
	
	printf("%s = %d\n", equ1, infix_cal(equ1));  // calculation result
	printf("%s = %d\n", equ2, infix_cal(equ2));
	printf("%s = %d\n", equ3, infix_cal(equ3));
}
