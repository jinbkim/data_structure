#include <stdio.h>
#include <stdlib.h>

typedef	struct	s_info
{
	char		name[101];
	int			age;
	int			order;
}				t_info;



t_info	**info_input(int num)
{
	t_info	**mans;
	int		i;
	
	mans = (t_info **)malloc(sizeof(t_info *) * (num + 1));
	i = -1;
	while(++i < num + 1)
	{
		mans[i] = (t_info *)malloc(sizeof(t_info));
		mans[i]->order = i;
	}
	i = -1;
	while(++i < num)
	{
		scanf("%d %s", &(mans[i]->age), mans[i]->name);
		getchar();
	}
	return (mans);
}



void	ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int		median_pivot(t_info **mans, int left, int right)
{
	int mid = (left + right) / 2;
	int	example[] = {left, mid, right};
	
	if (mans[example[1]]->age < mans[example[0]]->age)
		ft_swap(&example[1], &example[0]);
	if (mans[example[2]]->age < mans[example[1]]->age)
		ft_swap(&example[2], &example[1]);
	if (mans[example[1]]->age < mans[example[0]]->age)
		ft_swap(&example[1], &example[0]);
	return (example[1]);
}

void	ft_swap2(t_info **man1, t_info **man2)
{
	t_info	*temp;
	
	temp = *man1;
	*man1 = *man2;
	*man2 = temp;
}

int		partition(t_info **mans, int left, int right)
{
	int		pivot_idx;
	int		pivot;
	int		low;
	int		high;
	

	pivot_idx = median_pivot(mans, left, right);  // store median index
	printf("pivot idx : %d\n", pivot_idx);
	pivot = mans[pivot_idx]->age;
	low	= left + 1;
	high = right;
	ft_swap2(&mans[pivot_idx], &mans[left]);  // move pivot to left
	
	while (low <= high)
	{
		// keeping low <= high, increase low 
		// until we find low value bigger than pivot
		while (low <= right && mans[low]->age < pivot)
		{
			printf("low : %d\n", low);
			//if (mans[low]->age == pivot && mans[low]->order < mans[pivot_idx]->order)
				//break ;
			low++;
		}
		if (mans[low]->age == pivot && mans[low]->order < mans[pivot_idx]->order)
				break ;
		// keeping pivot < high, decrease high
		// until we find high value smaller than pivot
		while (left < high && pivot < mans[high]->age)
		{
			printf("high : %d\n", high);
			//if (mans[high]->age == pivot && mans[pivot_idx]->order < mans[high]->order)
				//break ;
			high--;
		}
		if (mans[high]->age == pivot && mans[pivot_idx]->order < mans[high]->order)
				break ;
		if (low <= high)  // change location if not crossed
			ft_swap2(&mans[low], &mans[high]);
	}
	ft_swap2(&mans[left], &mans[high]);
	return (high);
}

void	quick_sort_mans(t_info **mans, int left, int right)
{
	int	pivot;
	
	if (left <= right)
	{
		// pivot is already in the right place
		// devide by pivot and sort
		pivot = partition(mans, left, right);
		quick_sort_mans(mans, left, pivot - 1);
		quick_sort_mans(mans, pivot + 1, right);
	}
}



void	print_man(t_info **mans, int num)
{
	int	i;
	
	i = -1;
	while (++i < num)
		printf("%d %s\n", mans[i]->age, mans[i]->name);
}



void	free_all(t_info **mans, int num)
{
	int i;
	
	i = -1;
	while (++i < num + 1)
		free(mans[i]);
	free(mans);
}



int		main(void)
{
	t_info	**mans;
	int	num;
	
	scanf("%d", &num);
	getchar();
	
	mans = info_input(num);
	quick_sort_mans(mans, 0, num - 1);
	
	print_man(mans, num);
	free_all(mans, num);
}
