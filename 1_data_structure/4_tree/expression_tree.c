#include <stdio.h>
#include <stdlib.h>



typedef	void (*show_func)(int);  // function pointer



typedef	char	bt_data;

typedef	struct			s_bt_node
{
	bt_data				data;
	struct s_bt_node	*left;  // left child node
	struct s_bt_node	*right;  // right child node
}						t_bt_node;



typedef	t_bt_node	*stack_data;

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

void		stack_push(t_stack *stack, stack_data data)
{
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	new_node->next = stack->head;
	stack->head = new_node;
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

void		set_sub_tree(t_bt_node *parent, t_bt_node *left, t_bt_node *right)
{
	if (parent->left)
		free(parent->left);
	if (parent->right)
		free(parent->right);
	
	parent->left = left;
	parent->right = right;
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

t_bt_node	*get_left_sub_tree(t_bt_node *node)
{
	if (node)
		return (node->left);
	return (NULL);
}

t_bt_node	*get_right_sub_tree(t_bt_node *node)
{
	if (node)
		return (node->right);
	return (NULL);
}

bt_data		get_data(t_bt_node *node)
{
	if (node)
		return (node->data);
	return (0);
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

t_bt_node	*make_e_tree(char *express)
{
	t_stack		stack;
	t_bt_node	*node;
	int			i;
	
	stack_init(&stack);
	
	i = -1;
	while (++i < ft_strlen(express))  // repeat by express size
	{
		if (ft_isdigit(express[i]))
			node = make_bt_node(express[i] - '0');  // conversion for calculation
		else
		{
			node = make_bt_node(express[i]);
			set_sub_tree(node, stack_pop(&stack), stack_pop(&stack));  // function call right -> left
		}
		stack_push(&stack, node);
	}
	
	return (stack_pop(&stack));  // return root node
}

void		show_data(int data)
{
	if (0 <= data && data <= 9)
		printf("%d ", data);
	else
		printf("%c ", data);
}

int			calculation_tree(t_bt_node *e_tree)
{
	char	oper;
	int		op1;
	int 	op2;
	
	if (!get_left_sub_tree(e_tree) && !get_right_sub_tree(e_tree))  // if terminal node 
		return (get_data(e_tree));
	
	op1 = calculation_tree(get_left_sub_tree(e_tree));  // left child node operand
	op2 = calculation_tree(get_right_sub_tree(e_tree));  // right child node operand
	oper = get_data(e_tree);  // current node operator
	
	if (oper == '+')
		return (op1 + op2);
	else if (oper == '-')
		return (op1 - op2);
	else if (oper == '*')
		return (op1 * op2);
	else if (oper == '/')
		return (op1 / op2);
	return (0);
}



// 332page. tree
int			main(void)
{
	char		express[] = "12+7*";
	t_bt_node	*e_tree;
	
	e_tree = make_e_tree(express);  // make expression tree
	
	preorder_traverse(e_tree, show_data);  // tree traverse
	printf("\n");
	inorder_traverse(e_tree, show_data);
	printf("\n");	
	postorder_traverse(e_tree, show_data);
	printf("\n");
	
	printf("result : %d\n", calculation_tree(e_tree));  // calculation result 
	
	delete_tree(e_tree);
}
