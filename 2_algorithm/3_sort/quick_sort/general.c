#include <stdio.h>
#include <stdlib.h>

#define STACK_LEN	100

typedef	int	stack_data;

typedef struct	s_stack
{
	stack_data	stack_arr[STACK_LEN];
	int			top_i;
}				t_stack;

typedef	int	(*fp)(void *, void *, char);



void	show_arr(void *arr, char type, int num)
{
	int		i;

	printf("----- show array -----\n");
	i = -1;
	while(++i < num)
	{
		if (type == 'i')
			printf("%d ", ((int *)arr)[i]);
		else if (type == 'd')
			printf("%lf ", ((double *)arr)[i]);
		else if (type == 'c')
			printf("%c ", ((char *)arr)[i]);
		else if (type == 's')
			printf("%s ", ((char **)arr)[i]);
	}
	printf("\n\n");
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

// void	trans_type(void *a, void *b, char type)
// {
// 	if (type == 'i')
// 		a = (int *)b;
// 	else if (type == 'd')
// 		a = (double *)b;
// 	else if (type == 'c' || type == 's')
// 		a = (char *)b;
// }

int		comp_func(void *a, void *b, char type)
{
	void	*ptr1;
	void	*ptr2;

	if (type == 'i')
	{
		ptr1 = (int *)a;
		ptr2 = (int *)b;
	}
	else if (type == 'd')
	{
		ptr1 = (double *)a;
		ptr2 = (double *)b;
	}
	else if (type == 'c' || type == 's')
	{
		ptr1 = (char *)a;
		ptr2 = (char *)b;
	}

	if (type == 'i' || type == 'd' || type == 'c')
		return (a - b);
	else if (type == 's')
		return (ft_strcmp(ptr1, ptr2));
	return (0);
}



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



void	*ft_memcpy(void *des, const void *src, size_t len)
{
	const char	*s;
	char		*d;
	size_t		i;

	if (!des || !src)
		return (NULL);
	d = (char *)des;
	s = (const char *)src;
	i = -1;
	while (++i < len)
		d[i] = s[i];
	return(d);
}

void	ft_swap(void *a, void *b, size_t len)
{
	void	*temp;

	if (!(temp = malloc(len)))
		return ;
	ft_memcpy(temp, a, len);
	ft_memcpy(a, b, len);
	ft_memcpy(b, temp, len);
	free(temp);
}

int		median_pivot(void *arr, int left, int right, char type, fp f)
{
	int		ex[] = {left, (left + right) / 2, right};
	void	*ptr;
	if (type == 'i')
		ptr = (int *)arr;
	else if (type == 'd')
		ptr = (double *)arr;
	else if (type == 'c' || type == 's')
		ptr = (char *)arr;


	if (f(ptr[left], ))
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


void	quick_sort(void *arr, int n, char type)
{
	t_stack	s;
	void	*ptr;
	int		left;
	int		right;
	int		pivot_i;

	if (type == 'i')
		ptr = (int *)arr;
	else if (type == 'd')
		ptr = (double *)arr;
	else if (type == 'c' || type == 's')
		ptr = (char *)arr;

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
			pivot_i = median_pivot(ptr, left, right, type, comp_func);
		}
	}
}


int		main(void)
{
	int 	arr1[] = {5, 4, 3, 2, 1};
	double	arr2[] = {5.5, 4.4, 3.3, 2.2, 1.1};
	char	arr3[] = {'e', 'd', 'c', 'b', 'a'};
	char	*arr4[] = {"hi", "my", "name", "is", "jinbkim"};

	show_arr(arr1, 'i', sizeof(arr1) / sizeof(int));
	quick_sort(arr1, sizeof(arr1) / sizeof(int), 'i');
	// show_arr(arr1, 'i', sizeof(arr1) / sizeof(int));

	show_arr(arr2, 'd', sizeof(arr2) / sizeof(double));
	// quick_sort(arr2, sizeof(arr2) / sizeof(double), comp_func);
	// show_arr(arr2, 'd', sizeof(arr2) / sizeof(double));

	show_arr(arr3, 'c', sizeof(arr3) / sizeof(char));
	// quick_sort(arr3, sizeof(arr3) / sizeof(char), comp_func);
	// show_arr(arr3, 'c', sizeof(arr3) / sizeof(char));

	show_arr(arr4, 's', sizeof(arr4) / sizeof(char *));
	// quick_sort(arr4, sizeof(arr4) / sizeof(char *), comp_func);
	// show_arr(arr4, 's', sizeof(arr4) / sizeof(char *));

}