#include <stdio.h>
#include <stdlib.h>

#define STACK_LEN	100000

typedef	char	stack_data;

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



int		cutting_bar(char *words)
{
	t_stack	stack;
	int		result;
	int		i;
	
	stack.top_idx = -1;  // stack reset
	
	result = 0;
	i = -1;
	while (words[++i])
	{
		if (words[i] == '(')
			stack_push(&stack, words[i]);
		else if (words[i] == ')' && stack.top_idx >= 0)
		{
			stack_pop(&stack);
			if (words[i - 1] == ')')
				result++;
			else
				result += (stack.top_idx + 1);
			}
		}
	}
	
	return (result);
}



int		main(void)
{
	char	words[100001];

	scanf("%s", words);
	getchar();
	
	printf("%d\n", cutting_bar(words));
}
