#include <stdio.h>
#include <stdlib.h>

typedef	char	list_data;

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

void 		list_init(t_list *l)
{
	l->head = NULL;
}

void		list_insert_tail(t_list *l, list_data d)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->data = d;

	if (l->head)
		l->tail->next = node;
	else
		l->head = node;
	l->tail = node;
	node->next = l->head;
}

list_data	list_delete(t_list *l)
{
	t_node		*re_node;
	t_node		*befo;
	list_data	re_data;

	re_node = l->cur;
	re_data = l->cur->data;
	l->befo->next = l->cur->next;
	l->cur = l->befo;
	befo = l->head;
	while (befo->next != l->cur)
		befo = befo->next;
	l->befo = befo;
	free(re_node);
	return (re_data);
}

void		josep(int n, int m)
{
	t_list		list;
	int			i;
	int			j;

	list_init(&list);
	i = -1;
	while (++i < n)
		list_insert_tail(&list, 'A' + i);
	list.cur = list.tail;
	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < m)
			list.cur = list.cur->next;
		printf("%c ", list_delete(&list));
	}
	printf("\n");
}

int			main(void)
{
	int	n;
	int	m;

	printf("----- Josephus problem -----\n");
	printf("n , m : ");
	scanf("%d %d", &n, &m);
	getchar();
	if (n <= 0 || m <= 0)
	{
		printf("wrong input!\n");
		return (0);
	}
	josep(n, m);
}