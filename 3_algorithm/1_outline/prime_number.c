#include <stdio.h>

void	get_prime(int n)
{
	int	i;

	i = 2;
	while (i * i <= n)
	{
		if (!(n % i++))
		{
			printf("%d isn't prime number!\n", n);
			return ;
		}
	}
	printf("%d is prime number!\n", n);

}

int		main(void)
{
	int	n;

	n = 1;
	while (++n < 20)
		get_prime(n);
}