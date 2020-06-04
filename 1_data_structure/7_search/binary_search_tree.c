#include <stdio.h>
#include <stdlib.h>

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



// 444page. search
int			main(void)
{
	t_bt_node	*bst_root_node;
	t_bt_node	*search_node;
	
	bst_init(&bst_root_node);  // binary search tree reset
	
	bst_insert(&bst_root_node, 9);  // insert data to binary search tree
	bst_insert(&bst_root_node, 1);
	bst_insert(&bst_root_node, 6);
	bst_insert(&bst_root_node, 2);
	bst_insert(&bst_root_node, 8);
	bst_insert(&bst_root_node, 3);
	bst_insert(&bst_root_node, 5);
	
	search_node = bst_search(bst_root_node, 1);
	if (search_node)
		printf("found %d!\n", get_data(search_node));
	else
		printf("search fail!\n");
	
	search_node = bst_search(bst_root_node, 4);
	if (search_node)
		printf("found %d!\n", get_data(search_node));
	else
		printf("search fail!\n");

	search_node = bst_search(bst_root_node, 6);
	if (search_node)
		printf("found %d!\n", get_data(search_node));
	else
		printf("search fail!\n");
	
	search_node = bst_search(bst_root_node, 7);
	if (search_node)
		printf("found %d!\n", get_data(search_node));
	else
		printf("search fail!\n");
	
	delete_tree(bst_root_node);
} 
