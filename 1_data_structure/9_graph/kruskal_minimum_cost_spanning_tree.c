#include <stdio.h>
#include <stdlib.h>

#define	HEAP_SIZE	100
#define STACK_LEN	100

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

typedef	int	stack_data;

typedef struct	s_stack
{
	stack_data	stack_arr[STACK_LEN];  // array type stack
	int			top_idx;  // top index of stack
}				t_stack;



void		list_init(t_list *list, sort_func f)
{
	list->head = (t_node *)malloc(sizeof(t_node));  // make dummy node
	list->head->next = NULL;
	list->f = f;
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

list_data	list_remove(t_list *list)
{
	t_node		*remem_node;
	list_data	remem_data;

	remem_node = list->cur;  // remember node to be deleted
	remem_data = list->cur->data;  // remember data to be deleted
	
	// connection before node and next node
	list->cur->before->next = list->cur->next;
	if (list->cur->next)  // if next node exist,
		list->cur->next->before = list->cur->before;
	
	// current node reset
	if (list->cur->before != list->head)  // if before node is not head node,
		list->cur = list->cur->before;
	else if (list->cur->next)  // if next node is exist,
		list->cur = list->cur->next;
	
	free(remem_node);
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
	if (list->cur->next == NULL)  // if next node is not exist
		return (0);
	list->cur = list->cur->next;
	*data = list->cur->data;
	return (1);
}



void		p_queue_init(t_p_queue *pq, priority_comp f)
{
	pq->data_num = 0;
	pq->f = f;
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

int			get_high_priority_child_idx(t_p_queue *pq, int idx)
{
	if (idx * 2 > pq->data_num)  // if child node is not exist
		return (0);
	else if (idx * 2 == pq->data_num)  // if lef child node is last node
		return (idx * 2);
	else
	{
		// if left child node has a higher priority than right child node,
		if (pq->f(pq->heap_arr[idx * 2], pq->heap_arr[idx * 2 + 1]) < 0)
			return (idx * 2 + 1);
		else
			return (idx * 2);
	}
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
		if (pq->f(last_elem, pq->heap_arr[child_i]) > 0)  // if you find good location
			break ;
		pq->heap_arr[parent_i] = pq->heap_arr[child_i];
		parent_i = child_i;
	}
	
	pq->heap_arr[parent_i] = last_elem;
	return (remem_data);
}

int			p_queue_is_empty(t_p_queue *pq)
{
	if (pq->data_num)
		return (0);
	return (1);
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
	int		remem_idx;
	
	if (stack_is_empty(stack))  // if stack is empty
	{
		printf("stack is empty!\n");
		exit (-1);
	}
	remem_idx = (stack->top_idx)--;
	return (stack->stack_arr[remem_idx]);
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

int			left_data_is_big(int d1, int d2)
{
	if (d1 > d2)
		return (1);
	return (0);
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

int			visit_vertex(t_al_graph *graph, int visit)
{
	if (!graph->visit_info[visit])
	{
		graph->visit_info[visit] = 1;
		//printf("%c ", visit + 'A');
		return (1);
	}
	return (0);
}

int			exist_edge(t_al_graph *graph, int vertex1, int vertex2)
{
	t_stack stack;
	t_node	*cur;
	int		next_vertex;
	int		visit_flag;

	stack.top_idx = -1;  // stack reset
	
	// start vertex
	visit_vertex(graph, vertex1);
	stack_push(&stack, vertex1);

	while (1)
	{
		visit_flag = 0;
		
		cur = graph->list[vertex1].head;  // head : starting point
		while (cur->next)
		{
			cur = cur->next;
			next_vertex = cur->data;
			if (cur->data == vertex2)
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
	list_insert(&(graph->list[from]), to);
	list_insert(&(graph->list[to]), from);
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
		edge = delete_p_queue(&(graph->w_info_q));
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
		enter_p_queue(&(graph->w_info_q), remem_edge[i]);
}

void		show_graph(t_al_graph *graph)
{
	t_node	*cur;
	int		i;
	
	i = -1;
	while (++i < graph->vertex_num)
	{
		printf("%c -> ", i + 'A');
		cur = graph->list[i].head;  // head : starting point
		while (cur->next)
		{
			cur = cur->next;  // current node reset
			printf("%c", cur->data + 'A');
			if (cur->next)
				printf(", ");
		}
		printf("\n");
	}
}

void		show_edge_info(t_al_graph *graph)
{
	t_edge		edge;

	while(!p_queue_is_empty(&(graph->w_info_q)))
	{
		edge = delete_p_queue(&(graph->w_info_q));
		printf("(%c - %c), weight : %d\n", edge.vertex1 + 'A', edge.vertex2 + 'A', edge.weight);
	}
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
	
	show_graph(&graph);
	show_edge_info(&graph);
	free_all(&graph);
}
