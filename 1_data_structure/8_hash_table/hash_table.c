#include <stdio.h>
#include <stdlib.h>

#define	TABLE_MAX	100

typedef	struct	s_info
{
	int			live_num;
	char		name[32];
	char		address[32];
}				t_info;

enum slot_status {EMPTY, DELETED, INUSE};

typedef	struct			s_slot
{
	t_info				*info;
	int					key;
	enum slot_status	status;
}						t_slot;

typedef int	(*hash_func)(int);


typedef	struct	s_table
{
	t_slot		table[TABLE_MAX];
	hash_func	f;
}				t_table;




int		my_hash_func(int n)
{
	return (n % 100);
}

void	table_init(t_table *table, hash_func f)
{
	int	i;
	
	i = -1;
	while (++i < TABLE_MAX)
		(table->table[i]).status = EMPTY;
	table->f = f;
}

char	*ft_strcpy(char *s1, char *s2)
{
	int i;
	
	i = -1;
	while (s2[++i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

t_info	*make_man(int live_num, char *name, char *address)
{
	t_info	*new_man;
	
	new_man = (t_info *)malloc(sizeof(t_info));
	new_man->live_num = live_num;
	ft_strcpy(new_man->name, name);
	ft_strcpy(new_man->address, address);
	return (new_man);
}

void	table_insert(t_table *table, t_info *man)
{
	int	hv;
	
	hv = table->f(man->live_num);
	table->table[hv].info = man;
	table->table[hv].key = man->live_num;
	table->table[hv].status = INUSE;
}

t_info	*table_search(t_table *table, int key)
{
	int hv;
	
	hv = table->f(key);
	if ((table->table[hv]).status != INUSE)
		return (NULL);
	else
		return ((table->table[hv]).info);
}

void	show_man(t_info *man)
{
	printf("live number : %d\n", man->live_num);
	printf("name : %s\n", man->name);
	printf("adderess : %s\n", man->address);
}

t_info	*table_delete(t_table *table, int key)
{
	int hv;
	
	hv = table->f(key);
	if ((table->table[hv]).status != INUSE)
		return (NULL);
	(table->table[hv]).status = DELETED;
	return ((table->table[hv]).info);
}



// 509page. hash table
int		main(void)
{
	t_table	table;
	t_info	*man;
	
	table_init(&table, my_hash_func);  // table reset

	man = make_man(201470610, "kim", "seoul");
	table_insert(&table, man);
	man = make_man(201470611, "jin", "paris");
	table_insert(&table, man);
	
	man = table_search(&table, 201470610);
	if (man)
		show_man(man);
	man = table_search(&table, 201470611);
	if (man)
		show_man(man);
	
	man = table_delete(&table, 201470610);
	if (man)
		free(man);
	man = table_delete(&table, 201470611);
	if (man)
		free(man);	
	
}
