#include <stdio.h>
#include <stdlib.h>

typedef	int	list_data;

typedef struct		s_node
{
	list_data		data;
	struct s_node	*next;  // address of next node
	struct s_node	*before;  // address of before node
}					t_node;

typedef	int (*sort_func)(list_data, list_data);  // function pointer

typedef	struct	s_list
{
	t_node		*head;  // head node of list
	sort_func	f;
}				t_list;

typedef	struct	s_al_graph
{
	int			vertex_num;
	int			edge_num;
	t_list		*list;  // adjacent list
}				t_al_graph;

enum {A, B, C ,D ,E};



int		left_data_is_big(int d1, int d2)
{
	if (d1 > d2)
		return (1);
	return (0);
}

void	list_init(t_list *list, sort_func f)
{
	list->head = (t_node *)malloc(sizeof(t_node));  // make dummy node
	list->head->next = NULL;
	list->f = f;
}

void		list_insert(t_list *list, list_data data)
{	
	t_node	*new_node;
	t_node	*current_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	// find position of the new node
	current_node = list->head;  // head : starting point
	while (current_node->next && list->f(data, current_node->next->data))
		current_node = current_node->next;

	// insert data after head node
	new_node->next = current_node->next;
	if (current_node->next)  // if node is exist
		current_node->next->before = new_node;
	new_node->before = current_node;
	current_node->next = new_node;
}

void	free_all(t_al_graph *graph)
{
	t_node	*current_node;
	int		i;
	
	i = -1;
	while (++i < graph->vertex_num)
	{
		current_node = graph->list[i].head;  // head : starting point
		while (current_node->next)
		{
			current_node = current_node->next;  // current node reset
			free(current_node->before);
		}
		free(current_node);
	}
	free(graph->list);
}



void	show_graph(t_al_graph *graph)
{
	t_node	*current_node;
	int		i;
	
	i = -1;
	while (++i < graph->vertex_num)
	{
		printf("%c -> ", i + 'A');
		current_node = graph->list[i].head;  // head : starting point
		while (current_node->next)
		{
			current_node = current_node->next;  // current node reset
			printf("%c", current_node->data + 'A');
			if (current_node->next)
				printf(", ");
		}
		printf("\n");
	}
}

void	graph_init(t_al_graph *graph, int vertex_num)
{
	int	i;
	
	graph->list = (t_list *)malloc(sizeof(t_list) * vertex_num);
	graph->vertex_num = vertex_num;
	graph->edge_num = 0;
	
	i = -1;
	while (++i < vertex_num)
		list_init(&(graph->list[i]), left_data_is_big);  // list reset
}

void	add_edge(t_al_graph *graph, int from, int to)
{
	list_insert(&(graph->list[from]), to);
	list_insert(&(graph->list[to]), from);
	(graph->edge_num)++;
}



// 547page. graph
int		main(void)
{
	t_al_graph graph;
	
	graph_init(&graph, 5);  // adjacent list graph reset

	add_edge(&graph, A, B);  // connact vertex A and B
	add_edge(&graph, A, D);
	add_edge(&graph, B, C);
	add_edge(&graph, C, D);
	add_edge(&graph, D, E);
	add_edge(&graph, E, A);
	
	show_graph(&graph);
	free_all(&graph);
}
