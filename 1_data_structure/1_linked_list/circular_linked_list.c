#include <stdio.h>
#include <stdlib.h>



typedef	struct	s_info
{
	int			live_num;
	char		name[32];
}				t_info;

typedef	t_info	*list_data;



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



char		*ft_strcpy(char *s1, char *s2)
{
	int i;
	
	i = -1;
	while (s2[++i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

t_info	*make_man(int live_num, char *name)
{
	t_info	*new_man;
	
	new_man = (t_info *)malloc(sizeof(t_info));
	new_man->live_num = live_num;
	ft_strcpy(new_man->name, name);
	return (new_man);
}

void	show_man(t_info *man)
{
	printf("name : %s\n", man->name);
	printf("live number : %d\n", man->live_num);
}

int			ft_strcmp(char *s1, char *s2)
{
	int i;
	
	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

void	search_man(t_list *list, char *name, int day)
{
	t_info	*data;
	int		i;
	
	list_first_node(list, &data);
	while (ft_strcmp(list->cur->data->name, name))
		list_next_node(list, &data);
	i = -1;
	while (++i < day)
		list->cur = list->cur->next;
	printf("%d day after, %s -> %s\n", day, name,list->cur->data->name);
}



// 177page. linked list
int			main(void)
{
	t_list	list;
	t_info	*data;
	int		i;
	int		data_num;

	list_init(&list);  // list reset
	data = make_man(950807, "kim");
	list_insert(&list, data);  // insert data to list
	data = make_man(961234, "jin");
	list_insert(&list, data);  // insert data to list
	data = make_man(972345, "bum");
	list_insert(&list, data);  // insert data to list
	data = make_man(983456, "kkk");
	list_insert(&list, data);  // insert data to list
	
	printf("number of data : %d\n", list.data_num);
	list_first_node(&list, &data);  // find first data in list
	show_man(data);
	i = -1;
	while (++i < 2 * list.data_num - 1)
	{
		list_next_node(&list, &data);  // find next data in list
		show_man(data);
	}
	printf("\n");
	
	search_man(&list, "kim", 5);
	
	printf("\n----- data delete -----\n");
	list_first_node(&list, &data); // find first data in list
	free(data);
	list_remove(&list);  // remove node
	data_num = list.data_num;
	i = -1;
	while (++i < data_num)
	{
		list_next_node(&list, &data);  // find next data in list
		free(data);
		list_remove(&list);  // remove node
	}
	printf("number of data : %d\n", list.data_num);
}
