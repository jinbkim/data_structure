#include <stdio.h>
#include <stdlib.h>

#define	HEAP_SIZE	100

typedef	int	list_data;

typedef	int (*sort_func)(list_data, list_data);  // function pointer

typedef struct		s_node
{
	list_data		data;
	struct s_node	*next;  // address of next node
	struct s_node	*before;  // address of before node
}					t_node;

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

typedef	int	(*priority_comp)(heap_data, heap_data);  // function pointer

typedef	struct		s_p_queue
{
	int				data_num;  // number of data
	heap_data		heap_arr[HEAP_SIZE];	
	priority_comp	f;
}					t_p_queue;

typedef	struct	s_al_graph
{
	int			vertex_num;
	int			edge_num;
	int			*visit_info;
	t_list		*list;  // adjacent list
	t_p_queue	w_info_q;
}				t_al_graph;

enum {A, B, C, D, E, F};



void		list_init(t_list *list, sort_func f)
{
	list->head = (t_node *)malloc(sizeof(t_node));  // make dummy node
	list->head->next = NULL;
	list->f = f;
}

void		p_queue_init(t_p_queue *pq, priority_comp f)
{
	pq->data_num = 0;
	pq->f = f;
}

void		list_insert(t_list *list, list_data data)
{	
	t_node	*new_node;
	t_node	*cur;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	
	// find position of the new node
	cur = list->head;  // head : starting point
	while (cur->next && list->f(data, cur->next->data))
		cur = cur->next;

	// insert data after head node
	new_node->next = cur->next;
	if (cur->next)  // if node is exist
		cur->next->before = new_node;
	new_node->before = cur;
	cur->next = new_node;
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



void		ft_memset(void *ptr, int value, size_t num)
{
	int	*arr;
	int i;
	
	arr = (int *)ptr;
	i = -1;
	while (++i < (int)(num / sizeof(int)))
		arr[i] = value;
}

int			comp_func(heap_data e1, heap_data e2)
{
	return (e1.weight - e2.weight);
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
	p_queue_init(&(graph->w_info_q), comp_func);  // priority queue reset
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

void		conversion_kruskal(t_al_graph *graph)
{
	t_edge	remem_edge[32];
	
	
	
	
	
	
	
	t_edge	remem_edge[32];
	t_edge	edge;
	int		edge_i;
	int		i;
	
	edge_i = -1;
	i = -1;
	
	// repeat until forming minimum cost spanning tree
	// MST edge number + 1 = vertex number
	while (graph->edge_num + 1 != graph->vertex_num)
	{
		// store edge with the highest weight in the priority queue
		edge = delete_p_queue(&(graph->w_info_q));
		// delete edge taken out of priority queue from graph
		remove_edge(graph, edge.vertex1, edge.vertex2);
		if (exist_edge(graph, edge.vertex1, edge.vertex2))
		{
			restore_edge(graph, edge.vertex1, edge.vertex2);
			remem_edge[++edge_i] = edge;
		}
	}
	
	// data restoration
	while (++i < edge_i)
		enter_p_queue(&(graph->w_info_q), remem_edge[i]);
}



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
