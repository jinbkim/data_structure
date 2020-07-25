#include <stdio.h>
#include <stdlib.h>

typedef	int	list_data;

typedef	struct		s_node
{
	list_data		data;
	struct s_node	*next;
	struct s_node	*before;
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
		node->before = l->tail;
		l->tail->next->before = node;
		l->tail->next = node;
		l->tail = node;
	}
	else
	{
		node->next = node;
		node->before = node;
		l->tail = node;
	}
	
}

list_data	list_remove(t_list *l)
{
	t_node		*del_n;
	list_data	del_d;

	del_n = l->cur;
	del_d = l->cur->data;

	if (l->tail->next == l->tail)
		l->tail = NULL;
	else if (del_n == l->tail)
	{
		del_n->before->next = del_n->next;
		del_n->next->before = del_n->before;
		l->cur = l->cur->before;
		l->tail = l->tail->before;
	}
	else
	{
		del_n->before->next = del_n->next;
		del_n->next->before = del_n->before;
		l->cur = l->cur->before;
	}
	free(del_n);
	return (del_d);
}

void		josep(int n, int k)
{
	t_list		list;
	list_data	data;
	int			i;

	list_init(&list);
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



int		main(void)
{
	int	n;
	int	k;

	scanf("%d %d", &n, &k);
	getchar();
	josep(n, k);
}