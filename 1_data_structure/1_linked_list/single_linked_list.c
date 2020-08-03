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
}				t_list;

typedef	int	(*cmp)(list_data, list_data);



int			comp_func(list_data d1, list_data d2)
{
	return (d1 - d2);
}

void		print_list(t_list l)
{
	l.cur = l.head;

	while(l.cur->next != l.tail)
	{
		l.cur = l.cur->next;
		printf("%d ", l.cur->data);
	}
	printf("\n");
}

void 		list_init(t_list *l)
{
	l->head = (t_node *)malloc(sizeof(t_node));  // make head dummy node
	l->tail = (t_node *)malloc(sizeof(t_node));  // make tail dummy node
	l->head->next = l->tail;
	l->tail->next = l->tail;
}

void		list_insert(t_list *l, list_data d, cmp f)
{
	t_node	*node;
	t_node	*before;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;

	// find position
	before = l->head;
	l->cur = l->head->next;
	// repeat when priority of data is lower then next node
	while (l->cur != l->tail && 0 <= f(d, l->cur->data))
	{
		before = l->cur;
		l->cur = l->cur->next;
	}

	// connection
	node->next = l->cur;
	before->next = node;
}

list_data	list_delete(t_list *l)
{
	t_node		*del_n;
	list_data	del_d;
	t_node		*before;

	del_n = l->cur;  // remember node to be deleted
	del_d = l->cur->data;  // remember data to be deleted

	before = l->head;
	while (before->next != del_n)  // find before node position
		before = before->next;
	before->next = del_n->next;  // connection

	l->cur = before;
	free(del_n);
	return (del_d);
}

void		free_all(t_list *l)
{
	t_node	*before;

	l->cur = l->head;
	while (l->cur != l->tail)
	{
		before = l->cur;
		l->cur = l->cur->next;
		free(before);
	}
	free(l->tail);
}



// 152page. linked list
int			main(void)
{
	t_list		list;
	int			i;

	list_init(&list);  // list reset

	i = 0;
	while (++i < 11)
		list_insert(&list, i, comp_func);
	print_list(list);

	printf("----- 3 delete -----\n");
	list.cur = list.head;  // head : starting point
	while (list.cur->data != 3)
		list.cur = list.cur->next;
	list_delete(&list);
	print_list(list);

	free_all(&list);
}