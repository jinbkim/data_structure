#include <stdio.h>
#include <stdlib.h>

#define STACK_LEN	51

typedef	int	stack_data;

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

char	stack_put_in(char *words)
{
	t_stack	stack;
	int		i;

	stack.top_idx = -1;  // stack reset
	
	i = -1;
	while (words[++i])
	{
		stack_push(&stack, words[i]);
		if (stack.top_idx > 0 && stack.stack_arr[stack.top_idx] == ')' && stack.stack_arr[stack.top_idx - 1] == '(')
		{
			stack_pop(&stack);
			stack_pop(&stack);
		}
	}

	if (stack.top_idx >= 0)  // if stack is not empty
		return (0);
	return ('1');
}

char	*bracket_input(int size)
{
	char	*braket;
	char	words[51];
	int		i;
	
	braket = (char *)malloc(size);
	
	i = -1;
	while (++i < size)
	{
		scanf("%s", words);
		getchar();
		braket[i] = stack_put_in(words);  // 0 : no, 1 : yes
	}
	
	return (braket);
}



void	print_braket(char *braket, int size)
{
	int i;
	
	i = -1;
	while (++i < size)
	{
		if (braket[i])
			printf("YES\n");
		else
			printf("NO\n");
	}	
}



int		main(void)
{
	char	*braket;
	int		size;
	
	scanf("%d", &size);
	getchar();
	
	braket = bracket_input(size);
	print_braket(braket, size);
	free(braket);
}
