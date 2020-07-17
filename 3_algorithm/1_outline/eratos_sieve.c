#include <stdio.h>

#define	MAX	20

void	find_prime(char *ar)
{
	int	i;
	int j;

	i = 1;
	while (++i < MAX)
	{
		j = 1;
		while (++j * i < MAX)
			ar[i * j] = '1';
	}
}

void	show_prime(char *ar)
{
	int i;

	printf("----- prime number less than %d -----\n", MAX);
	i = 1;
	while (++i < MAX)
		if (ar[i] != '1')
			printf("%d ", i);
	printf("\n");
}



int		main(void)
{
	char	arr[MAX];

	find_prime(arr);
	show_prime(arr);
}