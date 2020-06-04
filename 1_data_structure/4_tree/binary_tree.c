#include <stdio.h>
#include <stdlib.h>

typedef	void (*show_func)(int);  // function pointer

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

void		set_sub_tree(t_bt_node *parent, t_bt_node *left, t_bt_node *right)
{
	if (parent->left)
		free(parent->left);
	if (parent->right)
		free(parent->right);
	parent->left = left;
	parent->right = right;
}

t_bt_node	*get_left_sub_tree(t_bt_node *node)
{
	return (node->left);
}

t_bt_node	*get_right_sub_tree(t_bt_node *node)
{
	return (node->right);
}

bt_data		get_data(t_bt_node *node)
{
	return (node->data);
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



void		show_data(int data)
{
	printf("%d ", data);
}



// 317page. tree
int			main(void)
{
	t_bt_node	*node1;
	t_bt_node	*node2;
	t_bt_node	*node3;
	t_bt_node	*node4;
	t_bt_node	*node5;
	t_bt_node	*node6;
	
	node1 = make_bt_node(1);  // make binary tree node
	node2 = make_bt_node(2);
	node3 = make_bt_node(3);
	node4 = make_bt_node(4);
	node5 = make_bt_node(5);
	node6 = make_bt_node(6);
	
	set_sub_tree(node1, node2, node3);  // setting sub tree
	set_sub_tree(node2, node4, node5);
	set_sub_tree(node3, NULL, node6);
	
	preorder_traverse(node1, show_data);  // tree traverse
	printf("\n");
	inorder_traverse(node1, show_data);
	printf("\n");	
	postorder_traverse(node1, show_data);
	printf("\n");
	
	delete_tree(node1);
}
