/*                                                           */
/*  EBTRTEST.C  :  External B-tree test                      */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <graphics.h>
#include "hardcopy.h"
#include "extbtree.h"

int intcmp(const void *a, const void *b)
    {
    return *(int*)a - *(int*)b;
    }

void sort_prt(void *a)
    {
    printf("\n%c", *(int*)a);
    }

void list_prt(void *a, int flag)
    {
    printf("%c", *(int*)a);
    if (flag) printf("\n");
    }

long getdw(FILE *fp, long pos);

void dump_file(FILE *fp)
    {
    int a;
    int i = 0;
    rewind(fp);
    while (!feof(fp))
	{
	printf("%02x ", fgetc(fp));
	if (++i % 8 == 0)
	    {
	    printf("  ");
	    }
	if (i == 16)
	    {
	    printf("\n");
	    i = 0;
	    }
	}
    }

void view_file(FILE *fp, size_t *np)
    {
    int i, a, n;
    long l;
    rewind(fp);
    n = getw(fp);
    printf("\n N = %d", n);
    n = *np;
    l = getdw(fp, -1L);
    printf("    %ld", l);
    while (!feof(fp))
	{
	printf("\n");
	printf("Pos %-5ld,  ", ftell(fp));
	a = getw(fp);
	if (feof(fp)) break;
	printf("n = %2d    -->   ", a);
	for (i = 0; i <= M*2+1; i++)
	    {
	    l = getdw(fp, -1L);
	    printf("%-5ld", l);
	    }
	printf(" : ");
	for (i = 0; i < M*2+1; i++)
	    {
	    a = getw(fp);
	    printf("%c:%d,  ", a, a);
	    }
	}
    }

#define DY  50

Bnode *tnode;
char content[21];

long load_Bnode(Bnode *, FILE *, size_t, long);

void _draw_node(FILE *fp, long ptr, int x1, int x2, int y)
    {
    int i;
    char temp[3];
    load_Bnode(tnode, fp, 2, ptr);
    if (tnode->n > 0)
	{
	content[0] = 0;
	strcat(content, (char*)(tnode+1));
	for (i = 1; i < tnode->n; i++)
	    {
	    strcat(content, " ");
	    strcat(content, (char*)(tnode+1)+i*2);
	    }
	fillellipse((x1+x2)/2, y, textwidth(content)/2+7,
				  textheight(content)/2+5);
	outtextxy((x1+x2)/2, y-2, content);
	for (i = 0; i <= tnode->n; i++)
	    {
	    _draw_node(fp, tnode->ptr[i], i*(x2-x1)/(tnode->n+1)+x1,
		       (i+1)*(x2-x1)/(tnode->n+1)+x1, y+DY);
	    load_Bnode(tnode, fp, 2, ptr);
	    }
	}
    }

void _draw_link(FILE *fp, long ptr, int x1, int x2, int y)
    {
    int i;
    load_Bnode(tnode, fp, 2, ptr);
    if (tnode->n > 0)
	{
	for (i = 0; i <= tnode->n; i++)
	    {
	    lineto((x1+x2)/2, y);
	    _draw_link(fp, tnode->ptr[i], i*(x2-x1)/(tnode->n+1)+x1,
			  (i+1)*(x2-x1)/(tnode->n+1)+x1, y+DY);
	    load_Bnode(tnode, fp, 2, ptr);
	    moveto((x1+x2)/2, y);
	    }
	}
    }

void draw_file(FILE *fp)
    {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    if (graphresult() != grOk)
	{
	printf("\n Graphic system error !");
	return;
	}
    tnode = (Bnode*)malloc(sizeof(Bnode)+2*(M*2+1));
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setfillstyle(0, BLACK);
    moveto(getmaxx()/2, 15);
    load_Bnode(tnode, fp, 2, 6);
    _draw_link(fp, tnode->ptr[0], 10, getmaxx()-10, 15);
    load_Bnode(tnode, fp, 2, 6);
    _draw_node(fp, tnode->ptr[0], 10, getmaxx()-10, 15);
    wait_hardcopy(LPT1);
    closegraph();
    }

void interpret(FILE *fp, size_t *np)
    {
    char command[2];
    char key[2];
    int k;
    void *p;
    while (command[0] != 'q')
        {
        printf("\nInput command ->");
        scanf("%1s", command);
        scanf("%1s", &key);
        k = (int)key[0];
        switch (command[0])
            {
            case 'i' :
	    case 'I' : if (Btree_insert(fp, &k, np, 2, intcmp) == NULL)
			   printf("\n   Error : Disk full or Equal key");
		       else
			   printf("\n   Successful insert.");
		       break;
	    case 'd' :
	    case 'D' : if (Btree_delete(fp, &k, np, 2, intcmp) == NULL)
			   printf("\n   Error : Table empty or can't find.");
		       else
			   printf("\n   Successful delete.");
		       break;
	    case 's' :
	    case 'S' : if (Btree_search(fp, &k, np, 2, intcmp) == NULL)
			   printf("\n   Error : Can'f find that key");
		       else
			   printf("\n   Ok! find ");
		       break;
	    case 'l' :
	    case 'L' : Btree_list(fp, 2, list_prt);
		       break;
	    case 'o' :
            case 'O' : printf("\n");
		       Btree_sort(fp, 2, sort_prt);
		       break;
	    case 'v' :
	    case 'V' : view_file(fp, np);
		       break;
	    case 'h' :
	    case 'H' : dump_file(fp);
		       break;
	    case 'g' :
	    case 'G' : draw_file(fp);
		       break;
	    }
	printf("  n = %d", *np);
	}
    }

void main(void)
    {
    size_t num;
    FILE *fp;
    fp = init_Btree("btree.dat", &num, sizeof(int));
    interpret(fp, &num);
    close_Btree(fp, &num);
    }


