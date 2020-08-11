#include <stdio.h>
#include <stdlib.h>

typedef	int	list_data;

typedef struct		s_node
{
	list_data		data;
	struct s_node	*next;
}					t_node;

typedef	struct	s_list
{
	t_node		*head;
	t_node		*tail;

	t_node		*cur;
	t_node		*befo;
}				t_list;

typedef	int	(*cp)(list_data, list_data);



void 		list_init(t_list *l)
{
	l->head = (t_node *)malloc(sizeof(t_node));
	l->tail = (t_node *)malloc(sizeof(t_node));
	l->head->next = l->tail;
	l->tail->next = l->tail;
}

void		list_insert_head(t_list *l, list_data d)
{
	t_node 	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;

	node->next = l->head->next;
	l->head->next = node;
}

void		list_insert_order(t_list *l, list_data d, cp f)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;

	l->befo = l->head;
	l->cur = l->head->next;
	while(l->cur != l->tail && 0 <= f(d, l->cur->data))
	{
		l->befo = l->cur;
		l->cur = l->cur->next;
	}
	node->next = l->cur;
	l->befo->next = node;
}

int			comp_func(list_data d1, list_data d2)
{
	return (d1 - d2);
}

void		list_print(t_list l)
{
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
	t_node		*re_node;
	list_data	re_data;

	re_node = l->cur;
	re_data = l->cur->data;

	l->befo->next = l->cur->next;
	l->cur = l->befo;
	l->befo->next = l->cur->next;
	free(re_node);
	return (re_data);
}

void		free_all(t_list *l)
{
	l->befo = l->head;
	l->cur = l->head->next;

	while (l->cur != l->tail)
	{
		free(l->befo);
		l->befo = l->cur;
		l->cur = l->cur->next;
	}
	free(l->befo);
	free(l->cur);
}

void		clear_list(t_list *l)
{
	printf("\n---- clear list ----\n");
	free_all(l);
	list_init(l);
}


int			main(void)
{
	t_list		list;
	int			i;

	list_init(&list);

	i = 10;
	while (--i)
		list_insert_order(&list, i, comp_func);
	list_print(list);

	printf("----- 3 delete -----\n");
	list.cur = list.head;
	while (list.cur->data != 3)
	{
		list.befo = list.cur;
		list.cur = list.cur->next;
	}
	list_delete(&list);
	list_print(list);

	clear_list(&list);
	i = 0;
	while (++i < 5)
		list_insert_head(&list, i);
	list_print(list);

	free_all(&list);
}