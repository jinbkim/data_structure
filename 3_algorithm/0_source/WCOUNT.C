/*                                                           */
/*  WCOUNT.C  :  Word counting using Binary tree search      */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloc.h>
#include <ctype.h>
#include <bios.h>
#include "btrsrch.h"

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

void print_wcount(void *a)
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
            wcp = btv_search(&wc, head, &nitem, sizeof(wc), wcount_cmp);
            if (wcp == NULL)
                {
                wc.count = 1;
                btv_insert(&wc, head, &nitem, sizeof(wc), wcount_cmp);
                }
            else
                (wcp->count)++;
            tok = strtok(NULL, delim);
            }
        fgets(str, 256, fp);
	}
    printf("\n");
    btv_sort_list(head->left, print_wcount);
    bioskey(0);
    printf("\n");
    btv_list(head->left, print_wcount);
    bioskey(0);
    btv_draw(head->left, make_str, LINK|NODE);

    btv_balance(head, &nitem, sizeof(wc));
    btv_list(head->left, print_wcount);
    bioskey(0);
    btv_draw(head->left, make_str, LINK|NODE|TAIL);
    btv_deleteall(head, &nitem);
    }






