#include <stdio.h>
#include <stdlib.h>

#define	STR_SIZE	32
#define	DATA_SIZE	STR_SIZE * 2 + 4

typedef	struct	s_data
{
	char		name[STR_SIZE];
	char		live[STR_SIZE];
	int			age;
}				t_data;

typedef	t_data	list_data;

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



char	select_nc(void)
{
	char	menu;

	printf("\n----- name card -----\n");
	printf("1. insert\n");
	printf("2. delete\n");
	printf("3. search\n");
	printf("4. load\n");
	printf("5. save\n");
	printf("6. list\n");
	printf("7. end\n");

	while (1)
	{
		printf("select : ");
		gets(&menu);
		if ('1' <= menu && menu <= '7')
			break ;
		printf("wrong select!\n");
	}
	return (menu);
}

void	insert_nc(t_list *l)
{
	t_data	data;

	printf("\n----- insert namecard -----\n");
	printf("name : ");
	gets(data.name);
	printf("live : ");
	gets(data.live);
	printf("age : ");
	scanf("%d", &data.age);
	getchar();

	list_insert_head(l, data);
}

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

void	delete_nc(t_list *l)
{
	char	name[STR_SIZE];

	printf("\n----- delete namecard -----\n");
	printf("name : ");
	gets(name);

	l->befo = l->head;
	l->cur = l->head->next;
	while ((l->cur != l->tail) && ft_strcmp(l->cur->data.name, name))
	{
		l->befo = l->cur;
		l->cur = l->cur->next;
	}

	if (l->cur == l->tail)
	{
		printf("not found!\n");
		return ;
	}
	printf("deleted : %s\n", l->cur->data.name);
	list_delete(l);
}

void	print_card_before(void)
{
	printf("\nname           ");
	printf("live           ");
	printf("age            \n");
	printf("----------     ");
	printf("----------     ");
	printf("----------     \n");
}
void	print_card(t_data d)
{
	printf("%-10s     %-10s     %-10d\n", d.name, d.live, d.age);
}

void	search_nc(t_list *l)
{
	char	name[STR_SIZE];

	printf("\n----- search namecard -----\n");
	printf("name : ");
	gets(name);

	l->cur = l->head->next;
	while ((l->cur != l->tail) && ft_strcmp(l->cur->data.name, name))
		l->cur = l->cur->next;
	
	if (l->cur == l->tail)
	{
		printf("not found!\n");
		return ;
	}
	print_card_before();
	print_card(l->cur->data);
}

void	load_nc(t_list *l, char *f)
{
	FILE	*fp;
	t_node	*node;

	fp = fopen(f, "r");
	if (!fp)
	{
		printf("file open error!\n");
		return ;
	}
	clear_list(l);

	while (1)
	{
		node = (t_node *)malloc(sizeof(t_node));
		if (!fread(node, DATA_SIZE, 1, fp))
		{
			free(node);
			break ;
		}
		node->next = l->head->next;
		l->head->next = node;
	}
	fclose(fp);
}

void	save_nc(t_list *l, char *f)
{
	FILE	*fp;

	fp = fopen(f, "w");
	if (!fp)
	{
		printf("file open error!\n");
		return ;
	}

	l->cur = l->head->next;
	while (l->cur != l->tail)
	{
		fwrite(l->cur, DATA_SIZE, 1, fp);
		l->cur = l->cur->next;
	}
	fclose(fp);
}

void	print_nc(t_list *l)
{
	print_card_before();
	
	l->cur = l->head->next;
	while(l->cur != l->tail)
	{
		print_card(l->cur->data);
		l->cur = l->cur->next;
	}
}



int		main(void)
{
	t_list	l;
	char	*file;
	char	menu;

	file = "NAME_CARD.DAT";
	list_init(&l);
	
	while((menu = select_nc()) != '7')
	{
		if (menu == '1')
			insert_nc(&l);
		else if (menu == '2')
			delete_nc(&l);
		else if (menu == '3')
			search_nc(&l);
		else if (menu == '4')
			load_nc(&l, file);
		else if (menu == '5')
			save_nc(&l, file);
		else if (menu == '6')
			print_nc(&l);
	}
}