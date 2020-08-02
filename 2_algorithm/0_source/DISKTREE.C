/*                                                           */
/*  DISKTREE   :  Make disk tree information                 */
/*                                                           */
/*                Programmed By Lee jaekyu                   */
/*                                                           */

#include <stdio.h>
#include <dos.h>
#include <dir.h>

FILE *fp;

void scan(int depth)
    {
    struct ffblk info;
    if (findfirst("*", &info, FA_DIREC) == 0)
	{
	do
	    {
	    if (info.ff_name[0] == '.' || info.ff_attrib != FA_DIREC)
		continue;
	    fprintf(fp, "%-4d%-8s", depth, info.ff_name);
	    depth++;
	    chdir(info.ff_name);
	    scan(depth);
	    chdir("..");
	    depth--;
	    } while (findnext(&info) == 0);
	}
    }

void make_tree_info(void)
    {
    fprintf(fp, "%-4d%-8s", 0, "\\");
    scan(1);
    }

void print_tree(void)
    {
    int depth;
    char dir[9];
    if ((fp = fopen("TREEINFO.DAT", "r")) == NULL)
	{
	printf("\nDisk write error!");
	return;
	}
    printf("\n");
    while (!feof(fp))
	{
	fscanf(fp, "%4d%8s", &depth, dir);
	while (depth-- > 0)
	    printf("  ");
	printf("%-8s\n", dir);
	dir[0] = NULL;
	}
    fclose(fp);
    }

int main(void)
    {
    char curpath[30];
    if ((fp = fopen("TREEINFO.DAT", "w")) == NULL)
	{
	printf("\nDisk write error!");
	return 1;
	}
    getcwd(curpath, 30);
    chdir("\\");
    make_tree_info();
    chdir(curpath);
    fclose(fp);
    print_tree();
    return 0;
    }