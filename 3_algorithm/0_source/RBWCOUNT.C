/*                                                           */
/*  RBWCOUNT.C  :  Word counting using Red-Black tree        */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloc.h>
#include <ctype.h>
#include <bios.h>
#include "rbtrsrch.h"

node *head;

struct wcount
    {
    int count;
    char word[20];
    };

const char delim[] = " \t\r\n,:\"'!~@#$%^&*()-_=+\\|<>.?/[]{};";

int wcount_cmp(const void *a, const void *b)
    {
    return strcmp(((struct wcount*)a)->word, ((struct wcount*)b)->word);
    }

void print_wcount(void *a, int red)
    {
    printf("%s : %d\n", ((struct wcount*)a)->word,
                        ((struct wcount*)a)->count);
    }

void make_str(void *a, char *s)
    {
    strcpy(s, ((struct wcount*)a)->word);
    }

void main(int argc, char *argv[])
    {
    size_t nitem = 0;
    char *tok;
    FILE *fp;
    char str[256];
    struct wcount wc, *wcp;
    int i;

    if (argc < 2)
        {
        printf("\n Usage : wcount [filename]");
        exit(1);
        }
    init_tree(&head);
    if ((fp = fopen(argv[1], "rt")) == NULL)
        {
        printf("\n Can't find that file.");
        exit(1);
        }
    fgets(str, 255, fp);
    while (!feof(fp))
        {
        tok = strtok(str, delim);
        while (tok)
            {
            for (i = 0; i < strlen(tok); i++) tok[i] = tolower(tok[i]);
            strcpy(wc.word, tok);
	    wcp = rbtr_search(&wc, head, &nitem, sizeof(wc), wcount_cmp);
	    if (wcp == NULL)
		{
		wc.count = 1;
		rbtr_insert(&wc, head, &nitem, sizeof(wc), wcount_cmp);
		}
            else
                (wcp->count)++;
            tok = strtok(NULL, delim);
            }
        fgets(str, 256, fp);
	}
    printf("\n");
    rbtr_sort(head->left, print_wcount);
    bioskey(0);
    printf("\n");
    rbtr_list(head->left, print_wcount);
    bioskey(0);
    rbtr_draw(head->left, LINK|NODE|TAIL, make_str);
    rbtr_deleteall(head, &nitem);
    }






