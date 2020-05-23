#include <stdio.h>
#include <stdlib.h>

#define LIST_MAX	100





#define	NAME_MAX	100
#define PHONE_MAX	100

typedef struct	s_info
{
	char		name[NAME_MAX];
	char		phone[PHONE_MAX];
}				t_info;

typedef t_info *list_data;





/*
list_arr : array type list
data_num : number of data 
cur_i : current index of the array
*/
typedef	struct	s_list
{
	list_data	list_arr[LIST_MAX];
	int			data_num;
	int			cur_i;
}				t_list;

void		list_insert(t_list *list, list_data data)
{
	if (LIST_MAX <= list->data_num)  // wrong memory range of array
		printf("list is full!\n");
	else
		list->list_arr[(list->data_num)++] = data;  // insert data to list 
}

void		list_init(t_list *list)
{
	list->data_num = 0;  // number of data reset
}

int			first_list_data(t_list *list, list_data *data)
{
	if (!list->data_num)  // if number of data is zero, return 0
		return (0);
	list->cur_i = -1;  // current index of the array reset
	*data = list->list_arr[++(list->cur_i)];  // store first data in variable(data)
	return (1);
}

int			next_list_data(t_list *list , list_data *data)
{
	if (list->data_num - 1 <= list->cur_i)  // if current index of the array is bigger than number of data , return 0
		return (0);
	*data = list->list_arr[++(list->cur_i)];  // store next data in variable(data)
	return (1);
}

list_data	list_remove(t_list *list)
{
	list_data	remem_data;
	int			i;
	
	remem_data = list->list_arr[list->cur_i];  // remember data to be deleted
	i = --(list->cur_i);
	while (++i < list->data_num - 1)
		list->list_arr[i] = list->list_arr[i + 1];  // move data forward one space
	(list->data_num)--;
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

t_info		*make_man(char *name, char *phone)
{
	t_info	*new_man;
	
	new_man = (t_info *)malloc(sizeof(t_info));
	ft_strcpy(new_man->name, name);
	ft_strcpy(new_man->phone, phone);
	return (new_man);
}

void		show_man(t_info *man)
{
	printf("name : %s\n", man->name);
	printf("phone : %s\n", man->phone);
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





// 99page. linked list
int			main(void)
{
	t_list list;
	t_info *data;
	
	list_init(&list);  // list reset
	
	data = make_man("kim", "010-1111-1111");  // enter information in data
	list_insert(&list, data);  // insert data to list
	data = make_man("jin", "010-2222-2222");
	list_insert(&list, data);
	data = make_man("bum", "010-3333-3333");
	list_insert(&list, data);
	
	printf("----- all man information -----\n");
	if (first_list_data(&list, &data))  // find first data in list
	{
		show_man(data);
		while (next_list_data(&list, &data))  // find next data in list
			show_man(data);
	}
	
	printf("\n----- jin information -----\n");
	if (first_list_data(&list, &data))  // find first data in list
	{
		if (!ft_strcmp(data->name, "jin"))
			show_man(data);
		while (next_list_data(&list, &data))  // find next data in list
			if (!ft_strcmp(data->name, "jin"))
				show_man(data);
	}
	
	printf("\n----- kim phone change -----\n");
	if (first_list_data(&list, &data))  // find first data in list
	{
		if (!ft_strcmp(data->name, "kim"))
			ft_strcpy(data->phone, "010-4444-4444");
		while (next_list_data(&list, &data))  // find next data in list
			if (!ft_strcmp(data->name, "kim"))
				ft_strcpy(data->phone, "010-4444-4444");
	}
	
	printf("----- bum delete -----\n");
	if (first_list_data(&list, &data))  // find first data in list
	{
		if (!ft_strcmp(data->name, "bum"))
		{
			data = list_remove(&list);  // remove data
			free(data);
		}
		while (next_list_data(&list, &data))  // find next data in list
		{
			if (!ft_strcmp(data->name, "bum"))
			{
				data = list_remove(&list);  // remove data
				free(data);
			}
		}
	}
	
	printf("\n----- all man information -----\n");
	if (first_list_data(&list, &data))  // find first data in list
	{
		show_man(data);
		data = list_remove(&list);  // remove data
		free(data);
		while (next_list_data(&list, &data))  // find next data in list
		{
			show_man(data);
			data = list_remove(&list);  // remove data
			free(data);
		}
	}
}
