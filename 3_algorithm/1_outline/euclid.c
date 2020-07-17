#include <stdio.h>

int		gcd_minus(int n1, int n2)
{
	while (n1 != n2)
	{
		if (n1 < n2)
			n2 -= n1;
		else
			n1 -= n2;
	}
	return (n1);
}

int		gcd_rest(int n1, int n2)
{
	while (n1 && n2)
	{
		if (n1 < n2)
			n2 %= n1;
		else
			n1 %= n2;
	}
	if (!n1)
		return (n2);
	if (!n2)
		return (n1);
}

int		gcd_recur(int n1, int n2)
{
	if (!n1)
		return (n2);
	if (!n2)
		return (n1);
	else
	{
		if (n1 < n2)
			return (gcd_recur(n1, n2 % n1));
		else
			return (gcd_recur(n1 % n2, n2));
	}
}

int		main(void)
{
	int		n1;
	int		n2;

	printf("num1, num2 : ");
	scanf("%d %d", &n1, &n2);
	getchar();
	while (1)
	{
		if (n1 < 0 || n2 < 0)
			printf("enter a positive number!\n");
		else
		{
			printf("gcd %d\n", gcd_minus(n1, n2));
			printf("gcd %d\n", gcd_rest(n1, n2));
			printf("gcd %d\n", gcd_recur(n1, n2));
			break ;
		}
	}
}