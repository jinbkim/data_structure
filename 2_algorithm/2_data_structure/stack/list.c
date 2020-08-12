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
	t_node		*tail;
}				t_stack;



void		stack_init(t_stack *s)
{
	printf("\n----- stack init -----\n");
	s->head = (t_node *)malloc(sizeof(t_node));
	s->tail = (t_node *)malloc(sizeof(t_node));
	s->head->next = s->tail;
	s->tail->next = s->tail;
}

void		stack_push(t_stack *s, stack_data d)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;

	node->next = s->head->next;
	s->head->next = node;
}

void		stack_print(t_stack s)
{
	t_node	*cur;

	printf("\n----- stack -----\n");
	if (s.head->next == s.tail)
	{
		printf("empty!\n");
		return ;
	}
	cur = s.head->next;
	while (cur != s.tail)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n\n");
}

int			stack_is_empty(t_stack *s)
{
	if (s->head->next == s->tail)
		return (1);
	return (0);
}

stack_data	stack_pop(t_stack *s)
{
	t_node		*del_n;
	stack_data	del_d;

	if (s->head->next == s->tail)
	{
		printf("stack underflow!\n");
		return (-1);
	}

	del_n = s->head->next;
	del_d = s->head->next->data;

	s->head->next = del_n->next;
	free(del_n);
	return (del_d);
}

void		free_all(t_stack *s)
{
	t_node	*before;
	t_node	*cur;

	before = s->head;
	cur = s->head->next;
	while (before != s->tail)
	{
		free(before);
		before = cur;
		cur = cur->next;
	}
	free(s->tail);
}

void		clear_stack(t_stack *s)
{
	free_all(s);
	stack_init(s);
}



int			main(void)
{
	t_stack	s;
	int		i;

	stack_init(&s);

	i = 0;
	while (++i < 6)
		stack_push(&s, i);
	stack_print(s);

	printf("pop : %d\n", stack_pop(&s));
	stack_print(s);

	clear_stack(&s);
	stack_print(s);

	free_all(&s);
}