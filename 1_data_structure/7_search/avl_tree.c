#include <stdio.h>
#include <stdlib.h>

typedef	int	bt_data;

typedef	struct			s_bt_node
{
	bt_data				data;
	struct s_bt_node	*left;  // left child node
	struct s_bt_node	*right;  // right child node
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

void		delete_tree(t_bt_node *node)
{
	if (!node)
		return ;
	delete_tree(node->left);
	delete_tree(node->right);
	free(node);  // The root node should be deleted last
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
	node->right = rotate_rr(node->right);
	node = rotate_ll(node);
	return (node);
}

t_bt_node	*rotate_rl(t_bt_node *node)
{
	node->left = rotate_ll(node->left);
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

void		bst_insert(t_bt_node **root_node, bt_data data)
{
	if (!*root_node)
		*root_node = make_bt_node(data);
	else if (data < (*root_node)->data)
	{
		bst_insert(&((*root_node)->left), data);
		*root_node = rebalance(root_node);
	}
	else if ((*root_node)->data < data)
	{
		bst_insert(&((*root_node)->right), data);
		*root_node = rebalance(root_node);
	}
}



// 493page. search
int			main(void)
{
	t_bt_node	*avl_root_node;
	t_bt_node	*n;

	avl_root_node = NULL;  // avl tree reset
	
	bst_insert(&avl_root_node, 1);  // insert data to binary search tree
	bst_insert(&avl_root_node, 2);
	bst_insert(&avl_root_node, 3);
	bst_insert(&avl_root_node, 4);
	bst_insert(&avl_root_node, 5);
	bst_insert(&avl_root_node, 6);
	bst_insert(&avl_root_node, 7);
	
	n = avl_root_node;
	
	printf("1 : %d\n", n->data);
	printf("2 : %d\n", n->left->data);
	printf("3 : %d\n", n->right->data);
	printf("4 : %d\n", n->left->left->data);
	printf("5 : %d\n", n->left->right->data);
	printf("6 : %d\n", n->right->left->data);
	printf("7 : %d\n", n->right->right->data);
	
	delete_tree(avl_root_node);
}
