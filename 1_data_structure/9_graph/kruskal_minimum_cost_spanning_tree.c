#include <stdio.h>
#include <stdlib.h>

typedef	int list_data;

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

typedef	struct	s_edge
{
	int			vertex1;
	int			vertex2;
	int			weight;
}				t_edge;

#define	PQ_SIZE	100

typedef	t_edge	pq_data;
typedef	int		(*priority_comp)(pq_data, pq_data);

typedef	struct		s_p_queue
{
	int				data_num;
	pq_data			pq_arr[PQ_SIZE];	
	priority_comp	f;
}					t_p_queue;

typedef	struct	s_al_graph
{
	int			vertex_num;
	int			edge_num;
	int			*visit_info;
	t_list		*list;  // adjacent list
	t_p_queue	weight_info;
}				t_al_graph;

enum {A, B, C, D, E, F};

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

list_data	list_remove(t_list *list)
{
	t_node		*remem_node;
	list_data	remem_data;

	remem_node = list->cur;  // remember node to be deleted
	remem_data = list->cur->data;  // remember data to be deleted
	
	// connection before node and next node
	list->cur->before->next = list->cur->next;
	if (list->cur->next)  // if current node is not tail
		list->cur->next->before = list->cur->before;

	list->cur = list->cur->before;  // current node reset
	
	free(remem_node);
	return (remem_data);
}

int			list_next_node(t_list *list, list_data *data)
{
	if (list->cur->next == NULL)
		return (0);
	list->cur = list->cur->next;
	*data = list->cur->data;
	return (1);
}



int		func2(pq_data a, pq_data b)
{
	return (a.weight - b.weight);
}

void	p_queue_init(t_p_queue *pq, priority_comp f)
{
	pq->data_num = 0;
	pq->f = f;
}

void	enter_p_queue(t_p_queue *pq, pq_data data)
{
	int	idx;
	
	// number of nodes stored in priority queue matches index of last node
	idx = ++(pq->data_num);
	
	// find index location
	while (idx != 1)
	{
		// break when priority of data is lower then parent node
		if (pq->f(data, pq->pq_arr[idx / 2]) <= 0)
			break ;
		else
		{
			pq->pq_arr[idx] = pq->pq_arr[idx / 2];
			idx /= 2;
		}
	}
	
	pq->pq_arr[idx] = data;
}

int			get_high_priority_child_idx(t_p_queue *pq, int idx)
{
	if (pq->data_num < idx * 2)  // if child node is not exist
		return (0);
	else if (pq->data_num == idx * 2)  // if left child node is last node
		return (idx * 2);
	else
	{
		// if left child node has a higher priority than right child node,
		if (pq->f(pq->pq_arr[idx * 2], pq->pq_arr[idx * 2 + 1]) > 0)
			return (idx * 2);
		else
			return (idx * 2 + 1);
	}
}

pq_data	delete_p_queue(t_p_queue *pq)
{
	pq_data	remem_data;
	pq_data	last_elem;
	int			parent_i;
	int			child_i;
	
	remem_data = pq->pq_arr[1]; // remember data to be deleted
	last_elem = pq->pq_arr[(pq->data_num)--];
	
	// starting root node, find place of last element by comparing priortiy
	parent_i = 1;
	while ((child_i = get_high_priority_child_idx(pq, parent_i)))
	{
		// break when priority of last element is higher then child node
		if (pq->f(last_elem, pq->pq_arr[child_i]) >= 0)  // if you find good location
			break ;
		pq->pq_arr[parent_i] = pq->pq_arr[child_i];
		parent_i = child_i;
	}
	
	pq->pq_arr[parent_i] = last_elem;
	return (remem_data);
}

int		p_queue_is_empty(t_p_queue *pq)
{
	if (pq->data_num)
		return (0);
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
	p_queue_init(&(graph->weight_info), func2);  // priority queue reset
}

void		add_edge(t_al_graph *graph, int from, int to, int weight)
{
	t_edge	edge = {from, to, weight};
	
	list_insert_comp(&(graph->list[from]), to);
	list_insert_comp(&(graph->list[to]), from);
	(graph->edge_num)++;
	
	enter_p_queue(&(graph->weight_info), edge);  // store edge weight in priority queue
}

void		remove_edge_one_way(t_al_graph *graph, int from, int to)
{
	graph->list[from].cur = graph->list[from].head;  // head : starting point
	while (graph->list[from].cur->next)
	{
		graph->list[from].cur = graph->list[from].cur->next;
		if (graph->list[from].cur->data == to)
		{
			list_remove(&(graph->list[from]));
			break ;
		}
	}
}

void		remove_edge(t_al_graph *graph, int from, int to)
{
	remove_edge_one_way(graph, from, to);
	remove_edge_one_way(graph, to, from);
	(graph->edge_num)--;
}

int			visit_vertex(t_al_graph *graph, int vertex)
{
	if (!graph->visit_info[vertex])
	{
		graph->visit_info[vertex] = 1;
		//printf("%c ", vertex + 'A');
		return (1);
	}
	return (0);
}


int			exist_edge(t_al_graph *graph, int vertex1, int vertex2)
{
	t_stack stack;
	int		next_vertex;
	int		visit_flag;

	stack_init(&stack);
	
	// start vertex
	visit_vertex(graph, vertex1);
	stack_push(&stack, vertex1);
	
	while (1)
	{
		visit_flag = 0;
		
		graph->list[vertex1].cur = graph->list[vertex1].head;
		while (list_next_node(&(graph->list[vertex1]), &next_vertex))
		{
			if (graph->list[vertex1].cur->data == vertex2)
			{
				// initialize visit information before returning the function
				ft_memset(graph->visit_info, 0, sizeof(int) * graph->vertex_num);
				return (1);
			}
			
			if (visit_vertex(graph, next_vertex))
			{
				stack_push(&stack, vertex1);
				vertex1 = next_vertex;
				visit_flag = 1;
				break ;
			}
		}
		
		if (!visit_flag)
		{
			if (stack_is_empty(&stack))
				break ;
			else
				vertex1 = stack_pop(&stack);
		}
	}
	
	ft_memset(graph->visit_info, 0, sizeof(int) * graph->vertex_num);
	return (0);
}

void		restore_edge(t_al_graph *graph, int from, int to)
{
	list_insert_comp(&(graph->list[from]), to);
	list_insert_comp(&(graph->list[to]), from);
	(graph->edge_num)++;
}

void		conversion_kruskal(t_al_graph *graph)
{
	t_edge	remem_edge[32];
	t_edge	edge;
	int		edge_i;
	int		i;
	
	// repeat until forming minimum cost spanning tree
	// MST edge number + 1 = vertex number
	edge_i = -1;
	while (graph->edge_num + 1 != graph->vertex_num)
	{
		// take out edge in priority queue
		edge = delete_p_queue(&(graph->weight_info));
		// remove edge from priority queue
		remove_edge(graph, edge.vertex1, edge.vertex2);
		
		// restore edge if one vertex has no edge
		// put edge into priority queue a later
		if (!exist_edge(graph, edge.vertex1, edge.vertex2))
		{
			restore_edge(graph, edge.vertex1, edge.vertex2);
			remem_edge[++edge_i] = edge;
		}
	}
	
	// data restore
	i = -1;
	while (++i <= edge_i)
		enter_p_queue(&(graph->weight_info), remem_edge[i]);
}

void	show_graph(t_al_graph *graph)
{
	int		data;
	int		i;
	
	i = -1;
	//printf("vertex num : %d\n", graph->vertex_num);
	while (++i < graph->vertex_num)
	{
		printf("%c -> ", i + 'A');
		
		graph->list[i].cur = graph->list[i].head;  // head : starting point
		while (list_next_node(&(graph->list[i]), &data))
			printf("%c ", data + 'A');
		printf("\n");
	}
}

void		show_edge_info(t_al_graph *graph)
{
	t_edge		edge;

	while (!p_queue_is_empty(&(graph->weight_info)))
	{
		edge = delete_p_queue(&(graph->weight_info));
		printf("(%c - %c), weight : %d\n", edge.vertex1 + 'A', edge.vertex2 + 'A', edge.weight);
	}
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



// 598page. graph 
int			main(void)
{
	t_al_graph	graph;
	
	graph_init(&graph, 6);  // adjacent list graph reset

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
	show_graph(&graph);
	show_edge_info(&graph);

	free_all(&graph);
}
