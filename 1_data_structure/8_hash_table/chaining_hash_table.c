#include <stdio.h>
#include <stdlib.h>

#define	MAX_TABLE	100
#define	MAX_STR		100

typedef	struct	s_info
{
	int			live_num;
	char		name[MAX_STR];
	char		address[MAX_STR];
}				t_info;

typedef	struct	s_slot
{
	int			key;
	t_info		*info;
}				t_slot;

typedef	t_slot	list_data;

typedef	struct		s_node
{
	list_data		data;
	struct s_node	*next;  // next node address
	struct s_node	*before;  // before node addess
}					t_node;

typedef	struct	s_list
{
	t_node		*head;  // head node address
	t_node		*cur;  // current node address
}				t_list;

typedef	int	(*hash_func)(int);  // function pointer

typedef	struct	s_table
{
	t_list		table[MAX_TABLE];
	hash_func	f;
}				t_table;



void		list_init(t_list *list)
{
	list->head = (t_node *)malloc(sizeof(t_node));
	list->head->next = NULL;
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

void	 	list_insert(t_list *list, list_data data)
{
	t_node	*new_node;
	
	new_node = (t_node*)malloc(sizeof(t_node));
	new_node->data = data;
	
	// insert data after head node
	new_node->next = list->head->next;
	new_node->before = list->head;
	if (list->head->next)
		list->head->next->before = new_node;
	list->head->next = new_node;
}

void		show_man(t_info *man)
{
	printf("live number : %d\n", man->live_num);
	printf("name : %s\n", man->name);
	printf("adderess : %s\n", man->address);
}

list_data	list_remove(t_list *list)
{
	t_node		*remem_node;
	list_data	remem_data;
	
	remem_node = list->cur;
	remem_data = list->cur->data;
	
	// connection before node and next node
	list->cur->before->next = list->cur->next;
	if (list->cur->next)
		list->cur->next->before = list->cur->before;
	list->cur = list->cur->before;  // current node reset;
	free(remem_node);
	return (remem_data);
}



void		table_init(t_table *table, hash_func f)
{
	int	i;
	
	i = -1;
	while (++i < MAX_TABLE)
		list_init(&(table->table[i]));  // list reset
	table->f = f;
}

int			my_hash_func(int n)
{
	return (n % 100);
}

t_info		*make_man(int live_num, char *name, char *address)
{
	t_info	*new_man;
	
	new_man = (t_info *)malloc(sizeof(t_info));
	new_man->live_num = live_num;
	ft_strcpy(new_man->name, name);
	ft_strcpy(new_man->address, address);
	return (new_man);
}

t_info		*table_search(t_table *table, int key)
{
	int hv;
	
	hv = table->f(key);
	table->table[hv].cur = table->table[hv].head;  // head : starting point
	while (table->table[hv].cur->next)
	{
		table->table[hv].cur = table->table[hv].cur->next;
		if (table->table[hv].cur->data.key == key)
			return (table->table[hv].cur->data.info);		
	}
	return (NULL);
}

void		table_insert(t_table *table, t_info *man)
{
	int		hv;
	t_slot	slot;
	
	slot.key = man->live_num;
	slot.info = man;
	hv = table->f(man->live_num);

	if (table_search(table, man->live_num))
	{
		printf("key overlap!\n");
		return ;
	}
	else
		list_insert(&(table->table[hv]), slot);
}

t_info		*table_delete(t_table *table, int key)
{
	int		hv;
	t_info	*remem_man;
	
	hv = table->f(key);	
	table->table[hv].cur = table->table[hv].head;  // head : starting point
	while (table->table[hv].cur->next)
	{
		table->table[hv].cur = table->table[hv].cur->next;
		if (table->table[hv].cur->data.key == key)
		{
			remem_man = table->table[hv].cur->data.info;
			list_remove(&(table->table[hv]));
			return (remem_man);
		}
	}
	return (NULL);
}

void		free_all(t_table *table)
{
	int i;
	t_node	*current_node;
	
	i = -1;
	while (++i < MAX_TABLE)
	{
		current_node = table->table[i].head;  // head : starting point
		while (current_node->next)
		{
			current_node = current_node->next;
			free(current_node->before);
		}
		free(current_node);
	}
}



int			main(void)
{
	t_table	table;
	t_info	*man;
	
	table_init(&table, my_hash_func);  // table reset
	
	man = make_man(201470610, "kim", "seoul");
	table_insert(&table, man);  // insert data to table
	man = make_man(201470611, "jin", "paris");
	table_insert(&table, man);
	man = make_man(201470612, "bum", "tokyo");
	table_insert(&table, man);
	
	man = table_search(&table, 201470610);
	if (man)
		show_man(man);
	man = table_search(&table, 201470611);
	if (man)
		show_man(man);
	man = table_search(&table, 201470612);
	if (man)
		show_man(man);

	man = table_delete(&table, 201470610);
	if (man)
		free(man);
	man = table_delete(&table, 201470611);
	if (man)
		free(man);
	man = table_delete(&table, 201470612);
	if (man)
		free(man);
		
	free_all(&table);
}
