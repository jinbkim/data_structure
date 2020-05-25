#include <stdio.h>
#include <stdlib.h>

typedef	int list_data;

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
	int			data_num;  // number of data
}				t_list;



void		list_init(t_list *list)
{
	list->tail = NULL;  // tail node reset
	//list->cur = NULL;
	//list->before = NULL;
	list->data_num = 0;  // number of data reset
}

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
	(list->data_num)++;  // number of data increas
}

void		list_insert_front(t_list *list, list_data data)
{	
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));  // make new node
	new_node->data = data;  // data of new node set
	if (!list->tail)
		list->tail = new_node;  // tail node points to new node
	else
		new_node->next = list->tail->next;  // new node points tail next
	list->tail->next = new_node;  // tail node points new node
	(list->data_num)++;  // number of data increas
}

int			list_first_node(t_list *list, list_data *data)
{
	if (!list->tail)  // if tail node is NULL, return 0
		return (0);
	list->before = list->tail;  // before node points to tail node
	list->cur = list->tail->next;  // current node points to tail node next
	*data = list->cur->data;  // store first data in variable(data)
	return (1);
}

int			list_next_node(t_list *list, list_data *data)
{
	if (!list->tail)  // if tail node is NULL, return 0
		return (0);
	list->before = list->cur;  // before node points to current node
	list->cur = list->cur->next;  // current node move to next
	*data = list->cur->data;  // store first data in variable(data)
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
	(list->data_num)--;  // number of data decrease
	return (remem_data);
}



int			main(void)
{
	t_list	list;
	int		data;
	int		i;
	
	list_init(&list);
	
	list_insert(&list, 3);  // insert data to list
	list_insert(&list, 4);
	list_insert(&list, 5);
	list_insert_front(&list, 2);  // insert data to list front
	list_insert_front(&list, 1);
	
	printf("number of data : %d\n", list.data_num);
	if (list_first_node(&list, &data)) // find first data in list
	{
		printf("%d ", data);
		i = -1;
		while (++i < 3 * list.data_num - 1)
			if (list_next_node(&list, &data))  // find next data in list
				printf("%d ", data);
	}
	list_first_node(&list, &data); // find first data in list
		if (data % 2 == 0)
			list_remove(&list);  // remove node
	i = -1;
	while (++i < list.data_num - 1)
	{
		list_next_node(&list, &data);
		if (data % 2 == 0)
			list_remove(&list);  // remove node
	}
/*	
	if (list_first_node(&list, &data)) // find first data in list
	{
		if (data % 2 == 0)
			list_remove(&list);  // remove node
		i = -1;
		while (++i < list.data_num - 1)
			if (list_next_node(&list, &data) && data % 2 == 0)
				list_remove(&list);  // remove node
	}
*/	
	printf("\n\nnumber of data : %d\n", list.data_num);
	if (list_first_node(&list, &data)) // find first data in list
	{
		printf("%d ", data);
		i = -1;
		while (++i < list.data_num - 1)
			if (list_next_node(&list, &data))  // find next data in list
				printf("%d ", data);
	}
	
	if (list_first_node(&list, &data)) // find first data in list
	{
		list_remove(&list);
		i = -1;
		while (++i < list.data_num - 1)
			if (list_next_node(&list, &data))  // find next data in list
				list_remove(&list);
	}
}
