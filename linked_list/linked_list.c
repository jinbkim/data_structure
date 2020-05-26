#include <stdio.h>
#include <stdlib.h>



typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef	t_point	*list_data;

typedef int (*comp_func)(list_data, list_data);

int			func(list_data left, list_data right)
{
	if (left->x > right->x)
		return (1);
	else if (left->x == right->x && left->y >= right->y)
		return (1);
	return (0);
}



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



t_point		*make_point(int x, int y)
{
	t_point	*new_point;
	
	new_point = (t_point *)malloc(sizeof(t_point));
	new_point->x = x;
	new_point->y = y;
	return (new_point);
}

void		show_point(t_point *point)
{
	printf("<%d, %d>\n", point->x, point->y);
}



// 152page. linked list
int			main(void)
{
	t_list	list;
	t_point	*data;
	 
	list_init(&list);  // list reset
	
	list.f = func;  // compare function set
	
	data = make_point(1, 1);
	list_insert(&list, data);  // insert data to list
	data = make_point(1, 2);
	list_insert(&list, data);
	data = make_point(2, 2);
	list_insert(&list, data);
	data = make_point(2, 1);
	list_insert(&list, data);

	printf("number of data : %d\n", list.data_num);
	if (list_first_node(&list, &data)) // find first data in list
	{
		show_point(data);
		while (list_next_node(&list, &data))  // find next data in list
			show_point(data);
	}
	
	if (list_first_node(&list, &data)) // find first data in list
	{
		if (data->x == 2)
		{
			free(data);
			list_remove(&list);  // remove node
		}
		while (list_next_node(&list, &data))  // find next data in list
			if (data->x == 2)
			{
				free(data);
				list_remove(&list);  // remove node
			}
	}
	
	printf("\nnumber of data : %d\n", list.data_num);
	if (list_first_node(&list, &data)) // find first data in list
	{
		show_point(data);
		while (list_next_node(&list, &data))  // find next data in list
			show_point(data);
	}
	
	printf("\n----- data delete -----\n");
	if (list_first_node(&list, &data)) // find first data in list
	{
		free(data);
		list_remove(&list);  // remove node
		while (list_next_node(&list, &data))  // find next data in list
		{
			free(data);
			list_remove(&list);  // remove node
		}
	}
	free(list.head);
	printf("number of data : %d\n", list.data_num);;
}
