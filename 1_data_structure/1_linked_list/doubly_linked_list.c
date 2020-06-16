#include <stdio.h>
#include <stdlib.h>

typedef	int	list_data;

typedef struct		s_node
{
	list_data		data;
	struct s_node	*before;
	struct s_node	*next;
}					t_node;

typedef struct		s_list
{
	t_node			*head;
	t_node			*cur;
	t_node			*tail;
}					t_list;



void		list_init(t_list *list)
{
	list->head = (t_node *)malloc(sizeof(t_node));  // make dummy node
	list->head->next = NULL;
	list->tail = list->head;
}

void		list_insert_tail(t_list *list, list_data data)
{	
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	new_node->next = NULL;
	new_node->before = list->tail;
	list->tail->next = new_node;
	list->tail = new_node;  // tail node reset
}

void		list_insert_head(t_list *list, list_data data)
{	
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	new_node->next = list->head->next;
	new_node->before = list->head;
	if (list->head->next)
		list->head->next->before = new_node;
	else  // there is no node
		list->tail = new_node;
	list->head->next = new_node;
}

int			list_next_node(t_list *list, list_data *data)
{
	if (list->cur->next == NULL)
		return (0);
	list->cur = list->cur->next;
	*data = list->cur->data;
	return (1);
}

list_data	list_remove(t_list *list)
{
	t_node		*remem_node;
	list_data	remem_data;

	remem_node = list->cur;  // remember node to be deleted
	remem_data = list->cur->data;  // remember data to be deleted
	
	// connection before node and next node
	list->cur->before->next = list->cur->next;
	if (list->cur->next)  // if current node is not tail
		list->cur->next->before = list->cur->before;

	list->cur = list->cur->before;  // current node reset
	
	free(remem_node);
	return (remem_data);
}



// 191page. linked list
int			main(void)
{
	t_list	list;
	int		data;
	int		i;
	
	list_init(&list);  // list reset
	
	i = 0;
	while (++i < 6)
		list_insert_head(&list, i);  // insert data to tail
	i = 0;
	while (++i < 6)
		list_insert_tail(&list, i);
	
	// show all data
	list.cur = list.head;  /// head : starting point
	while (list_next_node(&list, &data))
		printf("%d ", data);
	printf("\n");
		
	printf("----- even number data delete -----\n");
	list.cur = list.head;
	while (list_next_node(&list, &data))
		if (data % 2 == 0)
			list_remove(&list);
	
	// show all data
	list.cur = list.head;  /// head : starting point
	while (list_next_node(&list, &data))
		printf("%d ", data);
	printf("\n");
		
	// delete all data	
	list.cur = list.head;
	while (list_next_node(&list, &data))
		list_remove(&list);	
		
	free(list.head);
}
