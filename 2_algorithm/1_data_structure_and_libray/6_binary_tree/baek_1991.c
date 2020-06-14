#include <stdio.h>
#include <stdlib.h>

typedef	char	bt_data;

typedef	struct			s_bt_node
{
	bt_data				data;
	struct s_bt_node	*left;  // left child node
	struct s_bt_node	*right;  // right child node
}						t_bt_node;

typedef	void (*show_func)(char);  // function pointer



t_bt_node	*make_bt_node(bt_data data)
{
	t_bt_node	*new_node;
	
	new_node = (t_bt_node *)malloc(sizeof(t_bt_node));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void		set_sub_tree(t_bt_node **node, char n1, char n2, char n3)
{
	if (n2 != '.')
		node[n1 - 'A']->left = node[n2 - 'A'];
	if (n3 != '.')
		node[n1 - 'A']->right = node[n3 - 'A'];
}

t_bt_node	**tree_input(int size)
{
	t_bt_node	**bst_root;
	char		node[3];
	int			i;
	
	bst_root = (t_bt_node **)malloc(sizeof(t_bt_node *) * size);
	i = -1;
	while (++i < size)
		bst_root[i] = make_bt_node(i + 'A');
	
	i = -1;
	while (++i < size)
	{
		scanf("%c %c %c", &node[0], &node[1], &node[2]);
		getchar();
		set_sub_tree(bst_root, node[0], node[1], node[2]);
	}
	
	return (bst_root);
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

void		show_data(char data)
{
		printf("%c", data);
}

void		show_tree(t_bt_node *root)
{
	preorder_traverse(root, show_data);
	printf("\n");
	inorder_traverse(root, show_data);
	printf("\n");
	postorder_traverse(root, show_data);
	printf("\n");
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
	t_bt_node	**bst_root;
	int			size;
	
	scanf("%d", &size);
	getchar();
	
	bst_root = tree_input(size);
	show_tree(bst_root[0]);
	
	delete_tree(bst_root[0]);
	free(bst_root);
}
