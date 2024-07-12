#include "../../minishell.h"

void swap(char **a, char **b)
{
	char    *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void sort_env(char **env_copy, int count)
{
	int     i;
	int     j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (strcmp(env_copy[j], env_copy[j + 1]) > 0)
				swap(&env_copy[j], &env_copy[j + 1]);
			j++;
		}
		i++;
	}
}

void print_sorted_env(char **env)
{
	int		count;
	char	**env_copy;
	int		i;

	count = 0;
	while (env[count] != NULL)
		count++;
	env_copy = malloc(count * sizeof(char *));
	if (env_copy == NULL)
	{
		ft_printf("malloc error on export\n");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < count)
		env_copy[i] = env[i];
	sort_env(env_copy, count);
	i = -1;
	while (++i < count)
		printf("declare -x %s\n", env_copy[i]);
	free(env_copy);
}
