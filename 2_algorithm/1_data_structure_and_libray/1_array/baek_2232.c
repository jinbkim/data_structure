#include <stdio.h>

void	mine_input(int *mine, int num)
{
	int i;
	int	power;
	
	i = -1;
	while(++i < num)
	{
		scanf("%d", &power);
		getchar();
		mine[i] = power;
	}
}



int		find_max_i(int *mine, int num)
{
	int i;
	int	max_i;
	
	i = 0;
	max_i = 0;
	while(++i < num)
		if (mine[max_i] < mine[i])
			max_i = i;

	return (max_i);
}

void	left_mine_boom(int *mine, int max_i)
{
	int	right_mine;
	
	right_mine = mine[max_i];
	while (0 < max_i && mine[max_i - 1] < right_mine)
	{
		right_mine = mine[max_i - 1];
		mine[max_i - 1] = 0;
		max_i--;
	}
}

void	right_mine_boom(int *mine, int max_i, int num)
{
	int	left_mine;
	
	left_mine = mine[max_i];
	while(max_i < num - 1 && mine[max_i + 1] < left_mine)
	{
		left_mine = mine[max_i + 1];
		mine[max_i + 1] = 0;
		max_i++;
	}
}

void	mine_boom(int *mine, char *boom, int num)
{
	int	max_i;
	int i;

	i = -1;
	while (++i < num)
	{
		max_i = find_max_i(mine, num);
		if (mine[max_i] == 0)
			break ;
		left_mine_boom(mine, max_i);  // boom mine to the left
		right_mine_boom(mine, max_i, num);  // boom mine to the right
		mine[max_i] = 0;
		boom[max_i] = '1';  // popped mine check
	}
}



void	print_mine(char *boom, int num)
{
	int i;
	
	i = -1;
	while(++i < num)
		if (boom[i] == '1')
			printf("%d\n", i + 1);
}



int		main(void)
{
	char	boom[50000];
	int		mine[50000];
	int		num;

	scanf("%d", &num);
	getchar();  // remove enter in buffer

	mine_input(mine, num);
	mine_boom(mine, boom, num);
	print_mine(boom, num);
}
