#include <stdio.h>

void	arr_init(char arr[][101], int size)
{
	int i;
	int j;
	
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			arr[i][j] = '.';
		arr[i][j] = '\0';
	}
	arr[i][0] = '\0';
}



void	move_up_down(char arr[][101], int size, int *x, int *y, char str)
{
	// cancel command when it goes out of scope
	if ((str == 'U' && *x == 0) || (str == 'D' && *x == size - 1))
		return ;
	
	if (arr[*x][*y] == '.')
		arr[*x][*y] = '|';
	else if (arr[*x][*y] == '-')
		arr[*x][*y] = '+';

	// move location
	if (str == 'U')
		(*x)--;
	else if (str == 'D')
		(*x)++;
	
	if (arr[*x][*y] == '.')
		arr[*x][*y] = '|';
	else if (arr[*x][*y] == '-')
		arr[*x][*y] = '+';
}

void	move_left_right(char arr[][101], int size, int *x, int *y, char str)
{
	// cancel command when it goes out of scope
	if ((str == 'L' && *y == 0) || (str == 'R' && *y == size - 1))
		return ;
	
	if (arr[*x][*y] == '.')
		arr[*x][*y] = '-';
	else if (arr[*x][*y] == '|')
		arr[*x][*y] = '+';	
	
	// move location
	if (str == 'L')
		(*y)--;
	else if (str == 'R')
		(*y)++;
		
	if (arr[*x][*y] == '.')
		arr[*x][*y] = '-';
	else if (arr[*x][*y] == '|')
		arr[*x][*y] = '+';
}

void	move_machine(char arr[][101], int size, char *str)
{
	int	i;
	int	x;
	int	y;
	
	i = -1;
	x = 0;
	y = 0;
	while(str[++i])
	{
		if (str[i] == 'U' || str[i] == 'D')
			move_up_down(arr, size, &x, &y, str[i]);
		else if (str[i] == 'L' || str[i] == 'R')
			move_left_right(arr, size, &x, &y, str[i]);
	}
}



void	print_drawing(char arr[][101])
{
	int	i;
	
	i = -1;
	while(arr[++i][0])
		printf("%s\n", arr[i]);
}



int		main(void)
{
	char	arr[101][101];
	char	str[1000];
	int		size;

	scanf("%d", &size);
	getchar();  // remove enter in buffer
	
	arr_init(arr, size);  // initialize all array elements to '.'
	
	scanf("%s", str);
	getchar();
	
	move_machine(arr, size, str);
	print_drawing(arr);
}
