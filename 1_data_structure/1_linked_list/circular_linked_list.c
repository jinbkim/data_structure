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
	struct s_node	*before;
	struct s_node	*next;
}					t_node;

typedef struct		s_list
{
	t_node			*cur;
	t_node			*tail;
}					t_list;



void		list_init(t_list *list)
{
	list->tail = NULL;
}

void		list_insert(t_list *list, list_data data)
{	
	t_node	*new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	if (list->tail)
	{
		new_node->next = list->tail->next;
		new_node->before = list->tail;
	}
	else  // there is no node
		list->tail = new_node;
	list->tail->next = new_node;
	new_node->next->before = new_node;
}

int			list_next_node(t_list *list, list_data *data)
{
	if (!list->tail)
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
	
	
	if (list->tail == list->tail->next)  // if there is one node
		list->tail = NULL;
	else
	{
		list->cur->before->next = list->cur->next;
		list->cur->next->before = list->cur->before;
		list->cur = list->cur->before;  // current node reset
		if (remem_node == list->tail)
			list->tail = list->cur;  // tail node reset
	}
	
	free(remem_node);
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
	printf("live number : %d\n\n", man->live_num);
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
	
	list->cur = list->tail;  // tail : starting point
	while (1)
	{
		list_next_node(list, &data);
		if (!ft_strcmp(data->name, name))
			break ;
	}
	
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
	
	list_init(&list);  // list reset

	// insert data to list
	data = make_man(950807, "kim");
	list_insert(&list, data);
	data = make_man(961234, "jin");
	list_insert(&list, data); 
	data = make_man(972345, "bum");
	list_insert(&list, data); 
	data = make_man(983456, "kkk");
	list_insert(&list, data);
	
	// show all data
	i = -1;
	list.cur = list.tail;  // tail : starting point
	while (++i < 10)
	{
		list_next_node(&list, &data);
 		show_man(data);
	}
	
	search_man(&list, "kim", 5);
	
	// delete all data
	while (1)
	{
		list_next_node(&list, &data);
		free(data);
		list_remove(&list);
		if (!list.tail)
			break ;
	}
}
