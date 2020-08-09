#include <stdio.h>
#include <stdlib.h>

#define STACK_LEN	100

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

int			stack_is_empty(t_stack s)
{
	if (s.top_i >= 0)
		return (0);
	return (1);
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



void	show_arr(int *arr, int size)
{
	int i ;
	
	i = -1;
	while(++i < size)
		printf("%d ", arr[i]);
	printf("\n");
}

int		get_bits(int x, int bit, int size)
{
	return ((x >> bit) & ~(~0 << size)); 
}

void	ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	radix_sort(int *arr, int n, int bit)
{
	t_stack	s;
	int		left;
	int		right;
	int		i;
	int		j;

	left = 0;
	right = n - 1;
	stack_init(&s);
	stack_push(&s, bit);
	stack_push(&s, right);
	stack_push(&s, left);
	while (!stack_is_empty(s))
	{
		left = stack_pop(&s);
		right = stack_pop(&s);
		bit = stack_pop(&s);
		if (left <= right && bit >= 0)
		{
			i = left;
			j = right;
			while (1)
			{
				while (!get_bits(arr[i], bit, 1) && i < j)
					i++;
				while (get_bits(arr[j], bit, 1) && i < j)
					j--;
				if (j <= i)
					break;
				ft_swap(&arr[i], &arr[j]);
			}
			if (!get_bits(arr[right], bit, 1))
				j++;
			stack_push(&s, bit - 1);
			stack_push(&s, right);
			stack_push(&s, j);
			stack_push(&s, bit - 1);
			stack_push(&s, j - 1);
			stack_push(&s, left);
		}
	}
}



int		main(void)
{
	int	arr[] = {593, 9, 611, 86, 900, 55, 77, 302};

	show_arr(arr, sizeof(arr) / sizeof(int));
	radix_sort(arr, sizeof(arr) / sizeof(int), 16);
	show_arr(arr, sizeof(arr) / sizeof(int));
}