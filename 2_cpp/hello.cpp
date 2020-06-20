#include <iostream>
#include <cstdio>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;



int		main(void)
{
	char	str1[200] = "hello";
	char	str2[100];
	//int size = strlen(str1);
	strcat(str1, " world!");
	printf("str1 : %s\n", str1);

	strcpy(str2, str1);
	printf("str1 : %s\n", str1);

/*
	if (!strcmp(str1, str2))
		printf("same!\n");
	else
		printf("diff\n");
	printf("str1 : %s\n", str1);
	printf("str2 : %s\n", str2);
*/
} 
