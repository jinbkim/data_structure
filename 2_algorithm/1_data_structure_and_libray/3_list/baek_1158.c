#include <stdio.h>
#include <stdlib.h>

typedef	int	list_data;

typedef struct		s_node
{
	list_data		data;
	struct s_node	*next;  // next node address
}					t_node;

typedef	struct	s_list
{
	t_node		*cur;  // current node of list
	t_node		*before;  // before node of list
	t_node		*tail;  // tail node of list
}				t_list;



void		list_insert(t_list *list, list_data data)
{	
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));  // make new node
	new_node->data = data;  // data of new node set
	if (!list->tail)
		new_node->next = new_node;  // new node points onself
	else
	{
		new_node->next = list->tail->next;  // new node points tail next
		list->tail->next = new_node;  // tail node points new node
	}
	list->tail = new_node;  // tail node points to new node
}

int			list_next_node(t_list *list)
{
	if (!list->tail)  // if tail node is NULL, return 0
		return (0);
	list->before = list->cur;  // before node points to current node
	list->cur = list->cur->next;  // current node move to next
	return (1);
}

list_data	list_remove(t_list *list)
{
	t_node		*remem_node;
	list_data	remem_data;

	remem_node = list->cur;  // remember node to be deleted
	remem_data = list->cur->data;  // remember data to be deleted
	if (remem_node == list->tail)
	{
		if (list->tail == list->tail->next)  // if remaining one node
			list->tail = NULL;
		else
			list->tail = list->before;
	}
	list->before->next = list->cur->next;  // connection before node and next node
	list->cur = list->before;  // current node reset
	free(remem_node);  // node delete
	return (remem_data);
}



int			main(void)
{
	t_list	list;  // circular linked list
	int 	n;
	int		k;
	int		i;
	int		data;

	scanf("%d %d", &n, &k);
	getchar();  // remove the enter in the buffer
	
	list.tail = NULL;  // list reset
	
	i = 0;
	while (++i <= n)
		list_insert(&list, i);  // insert data to list (1 ~ i)

	printf("<");
	list.cur = list.tail;  // tail : starting point
	while (list.tail)
	{
		i = -1;
		while (++i < k)
			list_next_node(&list);  // move k to the next

		data = list_remove(&list);  // remove data
		printf("%d", data);

		if (list.tail)  // if the node remains
			printf(", ");
	}
	printf(">\n");
}
