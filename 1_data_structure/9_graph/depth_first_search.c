#include <stdio.h>
#include <stdlib.h>

typedef	int	list_data;

typedef struct		s_node
{
	list_data		data;
	struct s_node	*before;
	struct s_node	*next;
}					t_node;

typedef int (*comp_func)(list_data, list_data);

typedef struct		s_list
{
	t_node			*head;
	t_node			*cur;
	comp_func		f;
}					t_list;

typedef	struct	s_al_graph
{
	int			vertex_num;
	int			edge_num;
	int			*visit_info;
	t_list		*list;  // adjacent list
}				t_al_graph;

enum {A, B, C, D, E, F, G};

#define STACK_LEN	100

typedef	int	stack_data;

typedef struct	s_stack
{
	stack_data	stack_arr[STACK_LEN];
	int			top_idx;
}				t_stack;



int			func1(list_data d1, list_data d2)
{
	return (d2 - d1);
}

void		list_init(t_list *list, comp_func f)
{
	list->head = (t_node *)malloc(sizeof(t_node));  // make dummy node
	list->head->next = NULL;
	list->f = f;
}

void		list_insert_comp(t_list *list, list_data data)
{	
	t_node	*new_node;
	t_node	*cur;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	// find position
	cur = list->head;  // head : starting point
	// repeat when priority of data is lower then next node
	while (cur->next && list->f(data, cur->next->data) < 0)
		cur = cur->next;

	// connection
	new_node->next = cur->next;
	if (cur->next)  // if cur is not tail
		cur->next->before = new_node;
	new_node->before = cur;
	cur->next = new_node;
}

int			list_next_node(t_list *list, list_data *data)
{
	if (list->cur->next == NULL)
		return (0);
	list->cur = list->cur->next;
	*data = list->cur->data;
	return (1);
}



void		stack_init(t_stack *stack)
{
	stack->top_idx = -1;
}

void		stack_push(t_stack *stack, stack_data data)
{
	stack->stack_arr[++(stack->top_idx)] = data;
}

int			stack_is_empty(t_stack *stack)
{
	if (stack->top_idx >= 0)  // if stack is not empty
		return (0);
	return (1);
}

stack_data	stack_pop(t_stack *stack)
{
	return (stack->stack_arr[(stack->top_idx)--]);
}



void		ft_memset(void *ptr, int value, size_t num)
{
	int	*arr;
	int i;
	
	arr = (int *)ptr;
	i = -1;
	while (++i < (int)(num / sizeof(int)))
		arr[i] = value;
}

void		graph_init(t_al_graph *graph, int vertex_num)
{
	int	i;
	
	graph->list = (t_list *)malloc(sizeof(t_list) * vertex_num);
	graph->visit_info = (int *)malloc(sizeof(int) * vertex_num);
	ft_memset(graph->visit_info, 0, sizeof(int) * vertex_num);  // reset visit history to 0
	graph->vertex_num = vertex_num;
	graph->edge_num = 0;
	
	i = -1;
	while (++i < vertex_num)
		list_init(&(graph->list[i]), func1);  // list reset
}

void		add_edge(t_al_graph *graph, int from, int to)
{
	list_insert_comp(&(graph->list[from]), to);
	list_insert_comp(&(graph->list[to]), from);
	(graph->edge_num)++;
}

void	show_graph(t_al_graph *graph)
{
	int		data;
	int		i;
	
	i = -1;
	while (++i < graph->vertex_num)
	{
		printf("%c -> ", i + 'A');
		
		graph->list[i].cur = graph->list[i].head;  // head : starting point
		while (list_next_node(&(graph->list[i]), &data))
			printf("%c ", data + 'A');
		printf("\n");
	}
}

int			visit_vertex(t_al_graph *graph, int vertex)
{
	if (!graph->visit_info[vertex])
	{
		graph->visit_info[vertex] = 1;
		printf("%c ", vertex + 'A');
		return (1);
	}
	return (0);
}

void		dfs_graph(t_al_graph *graph, int vertex)
{
	t_stack	stack;
	int		next_vertex;
	int		visit_flag;
	
	stack_init(&stack);  // stack reset
	
	// start vertex
	visit_vertex(graph, vertex);
	stack_push(&stack, vertex);
	
	while (1)
	{
		visit_flag = 0;

		// starting point : head(dummy node)
		graph->list[vertex].cur = graph->list[vertex].head;
		while (list_next_node(&(graph->list[vertex]), &next_vertex))
		{
			if (visit_vertex(graph, next_vertex))  // unvisited
			{
				stack_push(&stack, vertex);
				vertex = next_vertex;
				visit_flag = 1;
				break ;
			}
		}
		
		if (!visit_flag)
		{
			if (stack_is_empty(&stack))
				break ;
			else
				vertex = stack_pop(&stack);
		}
	}
	
	ft_memset(graph->visit_info, 0, sizeof(int) * graph->vertex_num);  // reset visit history to 0
	printf("\n");
}

void		free_all(t_al_graph *graph)
{
	t_node	*cur;
	int		i;
	
	i = -1;
	while (++i < graph->vertex_num)
	{
		cur = graph->list[i].head;  // head : starting point
		while (cur->next)
		{
			cur = cur->next;  // current node reset
			free(cur->before);
		}
		free(cur);
	}
	free(graph->list);
	free(graph->visit_info);
}



// 567page. graph
int			main(void)
{
	t_al_graph graph;
	
	graph_init(&graph, 7);  // adjacent list graph reset

	add_edge(&graph, A, B);  // connact vertex A and B
	add_edge(&graph, A, D);
	add_edge(&graph, B, C);
	add_edge(&graph, D, C);
	add_edge(&graph, D, E);
	add_edge(&graph, E, F);
	add_edge(&graph, E, G);
	
	show_graph(&graph);
	
	dfs_graph(&graph, A);  // graph depth first search
	dfs_graph(&graph, B);
	dfs_graph(&graph, C);
	dfs_graph(&graph, D);
	dfs_graph(&graph, E);
	dfs_graph(&graph, F);
	dfs_graph(&graph, G);
	
	free_all(&graph);
}
