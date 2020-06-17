#include <stdio.h>
#include <stdlib.h>



typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef	t_point	*list_data;



typedef struct		s_node
{
	list_data		data;
	struct s_node	*before;
	struct s_node	*next;
}					t_node;

typedef int (*comp_func)(list_data, list_data);

typedef struct		s_list
{
	t_node			*head;
	t_node			*cur;
	comp_func		f;
}					t_list;



int			func1(list_data d1, list_data d2)
{
	if (d1->x != d2->x)
		return (d2->x - d1->x);
	else
		return (d2->y - d1->y);
}

void		list_init(t_list *list, comp_func f)
{
	list->head = (t_node *)malloc(sizeof(t_node));  // make dummy node
	list->head->next = NULL;
	list->f = f;
}

void		list_insert_comp(t_list *list, list_data data)
{	
	t_node	*new_node;
	t_node	*cur;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	// find position
	cur = list->head;  // head : starting point
	// repeat when priority of data is lower then next node
	while (cur->next && list->f(data, cur->next->data) < 0)
		cur = cur->next;

	// connection
	new_node->next = cur->next;
	if (cur->next)  // if cur is not tail
		cur->next->before = new_node;
	new_node->before = cur;
	cur->next = new_node;
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

int			list_next_node(t_list *list, list_data *data)
{
	if (list->cur->next == NULL)
		return (0);
	list->cur = list->cur->next;
	*data = list->cur->data;
	return (1);
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
	
	list_init(&list, func1);  // list reset
	
	data = make_point(2, 2);
	list_insert_comp(&list, data);  // insert data to list
	data = make_point(2, 1);
	list_insert_comp(&list, data);
	data = make_point(1, 2);
	list_insert_comp(&list, data);
	data = make_point(1, 1);
	list_insert_comp(&list, data);
	
	// show all data
	list.cur = list.head;  // head : starting point
	while ((list_next_node(&list, &data)))
		show_point(data);

	// delete one data
	list.cur = list.head;
	while (list_next_node(&list, &data))
	{
		if (list.cur->data->x == 2)
		{
			free(list.cur->data);
			list_remove(&list);
		}
	}
	
	// show all data
	printf("----- x:2 delete -----\n");
	list.cur = list.head;  // head : starting point
	while (list_next_node(&list, &data))
		show_point(data);
	
	// delete all data
	list.cur = list.head;
	while (list_next_node(&list, &data))
	{
		free(list.cur->data);
		list_remove(&list);
	}
	
	free(list.head);
}
