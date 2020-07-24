/*                                                           */
/*  POST2IN.C  :  Convert Postfix to Infix using parse tree  */
/*                                                           */
/*                Programmed By Lee jaekyu                   */
/*                                                           */

#include <stdio.h>
#include <alloc.h>

typedef struct _node
    {
    int key;
    struct _node *left;
    struct _node *right;
    } node;

node *head, *tail;

char post[256];
char in[256];
char *i;

#define MAX  100

node *stack_node[MAX];
int top_node;

void init_stack_node(void)
    {
    top_node = -1;
    }

node *push_node(node *t)
    {
    if (top_node >= MAX - 1)
	{
	printf("\n    Stack overflow.");
	return NULL;
	}
    stack_node[++top_node] = t;
    return t;
    }

node *pop_node(void)
    {
    if (top_node < 0)
	{
	printf("\n    Stack underflow.");
	return NULL;
	}
    return stack_node[top_node--];
    }

int stack_int[MAX];
int top_int;

void init_stack_int(void)
    {
    top_int = -1;
    }

int push_int(int t)
    {
    if (top_int >= MAX - 1)
	{
	printf("\n    Stack overflow.");
	return -1;
	}
    stack_int[++top_int] = t;
    return t;
    }

int pop_int(void)
    {
    if (top_int < 0)
	{
	printf("\n    Stack underflow.");
	return -1;
	}
    return stack_int[top_int--];
    }

int top_value(void)
    {
    return stack_int[top_int];
    }

int paren(void)
    {
    int i = top_int;
    while (stack_int[i] == stack_int[top_int])
	i--;
    return top_int - i;
    }

void init_tree(void)
    {
    head = (node*)malloc(sizeof(node));
    tail = (node*)malloc(sizeof(node));
    head->left = tail;
    head->right = tail;
    tail->left = tail;
    tail->right = tail;
    }

int is_operator(int k)
    {
    return (k == '+' || k == '-' || k == '*' || k == '/') ? 1 : 0;
    }

node *make_parse_tree(char *p)
    {
    node *t;
    while (*p)
       {
       while (*p == ' ')
	   p++;
       t = (node*)malloc(sizeof(node));
       t->key = *p;
       t->left = tail;
       t->right = tail;
       if (is_operator(*p))
	   {
	   t->right = pop_node();
	   t->left = pop_node();
	   }
       push_node(t);
       p++;
       }
    return pop_node();
    }

void inorder_traverse(node *t)
    {
    int k;
    if (t != tail)
	{
	push_int('(');
	inorder_traverse(t->left);

	if (top_value() == '(' && !is_operator(t->key))
	    for (k = paren(); k > 0; k--)
		*i++ = '(';
	*i++ = t->key;
	if (top_value() == ')' && !is_operator(t->key))
	    for (k = paren(); k > 0; k--)
		*i++ = ')';

	push_int(')');
	inorder_traverse(t->right);
	}
    pop_int();
    }

void post2in(void)
    {
    init_stack_node();
    head->left = make_parse_tree(post);
    init_stack_int();
    push_int(0);   /* dummy push, else stack underflow... */
    inorder_traverse(head->left);
    }

int is_legal(char *s)
    {
    int o = 0;
    int v = 0;
    while (*s)
	{
	while (*s == ' ')   /* remove space */
	    s++;
	if (is_operator(*s))
	    o++;
	else
	    v++;
	s++;
	}
    return (v - o == 1) ? 1 : 0;   /* legal if valuable - operator == 1 */
    }

void main(void)
    {
    init_tree();
    while (1)
	{
	printf("\n Input Postfix expression -> ");
	gets(post);
	if (*post == NULL)
	    {
	    printf("\n Program ends...");
	    exit(0);
	    }
	if (!is_legal(post))
	    {
	    printf("\n Expression is not legal.");
	    continue;
	    }
	i = in;
	post2in();
	*i = NULL;   /* Terminate string */
	printf("\n Infix : %s", in);
	}
    }

