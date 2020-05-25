#include <stdio.h>
#include <stdlib.h>

typedef	int	list_data;

typedef int (*comp_func)(list_data, list_data);

typedef struct		s_node
{
	list_data		data;
	struct s_node	*next;  // next node address
}					t_node;

typedef struct		s_list
{
	t_node			*head;  // head node of list
	t_node			*cur;  // cuurent node of list
	t_node			*before;  // before node of list
	int				data_num;  // number of data 
	comp_func		f;  // compare function
}					t_list;



int			left_data_is_big(int left, int right)
{
	if (left >= right)  // if left data is bigger than right data, return 1
		return (1);
	return (0);
}

void		compare_insert(t_list *list, list_data data)
{
	t_node	*new_node;
	t_node	*cur;
	
	new_node = (t_node *)malloc(sizeof(t_node));  // make new node
	new_node->data = data;  // data set
	cur = list->head;  // current node points dummy node;
	while (cur->next && list->f(data, cur->next->data))  // find data location
		cur = cur->next;
	new_node->next = cur->next;  // position of new node set
	cur->next = new_node;  // position of new node set
	(list->data_num)++;  // number of data increase
}

void		just_insert(t_list *list, list_data data)
{
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));  // make new node
	new_node->data = data;  // data of new node set
	new_node->next = list->head->next;  // position of new node set
	list->head->next = new_node;  // head node points to new node
	(list->data_num)++;  // number of data increase
}

void		list_insert(t_list *list, list_data data)
{
	if (list->f)
		compare_insert(list, data);
	else
		just_insert(list, data);
}

void		list_init(t_list *list)
{
	list->head = (t_node *)malloc(sizeof(t_node));  // make dummy node
	list->head->next = NULL;  // first node reset
	list->data_num = 0;  // number of data reset
	list->f = NULL;  // comparison function of data reset
}

int			list_first_node(t_list *list, list_data *data)
{
	if (!list->head->next)  // if first node is NULL, return 0
		return (0);
	list->before = list->head;  // before node points to head node
	list->cur = list->head->next;  // current node points to head node next
	*data = list->cur->data;  // store first data in variable(data)
	return (1);
}

int			list_next_node(t_list *list, list_data *data)
{
	if (!list->cur->next)  // if next node is NULL, return 0
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
	 
	list_init(&list);  // list reset
	
	list.f = left_data_is_big;  // compare function set

	list_insert(&list, 1);  // insert data to list
	list_insert(&list, 1);
	list_insert(&list, 2);
	list_insert(&list, 2);
	list_insert(&list, 3);
	list_insert(&list, 3);

	printf("number of data : %d\n", list.data_num);
	if (list_first_node(&list, &data)) // find first data in list
	{
		printf("%d ", data);
		while (list_next_node(&list, &data))  // find next data in list
			printf("%d ", data);
	}
	printf("\n\n");
	
	if (list_first_node(&list, &data)) // find first data in list
	{
		if (data == 2)
			list_remove(&list);  // remove node
		while (list_next_node(&list, &data))  // find next data in list
			if (data == 2)
				list_remove(&list);  // remove node
	}
	
	printf("number of data : %d\n", list.data_num);
	if (list_first_node(&list, &data)) // find first data in list
	{
		printf("%d ", data);
		while (list_next_node(&list, &data))  // find next data in list
			printf("%d ", data);
	}
	printf("\n\n");
	
	if (list_first_node(&list, &data)) // find first data in list
	{
		list_remove(&list);  // remove node
		while (list_next_node(&list, &data))  // find next data in list
			list_remove(&list);  // remove node
	}
	free(list.head);
	printf("number of data : %d\n", list.data_num);;
}
