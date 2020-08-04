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
	t_node			*tail;
	t_node			*cur;
}					t_list;



void		list_init(t_list *l)
{
	l->head = (t_node *)malloc(sizeof(t_node));
	l->tail = (t_node *)malloc(sizeof(t_node));
	l->head->next = l->tail;
	l->head->before = l->head;
	l->tail->next = l->tail;
	l->tail->before = l->head;
}

void		list_insert_head(t_list *l, list_data d)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;

	node->next = l->head->next;
	node->before = l->head;
	l->head->next->before = node;
	l->head->next = node;
}

void		list_insert_tail(t_list *l, list_data d)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;

	node->next = l->tail;
	node->before = l->tail->before;
	l->tail->before->next = node;
	l->tail->before = node;
}

void		list_print(t_list l)
{
	printf("----- list -----\n");
	l.cur = l.head;
	while(l.cur->next != l.tail)
	{
		l.cur = l.cur->next;
		printf("%d ", l.cur->data);
	}
	printf("\n");
}

list_data	list_delete(t_list *l)
{
	t_node		*del_n;
	list_data	del_d;

	del_n = l->cur;
	del_d = l->cur->data;

	l->cur->before->next = l->cur->next;
	l->cur->next->before = l->cur->before;
	if (l->cur->before != l->head)
		l->cur = l->cur->before;
	free(del_n);
	return (del_d);
}

void		free_all(t_list *l)
{
	l->cur = l->head;
	
	while (l->cur != l->tail)
	{
		l->cur = l->cur->next;
		free(l->cur->before);
	}
	free(l->tail);
}



int			main(void)
{
	t_list	list;
	int		i;

	list_init(&list);

	i = 0;
	while (++i < 6)
		list_insert_head(&list, i);
	list_print(list);

	i = 10;
	while (++i < 16)
		list_insert_tail(&list, i);
	list_print(list);

	printf("----- even number data delete -----\n");
	list.cur = list.head;
	while (list.cur->next != list.tail)
	{
		list.cur = list.cur->next;
		if (list.cur->data % 2 == 0)
			list_delete(&list);
	}
	list_print(list);

	free_all(&list);
}