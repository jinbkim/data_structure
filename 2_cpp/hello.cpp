#include <iostream>

void	ft_swap(int *n1, int *n2)
{
	int	temp;
	
	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void	ft_swap(char *n1, char *n2)
{
	char	temp;
	
	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void	ft_swap(double *n1, double *n2)
{
	double	temp;
	
	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

int		main(void)
{
	int 	num1 = 1;
	int 	num2 = 2;
	char	word1 = 'A';
	char	word2 = 'B';
	double	real1 = 1.1;
	double	real2 = 2.2;
	
	std::cout<<num1<<' '<<num2<<std::endl;
	ft_swap(&num1, &num2);
	std::cout<<num1<<' '<<num2<<std::endl;

	std::cout<<word1<<' '<<word2<<std::endl;
	ft_swap(&word1, &word2);
	std::cout<<word1<<' '<<word2<<std::endl;
	
	std::cout<<real1<<' '<<real2<<std::endl;
	ft_swap(&real1, &real2);
	std::cout<<real1<<' '<<real2<<std::endl;

}
