#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE	10

typedef	char		bt_data;

typedef	struct			s_bt_node
{
	bt_data				data;
	struct s_bt_node	*left;
	struct s_bt_node	*right;
}						t_bt_node;

typedef	t_bt_node	*stack_data;

typedef	struct	s_list
{
	t_bt_node	*head;
	t_bt_node	*tail;
}				t_list;

typedef struct	s_stack
{
	stack_data	stack_arr[STACK_SIZE];
	int			top_i;
}				t_stack;



int			ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}



void		stack_init(t_stack *stack)
{
	printf("\n----- stack init -----\n");
	stack->top_i = -1;
}

stack_data	stack_pop(t_stack *s)
{
	if (s->top_i == -1)
	{
		printf("current top index : %d\n", s->top_i);
		printf("stack underflow!\n");
		return (NULL);
	}
	else
		return (s->stack_arr[(s->top_i)--]);
}

void		stack_push(t_stack *s, stack_data d)
{
	if (s->top_i == STACK_SIZE - 1)
	{
		printf("current top index : %d\n", s->top_i);
		printf("stack overvlow!\n");
	}
	else
		s->stack_arr[++(s->top_i)] = d;
}



void		tree_init(t_list *l)
{
	printf("\n----- tree init -----\n");
	l->head = (t_bt_node *)malloc(sizeof(t_bt_node));
	l->tail = (t_bt_node *)malloc(sizeof(t_bt_node));

	l->head->left = l->tail;
	l->head->right = l->head;
	l->tail->left = l->tail;
	l->tail->right = l->tail;
}

t_bt_node	*make_e_tree(char *exp, t_list *l)
{
	t_bt_node	*node;
	t_stack		s;
	int			i;

	stack_init(&s);
	i = -1;
	while (exp[++i])
	{
		node = (t_bt_node *)malloc(sizeof(t_bt_node));
		node->data = exp[i];
		node->left = l->tail;
		node->right = l->tail;
		if (!ft_isdigit(exp[i]))
		{
			node->right = stack_pop(&s);
			node->left = stack_pop(&s);
		}
		stack_push(&s, node);
	}
	return (stack_pop(&s));
}



void	preorder_traverse(t_bt_node *node, t_list *l)
{
	if (node != l->tail)
	{
		printf("%c ",node->data);
		preorder_traverse(node->left, l);
		preorder_traverse(node->right, l);
	}
}

void	inorder_traverse(t_bt_node *node, t_list *l)
{
	if (node != l->tail)
	{
		inorder_traverse(node->left, l);
		printf("%c ",node->data);
		inorder_traverse(node->right, l);
	}
}

void	postorder_traverse(t_bt_node *node, t_list *l)
{
	if (node != l->tail)
	{
		postorder_traverse(node->left, l);
		postorder_traverse(node->right, l);
		printf("%c ",node->data);

	}
}



int		cal_tree(t_bt_node *node, t_list l)
{
	int	op1;
	int	op2;

	if (node->left == l.tail && node->right == l.tail)
		return (node->data);
	op1 = cal_tree(node->left, l) - '0';
	op2 = cal_tree(node->right, l) - '0';
	printf("op1 : %d, op2 : %d\n", op1, op2);
	printf("data : %c\n", node->data);
	if (node->data == '+')
		return (op1 + op2);
	else if (node->data == '-')
		return (op1 - op2);
	else if (node->data == '*')
		return (op1 * op2);
	else if (node->data == '/')
		return (op1 / op2);
	else
		return (0);
}


int		main(void)
{
	char		exp[] = "12+43-5*";
	t_list		l;

	tree_init(&l);

	l.head->left = make_e_tree(exp, &l);
	printf("\n----- preorder traverse -----\n");
	preorder_traverse(l.head->left, &l);
	printf("\n----- inorder traverse -----\n");
	inorder_traverse(l.head->left, &l);
	printf("\n----- postorder traverse -----\n");
	postorder_traverse(l.head->left, &l);
	printf("\n");

	printf("result : %d\n", cal_tree(l.head->left, l));
}

