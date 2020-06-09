#include <stdio.h>
#include <stdlib.h>

#define	HEAP_SIZE	100
#define STACK_LEN	100

enum {A, B, C, D, E, F};

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
	t_node		*cur;	// current node of list
	sort_func	f;
}				t_list;

typedef	struct	s_edge
{
	int			vertex1;
	int			vertex2;
	int			weight;
}				t_edge;

typedef	t_edge	heap_data;

typedef	int	(*priority_comp_func)(heap_data, heap_data);  // function pointer

typedef	struct	s_p_queue
{
	int					data_num;  // number of data
	heap_data			heap_arr[HEAP_SIZE];	
	priority_comp_func	f;
}				t_p_queue;

typedef	struct	s_al_graph
{
	int			vertex_num;
	int			edge_num;
	int			*visit_info;
	t_list		*list;  // adjacent list
	t_p_queue	w_info_q;
}				t_al_graph;

typedef	int	stack_data;

typedef struct	s_stack
{
	stack_data	stack_arr[STACK_LEN];  // array type stack
	int			top_idx;  // top index of stack
}				t_stack;



void		ft_memset(void *ptr, int value, size_t num)
{
	int	*arr;
	int i;
	
	arr = (int *)ptr;
	i = -1;
	while (++i < (int)(num / sizeof(int)))
		arr[i] = value;
}

int			left_data_is_big(int d1, int d2)
{
	if (d1 > d2)
		return (1);
	return (0);
}

void		list_init(t_list *list, sort_func f)
{
	list->head = (t_node *)malloc(sizeof(t_node));  // make dummy node
	list->head->next = NULL;
	list->f = f;
}

void		p_queue_init(t_p_queue *pq, priority_comp_func f)
{
	pq->data_num = 0;
	pq->f = f;
}

int			priority_comp(heap_data e1, heap_data e2)
{
	return (e1.weight - e2.weight);
}

void		enter_p_queue(t_p_queue *pq, heap_data data)
{
	int	idx;
	
	// number of nodes stored in heap matches index of last node
	idx = ++(pq->data_num);
	
	// find index location
	while (idx != 1)
	{
		if (pq->f(data, pq->heap_arr[idx / 2]) < 0)  // compare priority of parent node
			break ;
		else
		{
			pq->heap_arr[idx] = pq->heap_arr[idx / 2];
			idx /= 2;
		}
	}
	pq->heap_arr[idx] = data;
}

heap_data	delete_p_queue(t_p_queue *pq)
{
	heap_data	remem_data;
	heap_data	last_elem;
	int			parent_i;
	int			child_i;
	
	remem_data = pq->heap_arr[1]; // remember data to be deleted
	last_elem = pq->heap_arr[(pq->data_num)--];
	parent_i = 1;
	
	// store index to child_i (high priority child node)
	// compare priority of the last data from the root node to ~
	while ((child_i = get_high_priority_child_idx(pq, parent_i)))
	{
		if (pq->f(last_elem, pq->heap_arr[child_i]) <= 0)  // if you find good location
			break ;
		pq->heap_arr[parent_i] = pq->heap_arr[child_i];
		parent_i = child_i;
	}
	
	pq->heap_arr[parent_i] = last_elem;
	return (remem_data);
}

int			list_first_node(t_list *list, list_data *data)
{
	if (!list->head->next)  // if node is not exist
		return (0);
	list->cur = list->head->next;
	*data = list->cur->data;
	return (1);	
}

int			list_next_node(t_list *list, list_data *data)
{
	if (!list->cur->next)  // if next node is not exist
		return (0);
	list->cur = list->cur->next;
	*data = list->cur->data;
	return (1);
}

list_data	list_remove(t_list *list)
{
	t_node		*remem_node;
	list_data	remem_data;

	remem_node = list->cur;  // remember node to be deleted
	remem_data = list->cur->data;  // remember data to be deleted
	
	// connection before node and next noe
	list->cur->before->next = list->cur->next;
	if (list->cur->next)  // if next node exist,
		list->cur->next->before = list->cur->before;
	else
		list->cur->next = NULL;
	
	// current node reset
	if (list->cur->before != list->head)  // if before node is not head node,
		list->cur = list->cur->before;
	else if (list->cur->next)  // if next node is exist,
		list->cur = list->cur->next;
	
	free(remem_node);
	(list->data_num)--;
	return (remem_data);
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
		list_init(&(graph->list[i]), left_data_is_big);  // list reset
	p_queue_init(&(graph->w_info_q), priority_comp);  // priority queue reset
}

void		add_edge(t_al_graph *graph, int from, int to, int weight)
{
	t_edge	edge;
	
	edge.vertex1 = from;
	edge.vertex2 = to;
	edge.weight = weight;
	
	list_insert(&(graph->list[from]), to);
	list_insert(&(graph->list[to]), from);
	(graph->edge_num)++;
	
	enter_p_queue(&(graph->w_info_q), edge);  // store edge weight in priority queue
}

void		remove_edge_one_way(t_al_graph *graph, int from, int to)
{
	int	vertex;
	
	if (list_first_node(&(graph->list[from]), &vertex))
	{
		if (vertex == to)
			list_remove(&(graph->list[from]));
		else
		{
			while (list_next_node(&(graph->list[from]), &vertex)))
			{
				if (vertex == to)
				{
					list_remove(&(graph->list[from]));
					return ;
				}
			}
		}
	}
}

void		remove_edge(t_al_graph *graph, int from, int to)
{
	remove_edge_one_way(graph, from, to);
	remove_edge_one_way(graph, to, from);
	(graph->edge_num)--;
}

int			visit_vertex(t_al_graph *graph, int visit)
{
	if (!graph->visit_info[visit])
	{
		graph->visit_info[visit] = 1;
		printf("%c ", visit + 'A');
		return (1);
	}
	return (0);
}

int			no_edge(t_al_graph *graph, int vertex1, int vertex2)
{
	t_stack stack;
	int		visit_vertex;
	int		next_vertex;

	visit_vertex = 1;
	stack.top_idx = -1;
	visit_vertex(graph, visit_vertex)
}

void		conversion_kruskal(t_al_graph *graph)
{
	t_edge	remem_edge[32];
	t_edge	edge;
	
	// repeat until forming minimum cost spanning tree
	// MST edge number + 1 = vertex number
	while (graph->edge_num + 1 != graph->vertex_num)
	{
		edge = delete_p_queue(&(graph->w_info_q));
		remove_edge(graph, edge.vertex1, edge.vertex2);
		if (no_edge(graph, edge.vertex1, edge.vertex2))
	}
}



// 597page. graph
int			main(void)
{
	t_al_graph	graph;
	
	graph_init(&graph, 6);  // graph reset
	
	add_edge(&graph, A, B, 9);  // connact vertex A and B
	add_edge(&graph, B, C, 2);
	add_edge(&graph, A, C, 12);
	add_edge(&graph, A, D, 8);
	add_edge(&graph, D, C, 6);
	add_edge(&graph, A, F, 11);
	add_edge(&graph, F, D, 4);
	add_edge(&graph, D, E, 3);
	add_edge(&graph, E, C, 7);
	add_edge(&graph, F, E, 13);
	
	conversion_kruskal(&graph);
}
