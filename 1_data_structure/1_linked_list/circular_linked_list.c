#include <stdio.h>
#include <stdlib.h>

typedef	int	list_data;

typedef	struct		s_node
{
	list_data		data;
	struct s_node	*next;
}					t_node;

typedef struct	s_list
{
	t_node		*tail;
	t_node		*cur;
}				t_list;



void		list_init(t_list *l)
{
	l->tail = NULL;
}

void		list_insert_tail(t_list *l, list_data d)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;

	if (l->tail)
	{
		node->next = l->tail->next;
		l->tail->next = node;
		l->tail = node;
	}
	else  // there is no node
	{
		node->next = node;
		l->tail = node;
	}
}

list_data	list_remove(t_list *l)
{
	t_node		*del_n;
	t_node		*before;
	list_data	del_d;

	del_n = l->cur;  // remember node to be deleted
	del_d = l->cur->data;  // remember data to be deleted

	before = l->tail;
	while (before->next != del_n)  // find before node
		before = before->next;

	if (l->tail->next == l->tail)  // if there is one node
		l->tail = NULL;
	else
	{
		before->next = l->cur->next;
		l->cur = before;  // current node reset
	}
	if (del_n == l->tail)
		l->tail = before;  // tail node reset
	
	free(del_n);
	return (del_d);
}

void		josep(int n, int k)
{
	t_list		list;
	list_data	data;
	int			i;

	list_init(&list);  // list reset

	i = 0;
	while (++i <= n)
		list_insert_tail(&list, i);

	list.cur = list.tail;
	while (list.tail)
	{
		i = -1;
		while (++i < k)
			list.cur = list.cur->next;
		data = list_remove(&list);
		printf("%d ", data);
	}
	printf("\n");
}



// 177page. linked list
int			main(void)
{
	int	n;
	int	k;

	scanf("%d %d", &n, &k);
	getchar();
	josep(n, k);
}