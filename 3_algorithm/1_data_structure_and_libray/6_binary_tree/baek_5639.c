#include <stdio.h>
#include <stdlib.h>

typedef	int	bt_data;

typedef	struct			s_bt_node
{
	bt_data				data;
	struct s_bt_node	*left;  // left child node
	struct s_bt_node	*right;  // right child node
}						t_bt_node;

typedef	void (*show_func)(int);  // function pointer



t_bt_node	*make_bt_node(bt_data data)
{
	t_bt_node	*new_node;
	
	new_node = (t_bt_node *)malloc(sizeof(t_bt_node));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int			comp_func(bt_data a, bt_data b)
{
	// designed to return positive value when a has higher priority
	return (b - a);
}

t_bt_node	*bst_insert(t_bt_node *node, bt_data data)
{
	if (node == NULL)
		node = make_bt_node(data);
	else if (comp_func(data, node->data) == 0)
		exit(1);  // do not allow duplicate data
	else if (comp_func(data, node->data) > 0)
		node->left = bst_insert(node->left, data);
	else if (comp_func(data, node->data) < 0)
		node->right = bst_insert(node->right, data);

	return (node);
}



void		show_data(int data)
{
		printf("%d\n", data);
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



int			main(void)
{
	t_bt_node	*bst_root;
	int			data;

	bst_root = NULL;  // binary search tree reset
	
	while (scanf("%d", &data) != EOF)
		bst_root = bst_insert(bst_root, data);
	
	postorder_traverse(bst_root, show_data);
	delete_tree(bst_root);
}
