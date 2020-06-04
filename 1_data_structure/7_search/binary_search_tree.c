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



void		bst_init(t_bt_node **root_node)
{
	*root_node = NULL;
}

bt_data		get_data(t_bt_node *node)
{
	return (node->data);
}

t_bt_node	*get_left_sub_tree(t_bt_node *node)
{
	return (node->left);
}

t_bt_node	*get_right_sub_tree(t_bt_node *node)
{
	return (node->right);
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

void		delete_tree(t_bt_node *node)
{
	if (!node)
		return ;
	delete_tree(node->left);
	delete_tree(node->right);
	free(node);  // The root node should be deleted last
}



void		bst_insert(t_bt_node **root_node, bt_data data)
{
	t_bt_node	*parent_node;
	t_bt_node	*current_node;
	t_bt_node	*new_node;
	
	parent_node = NULL;
	current_node = *root_node;
	new_node = NULL;
	
	// find the location where the new_node will be added
	while (current_node)
	{
		if (get_data(current_node) == data)  // data duplication is not allowed.
			return ;
		parent_node = current_node;
		if (get_data(current_node) < data)
			current_node = get_right_sub_tree(current_node);
		else
			current_node = get_left_sub_tree(current_node);
	}
	
	new_node = make_bt_node(data);
	if (parent_node == NULL) // if new_node is root_node
		*root_node = new_node;
	else
	{
		if (get_data(parent_node) < data)
			set_sub_tree(parent_node, NULL, new_node);
		else
			set_sub_tree(parent_node, new_node, NULL);
	}
	
}

t_bt_node	*bst_search(t_bt_node *node, bt_data data)
{
	while (node)
	{
		if (get_data(node) == data)
			return (node);
		else if (get_data(node) < data)
			node = get_right_sub_tree(node);
		else
			node = get_left_sub_tree(node);
	}
	return (NULL);
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

void		show_data(int data)
{
	if (0 <= data && data <= 9)
		printf("%d ", data);
	else
		printf("%c ", data);
}

void		bst_show(t_bt_node *root_node)
{
	inorder_traverse(root_node, show_data);
}

t_bt_node	*bst_remove(t_bt_node **root_node, bt_data data)
{
	t_bt_node	*virtual_root_node;
	t_bt_node	*parent_node;
	t_bt_node	*current_node;
	t_bt_node	*delete_node;
	
	virtual_root_node = make_bt_node(0);
	parent_node = virtual_root_node;
	current_node = *root_node;
	// set root node to the right child node of virtual root node
	virtual_root_node->right = *root_node;
	
	// search node to be deleted
	while (current_node && get_data(current_node) != data)
	{
		parent_node = current_node;
		if (get_data(current_node) < data)
			current_node = get_right_sub_tree(current_node);
		else
			current_node = get_left_sub_tree(current_node);
	}
	
	if (current_node == NULL)
		return (NULL);
	delete_node = current_node;

	// if the node to be deleted is terminal node
	if (!get_right_sub_tree(delete_node) && !get_left_sub_tree(delete_node))
	{
		if (get_left_sub_tree(parent_node) == delete_node)
			parent_node->left = NULL;
		else
			parent_node->right = NULL;
	}
	
	// if the node to be deleted has one child node 
	else if (!(get_right_sub_tree(delete_node) && get_left_sub_tree(delete_node)))
	{
		t_bt_node	*child_node;
		
		// child_node points to the child node of delete_node
		if (get_left_sub_tree(delete_node))
			child_node = get_left_sub_tree(delete_node);
		else
			child_node = get_right_sub_tree(delete_node);
		
		// connect parrent_node and child_node (delete_node)
		if (get_left_sub_tree(parent_node) == delete_node)
			parent_node->left = child_node;
		else if (get_right_sub_tree(parent_node) == delete_node)
			parent_node->right = child_node;
	}
	
	// if the node to be deleted has two child node 
	else
	{
		t_bt_node	*replace_node;
		t_bt_node	*replace_parent_node;
		bt_data		delete_data;
		
		replace_node = get_right_sub_tree(delete_node);
		replace_parent_node = delete_node;
		
		// find the node to be replaced
		while (get_left_sub_tree(replace_node))
		{
			replace_parent_node = replace_node;
			replace_node = get_left_sub_tree(replace_node);
		}
		
		delete_data = delete_node->data;
		delete_node->data = replace_node->data;
		
		// if the replacement node is the left child node
		if (get_left_sub_tree(replace_parent_node) == replace_node)
			replace_parent_node->left = replace_node->right;
		// if the replacement node is the right child node
		else
			replace_parent_node->right = replace_node->right;
		
		delete_node = replace_node;
		delete_node->data = delete_data;  // data restoration
	}
	
	// if the deleted node is root node
	if (get_right_sub_tree(virtual_root_node) != *root_node)
		*root_node = get_right_sub_tree(virtual_root_node);
	free(virtual_root_node);
	return (delete_node);
}



// 465page. search
int			main(void)
{
	t_bt_node	*bst_root_node;
	t_bt_node	*search_node;

	bst_init(&bst_root_node);  // binary search tree reset

	bst_insert(&bst_root_node, 5);  // insert data to binary search tree
	bst_insert(&bst_root_node, 8);
	bst_insert(&bst_root_node, 1);
	bst_insert(&bst_root_node, 6);
	bst_insert(&bst_root_node, 4);
	bst_insert(&bst_root_node, 9);
	bst_insert(&bst_root_node, 3);
	bst_insert(&bst_root_node, 2);
	bst_insert(&bst_root_node, 7);
	
	bst_show(bst_root_node);
	printf("\n");
	
	search_node = bst_remove(&bst_root_node, 3);
	free(search_node);
	bst_show(bst_root_node);
	printf("\n");
	
	search_node = bst_remove(&bst_root_node, 8);
	free(search_node);
	bst_show(bst_root_node);
	printf("\n");
	
	search_node = bst_remove(&bst_root_node, 1);
	free(search_node);
	bst_show(bst_root_node);
	printf("\n");
	
	search_node = bst_remove(&bst_root_node, 6);
	free(search_node);
	bst_show(bst_root_node);
	printf("\n");

	delete_tree(bst_root_node);	
} 
