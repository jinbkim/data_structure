/*                                                           */
/*  TVIEW.C  :  Text viewer  , application of dll            */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */

#include <conio.h>
#include <stdio.h>
#include <bios.h>
#include "key.h"

typedef struct _line
    {
    char *buf;
    struct _line *prev;
    struct _line *next;
    } line;

line *head, *tail;
int total, now;
char filename[13];

void init_line(void)
    {
    head = (line*)malloc(sizeof(line));
    tail = (line*)malloc(sizeof(line));
    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
    }

void load_file(void)
    {
    FILE *fp;
    char buf[256];
    line *t;
    if ((fp = fopen(filename, "rt")) == NULL)
        {
        printf("\n Error : Can't read that file.");
        exit(1);
        }
    total = 0;
    printf("\n File loading...");
    while (!feof(fp))
        {
        fgets(buf, 255, fp);
        if (strlen(buf) > 80)
            buf[80] = 0;
        if ((t = (line*)malloc(sizeof(line))) == NULL)
            {
            printf("\n Error : Out of Memory.");
            exit(1);
            }
        if ((t->buf = (char*)malloc(strlen(buf))) == NULL)
            {
            printf("\n Error : Out of Memory.");
            exit(1);
            }
        strcpy(t->buf, buf);
        t->prev = tail->prev;
        t->next = tail;
        tail->prev->next = t;
        tail->prev = t;
        total++;
        }
    fclose(fp);
    }

void move_line(int d, line **t)
    {
    if (d < 0)
        while (d++ != 0 && (*t)->prev != head)
            {
            *t = (*t)->prev;
            now--;
            }
    else
        while (d-- != 0 && (*t)->next != tail)
            {
            *t = (*t)->next;
            now++;
            }
    }

void show_header(void)
    {
    textattr((LIGHTGRAY<<4) | BLACK);
    gotoxy(1, 1);
    cprintf(" TVIEW : %-12s      Loc : %6d of %6d    By Lee jaekyu     ",
             filename, now, total);
    textattr((BLACK<<4) | LIGHTGRAY);
    }

void show_page(line *t)
    {
    int i = 0;
    clrscr();
    show_header();
    gotoxy(1, 2);
    while (i++ < 23 && t != tail)
        {
        cprintf("%-80s\r", t->buf);
        t = t->next;
        }
    }

void key_proc(void)
    {
    line *t;
    int key;
    now = 1;
    t = head->next;
    show_page(t);
    while ((key = bioskey(0)) != ESC)
        {
        switch (key)
            {
            case PGUP : move_line(-23, &t);
                        show_page(t);
                        break;
            case PGDN : move_line(+23, &t);
                        show_page(t);
                        break;
            }
        }
    clrscr();
    }

void main(int argc, char *argv[])
    {
    line *t;
    if (argc < 2)
        {
        printf("\nUsage : TVIEW <filename.ext>");
        exit(0);
        }
    strcpy(filename, argv[1]);
    init_line();
    load_file();
    key_proc();
    printf("\nProgram ends...");
    }



