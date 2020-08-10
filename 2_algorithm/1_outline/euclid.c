#include <stdio.h>
#include <time.h>

#define	REPEAT	10000

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
	else
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
	long	start;
	long	finish;
	int		n1;
	int		n2;
	int		gcd;
	int		i;

	printf("num1, num2 : ");
	scanf("%d %d", &n1, &n2);
	getchar();

	if (n1 < 0 || n2 < 0)
	{
		printf("enter a positive number!\n");
		return (0);
	}
	printf("--------------------\n\n");
	start = clock();;
	i = -1;
	while (++i < REPEAT)
		gcd = gcd_minus(n1, n2);
	finish = clock();;
	printf("minus gcd %d\n", gcd_minus(n1, n2));
	printf("time taken : %ld\n\n", finish - start);

	start = clock();;
	i = -1;
	while (++i < REPEAT)
		gcd = gcd_rest(n1, n2);
	finish = clock();;
	printf("rest gcd %d\n", gcd_rest(n1, n2));
	printf("time taken : %ld\n\n", finish - start);;

	start = clock();;
	i = -1;
	while (++i < REPEAT)
		gcd = gcd_recur(n1, n2);
	finish = clock();;
	printf("recursion gcd %d\n", gcd_recur(n1, n2));
	printf("time taken : %ld\n\n", finish - start);
}
