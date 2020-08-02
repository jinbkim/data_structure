#include <stdio.h>
#include <stdlib.h>

typedef	char	list_data;

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
}					t_list;



void		list_init(t_list *list)
{
	list->head = (t_node *)malloc(sizeof(t_node));
	list->head->next = NULL;
	list->cur = list->head;
}

int			list_next_node(t_list *list, list_data *data)
{
	if (list->cur->next == NULL)
		return (0);
	list->cur = list->cur->next;
	*data = list->cur->data;
	return (1);
}

void		list_remove_cur(t_list *l)
{
	t_node	*del_n;

	if (l->cur == l->head)
		return ;
	del_n = l->cur;
	l->cur->before->next = l->cur->next;
	if (l->cur->next)
		l->cur->next->before = l->cur->before;
	l->cur = l->cur->before;
	free(del_n);
}

void		list_insert_cur(t_list *l, list_data d)
{
	t_node	*new_n;

	new_n = (t_node *)malloc(sizeof(t_node));
	new_n->data = d;

	new_n->next = l->cur->next;
	new_n->before = l->cur;
	if (l->cur->next)
		l->cur->next->before = new_n;
	l->cur->next = new_n;
	l->cur = l->cur->next;
}

void		key_log(char *w)
{
	t_list	list;
	char	data;
	int		i;

	list_init(&list);
	i = -1;
	while (w[++i])
	{
		if (w[i] == '<')
		{
			if (list.cur != list.head)
				list.cur = list.cur->before;
		}
		else if (w[i] == '>')
		{
			if (list.cur->next)
				list.cur = list.cur->next;
		}
		else if (w[i] == '-')
			list_remove_cur(&list);
		else
			list_insert_cur(&list, w[i]);
	}
	list.cur = list.head;
	while(list_next_node(&list, &data))
	{
		printf("%c", data);
		free(list.cur->before);
	}
	free(list.cur);
	printf("\n");
}



int			main(void)
{
	char	word[1000001];
	int 	n;
	int		i;

	scanf("%d", &n);
	getchar();
	i = -1;
	while (++i < n)
	{
		scanf("%s", word);
		getchar();
		key_log(word);
	}
}