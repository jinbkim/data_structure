/*                                                           */
/*  TREE2.C  :   Make parse tree & traverse by Nonrecursive  */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
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

#define MAX  100

node *stack[MAX];
int top;

void init_stack(void)
    {
    top = -1;
    }

node *push(node *t)
    {
    if (top >= MAX - 1)
	{
	printf("\n    Stack overflow.");
	return NULL;
	}
    stack[++top] = t;
    return t;
    }

node *pop(void)
    {
    if (top < 0)
	{
	printf("\n    Stack underflow.");
	return NULL;
	}
    return stack[top--];
    }

int is_stack_empty(void)
    {
    return (top == -1);
    }

node *queue[MAX];
int front, rear;

void init_queue(void)
    {
    front = rear = 0;
    }

node *put(node *k)
    {
    if ((rear + 1) % MAX == front)   /* queue is full */
        {
        printf("\n    Queue overflow.");
        return NULL;
        }
    queue[rear] = k;
    rear = ++rear % MAX;
    return k;
    }

node *get(void)
    {
    node *i;
    if (front == rear)   /* queue is empty */
        {
        printf("\n    Queue underflow.");
        return NULL;
        }
    i = queue[front];
    front = ++front % MAX;
    return i;
    }

int is_queue_empty(void)
    {
    return (front == rear);
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
    return (k == '+' || k == '-' || k == '*' || k == '/');
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
	   t->right = pop();
	   t->left = pop();
	   }
       push(t);
       p++;
       }
    return pop();
    }

int is_legal(char *s)
    {
    int f = 0;
    while (*s)
	{
	while (*s == ' ')   /* remove space */
	    s++;
	if (is_operator(*s))
	    f--;
	else
	    f++;
        if (f < 1) break;
	s++;
	}
    return (f == 1);   /* legal if valuable - operator == 1 */
    }

void visit(node *t)
    {
    printf("%c  ", t->key);
    }

void preorder_traverse(node *t)
    {
    init_stack();
    push(t);
    while (!is_stack_empty())
        {
        t = pop();
        if (t != tail)
            {
            visit(t);
            push(t->right);
            push(t->left);
            }
        }
    }

void inorder_traverse(node *t)
    {
    int done = 0;
    init_stack();
    while (!done)
        {
        while (t != tail)
            {
            push(t);
            t = t->left;
            }
        if (!is_stack_empty())
            {
            t = pop();
            visit(t);
            t = t->right;
            }
        else
            done = 1;
        }
    }

void postorder_traverse(node *t)
    {
    int done = 0;
    node *s;
    init_stack();
    while (!done)
        {
        while (t != tail)
            {
            push(t);
            t = t->left;
            }
        while (!is_stack_empty())
            {
            s = t;
            t = pop();
            if (t->right != tail)
                {
                if (t->right == s)
                    visit(t);
                else
                    {
                    push(t);
                    t = t->right;
                    break;
                    }
                }
            else
                visit(t);
            }
        if (is_stack_empty())
            done = 1;
        }
    }

void levelorder_traverse(node *t)
    {
    put(t);
    while (!is_queue_empty())
        {
        t = get();
            visit(t);
        if (t->left != tail)
            put(t->left);
        if (t->right != tail)
            put(t->right);
        }
    }

void main(void)
    {
    char post[256];
    init_stack();
    init_queue();
    init_tree();
    while (1)
	{
	printf("\n\nInput Postfix expression -> ");
	gets(post);
	if (*post == NULL)
	    {
	    printf("\n Program ends...");
	    exit(0);
	    }
	if (!is_legal(post))
	    {
	    printf("\nExpression is not legal.");
	    continue;
	    }

	head->right = make_parse_tree(post);

        printf("\nPreorder   traverse -> ");
        preorder_traverse(head->right);

        printf("\nInorder    traverse -> ");
        inorder_traverse(head->right);

        printf("\nPostorder  traverse -> ");
        postorder_traverse(head->right);

        printf("\nLevelorder traverse -> ");
        levelorder_traverse(head->right);
	}
    }

