#include <stdio.h>
#include <stdlib.h>

#define	NODE_MAX	9

typedef	int	bt_data;

typedef	struct			s_bt_node
{
	bt_data				data;
	struct s_bt_node	*left;
	struct s_bt_node	*right;
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
	printf("%d ", data);
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



void		bst_init(t_bt_node **root_node)
{
	*root_node = NULL;
}

void		bst_insert(t_bt_node **root_node, bt_data data)
{
	t_bt_node	*current_node;
	t_bt_node	*parent_node;
	t_bt_node	*new_node;

	// find the location where the new_node will be added
	current_node = *root_node;
	parent_node = NULL;
	while (current_node)
	{
		// data duplication is not allowed
		if (data == current_node->data) 
			return ;
		parent_node = current_node;

		if (data < current_node->data)
			current_node = current_node->left;
		else
			current_node = current_node->right;
	}

	new_node = make_bt_node(data);
	
	if (parent_node)
	{
		if (data < parent_node->data)
			make_left_sub_free(parent_node, new_node);
		else
			make_right_sub_free(parent_node, new_node);
	}
	else
		*root_node = new_node;
}

t_bt_node	*bst_remove(t_bt_node **root_node, bt_data data)
{
	t_bt_node	*vr_node;  // virtual node made for when root node is removed
	t_bt_node	*current_node;
	t_bt_node	*parent_node;
	
	vr_node = make_bt_node(0);
	current_node = *root_node;
	parent_node = vr_node;
	
	vr_node->right = *root_node;
	
	// search node to be deleted
	while(current_node && current_node->data != data)
	{
		parent_node = current_node;
		
		if (data < current_node->data)
			current_node = current_node->left;
		else
			current_node = current_node->right;
	}
	
	if (!current_node)
		return (NULL);
	
	// if the node to be deleted is terminal node
	if (!current_node->left && !current_node->right)
	{
		if (parent_node->left == current_node)
			parent_node->left = NULL;
		else
			parent_node->right = NULL;
	}
	
	// if the node to be deleted has one child node 
	else if(!(current_node->left && current_node->right))
	{
		t_bt_node	*child_node;
		
		if (current_node->left)
			child_node = current_node->left;
		else
			child_node = current_node->right;
		
		if (parent_node->left == current_node)
			parent_node->left = child_node;
		else
			parent_node->right = child_node;
	}
	
	// if the node to be deleted has two child node 
	else
	{
		t_bt_node	*replace_parent_node;
		t_bt_node	*replace_node;
		bt_data		remem_data;
		
		replace_parent_node = current_node;
		replace_node = current_node->right;
		
		while (replace_node->left)
		{
			replace_parent_node = replace_node;
			replace_node = replace_node->left;
		}
		
		remem_data = current_node->data;  // remember data to removed
		current_node->data = replace_node->data;  // replace data
		
		// if the replacement node is the left child node
		if (replace_parent_node->left == replace_node)
			replace_parent_node->left = replace_node->right;
		// if the replacement node is the right child node
		else
			replace_parent_node->right = replace_node->right;
		
		current_node = replace_node;
		current_node->data = remem_data;  // data restoration
	}
	
	// if the deleted node is root node
	if (vr_node->right != *root_node)
		*root_node = vr_node->right;
	
	free(vr_node);
	return (current_node);
}



// 465page. search
int			main(void)
{
	t_bt_node	*root_node;
	t_bt_node	*node;
	
	bst_init(&root_node);  // binary search tree reset
	
	bst_insert(&root_node, 5);
	bst_insert(&root_node, 8);
	bst_insert(&root_node, 1);
	bst_insert(&root_node, 6);
	bst_insert(&root_node, 4);
	bst_insert(&root_node, 9);
	bst_insert(&root_node, 3);
	bst_insert(&root_node, 2);
	bst_insert(&root_node, 7);
	
	inorder_traverse(root_node, show_data);
	printf("\n");

	node = bst_remove(&root_node, 3);
	free(node);
	inorder_traverse(root_node, show_data);
	printf("\n");
	
	node = bst_remove(&root_node, 8);
	free(node);
	inorder_traverse(root_node, show_data);
	printf("\n");
	
	delete_tree(root_node);
}
