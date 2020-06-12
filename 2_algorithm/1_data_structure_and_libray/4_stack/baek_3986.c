#include <stdio.h>
#include <stdlib.h>

#define STACK_LEN	100

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



int		is_good_words(char *words)
{
	t_stack	stack;
	int		i;
	
	stack.top_idx = -1;  // stack reset
	
	i = -1;
	while (words[++i])
	{
		stack_push(&stack, words[i]);
		if (stack.top_idx > 0 && stack.stack_arr[stack.top_idx] == stack.stack_arr[stack.top_idx - 1])
		{
			stack_pop(&stack);
			stack_pop(&stack);
		}
	}
	
	if (stack.top_idx >= 0)  // if stack is not empty
		return (0);
	return (1);
}

int		words_input(int size)
{
	char	words[100001];
	int		result;
	int		i;
	
	result = 0;
	i = -1;
	while (++i < size)
	{
		scanf("%s", words);
		getchar();
		if (is_good_words(words))
			result++;
	}
	
	return (result);
}



int		main(void)
{
	int	size;

	scanf("%d", &size);
	getchar();
	
	printf("%d\n", words_input(size));
}
