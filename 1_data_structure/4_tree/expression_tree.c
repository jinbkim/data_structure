#include <stdio.h>
#include <stdlib.h>

typedef	char	bt_data;

typedef	struct			s_bt_node
{
	bt_data				data;
	struct s_bt_node	*left;
	struct s_bt_node	*right;
}						t_bt_node;

typedef	void (*show_func)(int);  // function pointer



typedef	t_bt_node	*stack_data;

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



t_bt_node	*make_bt_node(bt_data data)
{
	t_bt_node	*new_node;
	
	new_node = (t_bt_node *)malloc(sizeof(t_bt_node));
	new_node->data = data;

	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}

void		make_left_sub_free(t_bt_node *parent, t_bt_node *child)
{
	if (parent->left)
		free(parent->left);
	parent->left = child;
}

void		make_right_sub_free(t_bt_node *parent, t_bt_node *child)
{
	if (parent->right)
		free(parent->right);
	parent->right = child;
}



void		show_data(int data)
{
	if (0 <= data && data <= 9)
		printf("%d ", data);
	else
		printf("%c ", data);
}

void		preorder_traverse(t_bt_node *node, show_func f)
{
	if (!node)
		return ;
	f(node->data);
	preorder_traverse(node->left, f);
	preorder_traverse(node->right, f);
}

void		inorder_traverse(t_bt_node *node, show_func f)
{
	if (!node)
		return ;
	inorder_traverse(node->left, f);
	f(node->data);
	inorder_traverse(node->right, f);
}

void		postorder_traverse(t_bt_node *node, show_func f)
{
	if (!node)
		return ;
	postorder_traverse(node->left, f);
	postorder_traverse(node->right, f);
	f(node->data);
}

void		delete_tree(t_bt_node *node)
{
	if (!node)
		return ;
	delete_tree(node->left);
	delete_tree(node->right);
	free(node);  // The root node should be deleted last
}



int			ft_strlen(char *s)
{
	int i;
	
	i = 0;
	while (s[i])
		i++;

	return (i);
}

int			ft_isdigit(char n)
{
	if ('0' <= n && n <= '9')
		return (1);
	return (0);
}

t_bt_node	*make_e_tree(char *exp)
{
	t_bt_node	*node;
	t_stack		stack;
	int			i;
	
	stack_init(&stack);
	
	i = -1;
	while (++i < ft_strlen(exp))
	{
		if (ft_isdigit(exp[i]))
			node = make_bt_node(exp[i] - '0');  // conversion for calculation
		
		// if operator, take two operands from stack
		// make them child nodes
		else
		{
			node = make_bt_node(exp[i]);
			make_right_sub_free(node, stack_pop(&stack));
			make_left_sub_free(node, stack_pop(&stack));
		}
		
		stack_push(&stack, node);
	}
	
	return (stack_pop(&stack));
}

int			cal_tree(t_bt_node *e_tree)
{
	int op1;
	int	op2;

	if (!e_tree->left && !e_tree->right)
		return (e_tree->data);

	op1 = cal_tree(e_tree->left);
	op2 = cal_tree(e_tree->right);
	
	if (e_tree->data == '+')
		return (op1 + op2);
	else if (e_tree->data == '-')
		return (op1 - op2);
	else if (e_tree->data == '*')
		return (op1 * op2);	
	else if (e_tree->data == '/')
		return (op1 / op2);
	else
		return (0);
}



// 332page. tree
int			main(void)
{
	t_bt_node	*e_tree;
	char		exp[] = "12+7*";
	
	e_tree = make_e_tree(exp);
	
	preorder_traverse(e_tree, show_data);
	printf("\n");
	inorder_traverse(e_tree, show_data);
	printf("\n");	
	postorder_traverse(e_tree, show_data);
	printf("\n");
	
	printf("result : %d\n", cal_tree(e_tree));
	
	delete_tree(e_tree);
}
