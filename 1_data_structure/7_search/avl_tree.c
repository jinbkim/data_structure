#include <stdio.h>
#include <stdlib.h>

typedef	int	bt_data;

typedef	struct			s_bt_node
{
	bt_data				data;
	struct s_bt_node	*left;
	struct s_bt_node	*right;
}						t_bt_node;



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

void		delete_tree(t_bt_node *node)
{
	if (!node)
		return ;
	delete_tree(node->left);
	delete_tree(node->right);
	free(node);  // The root node should be deleted last
}





void		bst_init(t_bt_node **root_node)
{
	*root_node = NULL;
}

int			get_height(t_bt_node *node)
{
	int	left_height;
	int	right_height;
	
	if (node == NULL)
		return (0);
	
	left_height = get_height(node->left);
	right_height = get_height(node->right);
	
	// return higher value
	if (left_height < right_height)
		return (right_height + 1);
	else
		return (left_height + 1);
}

int			get_height_diff(t_bt_node *root_node)
{
	if (!root_node)
		return (0);
	return (get_height(root_node->left) - get_height(root_node->right));	
} 

t_bt_node	*rotate_ll(t_bt_node *node)
{
	t_bt_node	*return_node;

	return_node = node->left;
	node->left = return_node->right;
	return_node->right = node;
	return (return_node);
}

t_bt_node	*rotate_rr(t_bt_node *node)
{
	t_bt_node	*return_node;

	return_node = node->right;
	node->right = return_node->left;
	return_node->left = node;
	return (return_node);
}

t_bt_node	*rotate_lr(t_bt_node *node)
{
	node->left = rotate_rr(node->left);
	node = rotate_ll(node);
	return (node);
}

t_bt_node	*rotate_rl(t_bt_node *node)
{
	node->right = rotate_ll(node->right);
	node = rotate_rr(node);
	return (node);
}

t_bt_node	*rebalance(t_bt_node **root_node)
{
	if (get_height_diff(*root_node) >= 2 && get_height_diff((*root_node)->left) > 0)
		*root_node = rotate_ll(*root_node);
	else if (get_height_diff(*root_node) >= 2 && get_height_diff((*root_node)->left) < 0)
		*root_node = rotate_lr(*root_node);
	else if (get_height_diff(*root_node) <= -2 && get_height_diff((*root_node)->right) > 0)
		*root_node = rotate_rl(*root_node);
	else if (get_height_diff(*root_node) <= -2 && get_height_diff((*root_node)->right) < 0)
		*root_node = rotate_rr(*root_node);
	return (*root_node);
}

void		bst_insert(t_bt_node **node, bt_data data)
{
	if (!*node)
		*node = make_bt_node(data);
	else if (data < (*node)->data)
	{
		bst_insert(&((*node)->left), data);
		*node = rebalance(node);
	}
	else if ((*node)->data < data)
	{
		bst_insert(&((*node)->right), data);
		*node = rebalance(node);
	}
}



// 493page. search
int			main(void)
{
	t_bt_node	*root_node;
	int			i;
	
	bst_init(&root_node);  // binary search tree reset
	
	i = 0;
	while (++i < 8)
		bst_insert(&root_node, i);
	
	printf("1 : %d\n", root_node->data);
	printf("2 : %d\n", root_node->left->data);
	printf("3 : %d\n", root_node->right->data);
	printf("4 : %d\n", root_node->left->left->data);
	printf("5 : %d\n", root_node->left->right->data);
	printf("6 : %d\n", root_node->right->left->data);
	printf("7 : %d\n", root_node->right->right->data);
	
	delete_tree(root_node);
}
