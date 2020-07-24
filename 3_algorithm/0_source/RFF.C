/*                                                           */
/*  RFF.C    :   Recursive find file utility                 */
/*                                                           */
/*                Programmed By Lee jaekyu                   */
/*                                                           */

#include <stdio.h>
#include <dos.h>
#include <dir.h>

#define ALL_ATTRIB  FA_RDONLY|FA_HIDDEN|FA_SYSTEM|FA_LABEL|FA_DIREC|FA_ARCH

void findfile(char *mask)
    {
    char path[80];
    struct ffblk info;
    if (findfirst(mask, &info, ALL_ATTRIB) == 0)
	{
	do
	    {
	    getcwd(path, 80);
	    printf("\n%s%s%s", path,
			       strlen(path) == 3 ? "" : "\\",
			       info.ff_name);
	    } while (findnext(&info) == 0);
	}
    if (findfirst("*", &info, FA_DIREC) == 0)
	{
	do
	    {
	    if (info.ff_name[0] == '.' || info.ff_attrib != FA_DIREC)
		continue;
	    chdir(info.ff_name);
	    findfile(mask);
	    chdir("..");
	    } while (findnext(&info) == 0);
	}
    }

int main(int argc, char *argv[])
    {
    char curpath[30];
    if (argc < 2)
	{
	printf("\nUsage : RFF <file mask>");
	return 0;
	}
    getcwd(curpath, 30);
    chdir("\\");
    findfile(argv[1]);
    chdir(curpath);
    return 0;
    }
