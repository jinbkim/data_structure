#include <stdio.h>
#include <stdlib.h>

typedef	int	list_data;

typedef struct		s_node
{
	list_data		data;
	struct s_node	*next;  // next node address
	struct s_node	*before;  // before node address
}					t_node;

typedef	struct	s_list
{
	t_node		*head;  // head node of list
	t_node		*cur;  // current node of list
	t_node		*tail;  // tail node of list
	int			data_num;  // number of data
}				t_list;



void		list_init(t_list *list)
{
	list->head = (t_node *)malloc(sizeof(t_node));  // make dummy node
	list->head->next = NULL;
	list->data_num = 0;
}

void		list_insert(t_list *list, list_data data)
{	
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	// insert node
	new_node->next = list->head->next;
	if (list->head->next)  // if node is exist
		list->head->next->before = new_node;
	new_node->before = list->head;
	list->head->next = new_node;
	(list->data_num)++;
}

int			list_first_node(t_list *list, list_data *data)
{
	if (!list->head->next)  // if node is not exist
		return (0);
	list->cur = list->head->next;
	*data = list->cur->data;
	return (1);	
}

int			list_next_node(t_list *list, list_data *data)
{
	if (!list->cur->next)  // if next node is not exist
		return (0);
	list->cur = list->cur->next;
	*data = list->cur->data;
	return (1);
}

int			list_before_node(t_list *list, list_data *data)
{
	if (list->cur->before == list->head)  // if before node is head node
		return (0);
	list->cur = list->cur->before;
	*data = list->cur->data;
	return (1);
}

list_data	list_remove(t_list *list)
{
	t_node		*remem_node;
	list_data	remem_data;

	remem_node = list->cur;  // remember node to be deleted
	remem_data = list->cur->data;  // remember data to be deleted
	
	// connection before node and next noe
	list->cur->before->next = list->cur->next;
	if (list->cur->next)  // if next node exist,
		list->cur->next->before = list->cur->before;
	else
		list->cur->next = NULL;
	
	// current node reset
	if (list->cur->before != list->head)  // if before node is not head node,
		list->cur = list->cur->before;
	else if (list->cur->next)  // if next node is exist,
		list->cur = list->cur->next;
	
	free(remem_node);
	(list->data_num)--;
	return (remem_data);
}



void		list_insert_tail(t_list *list, list_data data)
{	
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	// insert node
	new_node->next = NULL;
	if (!list->head->next)  // if node is not exist, 
	{
		new_node->before = list->head;
		list->head->next = new_node;
	}
	else  // if node is exist,
	{
		new_node->before = list->tail;
		list->tail->next = new_node;
	}
	list->tail = new_node;
	(list->data_num)++;  // number of data increas
}



// 191page. linked list
int			main(void)
{
	t_list	list;
	int		data;
	int		i;
	
	list_init(&list);  // list reset
	
	i = 0;
	while (++i < 10)
		list_insert_tail(&list, i);  // insert data to list
	
	printf("number of data : %d\n", list.data_num);
	if (list_first_node(&list, &data))  // find first data in list
	{
		printf("%d ", data);
		while (list_next_node(&list, &data))  // find next data in list
			printf("%d ", data);
		while (list_before_node(&list, &data))  // find before data in list
			printf("%d ", data);
	}
	
	printf("\n\n----- even number data delete -----\n");
	if (list_first_node(&list, &data))
	{
		if (data %2 == 0)
			list_remove(&list);  // remove node
		while (list_next_node(&list, &data))
			if (data %2 == 0)
				list_remove(&list);
	}
	
	printf("number of data : %d\n", list.data_num);
	if (list_first_node(&list, &data))
	{
		printf("%d ", data);
		while (list_next_node(&list, &data))
			printf("%d ", data);
	}

	printf("\n\n----- data delete -----\n");
	if (list_first_node(&list, &data))
	{
		list_remove(&list);
		while (list_next_node(&list, &data))
			list_remove(&list); 
		list_remove(&list);
	}
	free(list.head);
	printf("number of data : %d\n", list.data_num);
}
