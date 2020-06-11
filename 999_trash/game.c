#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	CHAR_SIZE	4  // number of hero

enum{thanos, iron_man, captain_america, thor};

typedef	struct	s_char
{
	char		name[32];
	int			attack;
	int			defense;
	int			health;
	int			battle_experience;  // 0 : fight x, 1 : fight o
}				t_char;



void	ft_strcpy(char *s1, char *s2)  // strcpy
{
	int i;
	
	i = -1;
	while(s2[++i])
		s1[i] = s2[i];
	s1[i] = '\0';
}

t_char	*make_hero(char *name, int attack, int defense, int health)
{
	t_char *hero;
	
	hero = (t_char *)malloc(sizeof(t_char));
	ft_strcpy(hero->name, name);
	hero->attack = attack;
	hero->defense = defense;
	hero->health = health;
	hero->battle_experience = 0;  // no fight experience yet

	return (hero);
}

t_char	**make_heros(void)
{
	t_char	**heros;
	
	heros = (t_char **)malloc(sizeof(t_char *) * CHAR_SIZE);
	heros[0] = make_hero("thanos", 100, 50, 300);
	heros[1] = make_hero("iron man", 70, 50, 100);
	heros[2] = make_hero("captain america", 60, 50, 100);
	heros[3] = make_hero("thor", 90, 20, 100);
	
	return (heros);
}



int		input_form(t_char **hero)
{
	int	select;

	printf("----- input form -----\n");
	printf("1.iron man 2.captain america 3.thor\n");
	printf("select : ");
	scanf("%d", &select);
	printf("\n");
	
	hero[select]->battle_experience = 1;  // not fighting myself

	return (select);
}



void	show_info(t_char *my_char)
{
	printf("name : %s\n", my_char->name);
	printf("attack power : %d\n", my_char->attack);
	printf("deffense power : %d\n", my_char->defense);
	printf("health : %d\n", my_char->health);
}

void	before_fight(t_char **heros, int my_char, int enemy)
{
	heros[enemy]->battle_experience = 1;  // fight

	printf("--my character--\n");
	show_info(heros[my_char]);
	printf("--enemy character--\n");
	show_info(heros[enemy]);
	printf("--battle--\n\n");
}

void	attack(t_char *attacker, t_char *defender)
{
	defender->health = defender->health - attacker->attack;
}

int		fight(t_char **heros, int my_char, int enemy)
{
	// character description before battle
	before_fight(heros, my_char, enemy);
	
	while (heros[my_char]->health >= 0)
	{
		attack(heros[my_char], heros[enemy]);
		// if i win, 1 return
		if (heros[enemy]->health <= 0)
			return (1);
		attack(heros[enemy], heros[my_char]);
	}
	return (0); // if i lose, 0 return
}

void	fight_after(t_char **heros, int my_char)
{
	heros[my_char]->attack = heros[my_char]->attack + 10;
	heros[my_char]->defense = heros[my_char]->defense + 10;
	heros[my_char]->health = heros[my_char]->health + 200;
}

void	battle_game(t_char **heros, int my_char)
{
	int	battle_count;
	int	fight_result;
	int	enemy;
	
	battle_count = 0;
	fight_result = 1;
	srand(time(NULL));  // reset time to use random numbers
	
	printf("----- output form -----\n");
	while (battle_count < CHAR_SIZE - 1 && fight_result)
	{
		enemy = rand() % CHAR_SIZE;  // random enemies appear
		// cancel any enemy with fight experience
		if (heros[enemy]->battle_experience)
			continue ;
		battle_count++;

		printf("***%dst stage***\n", battle_count);
		fight_result = fight(heros, my_char, enemy);
		if (fight_result)
			printf("you win!\n\n");
		else
		{
			printf("you lose!\n\n");
			break ;
		}
		
		fight_after(heros, my_char);  // recovery after battle
	}
}



// free all allocated memory
void	free_all(t_char **heros)
{
	int i;
	
	i = -1;
	while (++i < CHAR_SIZE)
		free(heros[i]);
	free(heros);
}



int		main(void)
{
	t_char	**heros;
	int		my_char;

	heros = make_heros();
	my_char = input_form(heros);
	battle_game(heros, my_char);
	
	free_all(heros);
}
