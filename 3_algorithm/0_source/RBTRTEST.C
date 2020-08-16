/*                                                           */
/*  RBTRTEST.C  :  Red-Black Tree libabray test              */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <graphics.h>
#include "rbtrsrch.h"
#include "hardcopy.h"

node *head;

#define DY  50

void draw_node(node *p, int x1, int x2, int y, int mode,
		void (*fnode)(void*,char*))
    {
    char content[25];
	if (p != NULL)
	{
	draw_node(p->left, x1, (x1+x2)/2, y+DY, mode, fnode);
	fnode(p+1, content);
	if (p->red) setcolor(LIGHTRED);
	else setcolor(WHITE);
	fillellipse((x1+x2)/2, y,
		    textheight(content)/2+5, textheight(content)/2+5);
	outtextxy((x1+x2)/2, y-2, content);
	if (p->red)
	    {
	    ellipse((x1+x2)/2, y, 0, 360,
		textheight(content)/2+2, textheight(content)/2+2);
	    ellipse((x1+x2)/2, y, 0, 360,
		textheight(content)/2+4, textheight(content)/2+4);
	    }
	setcolor(WHITE);
	draw_node(p->right, (x1+x2)/2, x2, y+DY, mode, fnode);
	}
    else if (mode & TAIL)
	{
	fillellipse((x1+x2)/2, y, 3, 3);
	ellipse((x1+x2)/2, y, 0, 360, 3, 3);
	}
    }

void draw_link(node *p, int x1, int x2, int y, int mode)
    {
    if (p != NULL)
	{
	lineto((x1+x2)/2, y);
	draw_link(p->left, x1, (x1+x2)/2, y+DY, mode);
	moveto((x1+x2)/2, y);
	draw_link(p->right, (x1+x2)/2, x2, y+DY, mode);
	lineto((x1+x2)/2, y);
	}
    else if (mode & TAIL)
	{
	lineto((x1+x2)/2, y);
	moveto((x1+x2)/2, y);
	}
    }

void rb_draw(node *p, int mode, void (*fnode)(void*,char*))
    {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\tc\\bgi");
    if (graphresult() != grOk)
	{
	printf("\n Graphic system error !");
	return;
	}
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setfillstyle(0, BLACK);
    moveto(getmaxx()/2, 10);
    if (mode & LINK)
	draw_link(p, 7, getmaxx()-7, 15, mode);
    if (mode & NODE)
	draw_node(p, 7, getmaxx()-7, 15, mode, fnode);
    wait_hardcopy(LPT1);
    closegraph();
    }

int intcmp(const void *a, const void *b)
    {
    return *(int*)a - *(int*)b;
    }

void prnode(void *key, int red)
    {
    if (red)
	printf("%c\n", tolower(*(int*)key));
    else
	printf("%c\n", toupper(*(int*)key));
    }

void grnode(void *key, char *s)
    {
    s[0] = *(int*)key;
    s[1] = NULL;
    }

void interpret(node *a, size_t *np)
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
	    case 'I' : if (rbtr_insert(&k,a,np,2,intcmp) == NULL)
			   printf("\n   Error : Out of memory.");
		       else
			   printf("\n   Successful insert.");
		       break;
	    case 'd' :
	    case 'D' : if (rbtr_delete(&k,a,np,2,intcmp) == NULL)
			   printf("\n   Error : Table empty or can't find.");
		       else
			   printf("\n   Successful delete.");
		       break;
	    case 's' :
	    case 'S' : if (rbtr_search(&k,a,np,2,intcmp) == NULL)
			   printf("\n   Error : Can'f find that key");
		       else
			   printf("\n   Ok! find ");
		       break;
	    case 'l' :
	    case 'L' : rbtr_list(a->left, prnode);
		       break;
	    case 'o' :
            case 'O' : printf("\n");
		       rbtr_sort(a->left, prnode);
		       break;
	    case 'g' :
	    case 'G' : rb_draw(a->left, NODE|LINK|TAIL, grnode);
		       break;
	    }
	printf("  n = %d", *np);
	}
    }

void main(void)
    {
    int *table;
    size_t nitem = 0;
    init_tree(&head);
    interpret(head, &nitem);
    rbtr_deleteall(head, &nitem);
    }
