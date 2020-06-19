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

#define QUEUE_SIZE 100

typedef	int	queue_data;

typedef	struct	s_queue
{
	int			front;
	int			rear;
	queue_data	q_arr[QUEUE_SIZE];
}				t_queue;



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



void	queue_init(t_queue *q)
{
	q->front = -1;
	q->rear = -1;
}

void	enter_queue(t_queue *q, queue_data data)
{
	q->q_arr[++(q->rear)] = data;
}

int			queue_is_empty(t_queue *q)
{
	if (q->front == q->rear)
		return (1);
	return (0);
}

queue_data	delete_queue(t_queue *q)
{
	return (q->q_arr[++(q->front)]);
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

void		show_graph(t_al_graph *graph)
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

void		bfs_graph(t_al_graph *graph, int vertex)
{
	t_queue	q;
	int		next_vertex;
	
	queue_init(&q);  // queue reset
	
	visit_vertex(graph, vertex);
	while (1)
	{
		// starting point : head(dummy node)
		graph->list[vertex].cur = graph->list[vertex].head;
		while (list_next_node(&(graph->list[vertex]), &next_vertex))
			if (visit_vertex(graph, next_vertex))
				enter_queue(&q, next_vertex);

		if (queue_is_empty(&q))
			break ;
		else
			vertex = delete_queue(&q);
	}

	ft_memset(graph->visit_info, 0, sizeof(int) * graph->vertex_num);  // reset visit history to 0
	printf("\n");
}

void		free_all(t_al_graph *graph)
{
	list_data	data;
	int			i;
	
	i = -1;
	while (++i < graph->vertex_num)
	{
		graph->list[i].cur = graph->list[i].head;  // head : starting point
		while (list_next_node(&(graph->list[i]), &data))
			free(graph->list[i].cur->before);
		free(graph->list[i].cur);
	}
	free(graph->list);
	free(graph->visit_info);
}



// 576page. graph
int			main(void)
{
	t_al_graph	graph;
	
	graph_init(&graph, 7);  // adjacent list graph reset
	
	add_edge(&graph, A, B);  // connact vertex A and B
	add_edge(&graph, A, D);
	add_edge(&graph, B, C);
	add_edge(&graph, D, C);
	add_edge(&graph, D, E);
	add_edge(&graph, E, F);
	add_edge(&graph, E, G);
	
	show_graph(&graph);
	
	bfs_graph(&graph, A);  // graph breadth first search
	bfs_graph(&graph, B);
	bfs_graph(&graph, C);
	bfs_graph(&graph, D);
	bfs_graph(&graph, E);
	bfs_graph(&graph, F);
	bfs_graph(&graph, G);
	
	free_all(&graph);
}
