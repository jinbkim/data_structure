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

void	ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int		median_pivot(int *arr, int left, int right)
{
	int	ex[] = {left, (left + right) / 2, right};

	if (arr[ex[1]] < arr[ex[0]])
		ft_swap(&ex[0], &ex[1]);
	if (arr[ex[2] < arr[ex[1]]])
		ft_swap(&ex[1], &ex[2]);
	if (arr[ex[1]] < arr[ex[0]])
		ft_swap(&ex[0], &ex[1]);
	return (ex[1]);
}

void	quick_sort(int *arr, int n)
{
	t_stack	s;
	int		pivot;
	int		pivot_i;
	int		left;
	int		right;
	int		i;
	int		j;

	left = 0;
	right = n - 1;
	stack_init(&s);
	stack_push(&s, right);
	stack_push(&s, left);
	while (!stack_is_empty(s))
	{
		left = stack_pop(&s);
		right = stack_pop(&s);
		if (0 < right - left)
		{
			pivot_i = median_pivot(arr, left, right);
			pivot = arr[pivot_i];
			ft_swap(&arr[pivot_i], &arr[right]);
			i = left;
			j = right - 1;
			while (1)
			{
				while (arr[i] < pivot && i < right)
					i++;
				while (pivot < arr[j] && 0 < j)
					j--;
				if (j <= i)
					break ;
				ft_swap(&arr[i], &arr[j]);
			}
			ft_swap(&arr[i], &arr[right]);
			stack_push(&s, right);
			stack_push(&s, i + 1);
			stack_push(&s, i - 1);
			stack_push(&s, left);
		}
		show_arr(arr, 5);
	}	
}



int		main(void)
{
	int arr[] = {5, 4, 3, 2, 1};

	show_arr(arr, sizeof(arr) / sizeof(int));
	quick_sort(arr, sizeof(arr) / sizeof(int));
	show_arr(arr, sizeof(arr) / sizeof(int));
}