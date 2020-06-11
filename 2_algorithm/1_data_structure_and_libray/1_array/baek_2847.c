#include <stdio.h>

void	level_input(int	*level, int count)
{
	int value;
	int i;
	
	i = -1;
	while (++i <count)
	{
		scanf("%d", &value);
		getchar();
		level[i] = value;
	}
}



int		make_ascending(int *level, int count)
{
	int result;
	
	result = 0;
	while(--count > 0)
		while(level[count] <= level[count - 1] && ++result)
			level[count - 1]--;

	return (result);
}



int		main(void)
{
	int	level[100];
	int	count;

	scanf("%d", &count);
	getchar();  // remove enter in buffer
	
	level_input(level, count);
	printf("%d\n", make_ascending(level, count));
}
