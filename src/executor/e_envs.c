/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_envs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:41:51 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/22 18:08:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	write_to_pipe(int fd, char ***envs)
{
	int	i;

	i = -1;
	//printf("inside writing\n");
	while(envs && envs[0][++i])
	{
		//printf("w[%d] = '%s'\n", i, envs[0][i]);
		ft_putstr_fd(envs[0][i], fd);
		ft_putchar_fd('\n', fd);
	}
	ft_putchar_fd('\0', fd);
	//printf("outside writing\n");
}

char	**add_str(char **list, int *i)
{
	char 	**new;
	int		j;
	
	//printf("incoming = %d\n", *i);
	(*i) = 0;
	j = 0;
	while (list[*i] != NULL)
	{
		//printf("old list[%d] = '%s'\n", *i, list[*i]);
		(*i)++;
	}
	//printf("first count %d\n", *i);
	new = (char **)malloc(((*i) + 2) * sizeof(char *));
	(*i) = 0;
	while (list[(*i)] != NULL)
	{
		new[j] = ft_strdup(list[(*i)]);
		//printf("new list[%d] = '%s'\n", j, new[j]);
		//printf("old list[%d] = '%s'\n", *i, list[(*i)]);
		j++;
		(*i)++;
	}
	//printf("after loop i %d\n", *i);
	//printf("after loop j %d\n", *i);
	new[j] = NULL;
	new[j + 1] = NULL;
	free_db_str(list);
	//printf("function exit %d\n", *i);
	return (new);
}

char	***read_from_pipe(int fd, t_execlist *execl)
{
	char	***n_env;
	char	**env_list;
	char	*input;
	int		i;

	//printf("\n\n\ninside reading\n");
	//print_db_char(execl->my_envp[0]);
	(void) execl;
	input = get_next_line(fd);
	env_list = NULL;
	//printf("inside reading\n");
	//printf("first input = '%s'\n", input);
	i = 0;
	if (!input)
		return (NULL);
	//input = rmv_newline(input);
	while (input != NULL)
	{
		input = rmv_newline(input);
		//printf("------------inside while---------------\n");
		if (!env_list)
		{
			//printf("if\n");
			env_list = (char **)malloc(2 * sizeof(char *));
			env_list[0] = ft_strdup(input);
			//printf("env_list[0] = '%s'\n", env_list[0]);
			env_list[1] = NULL;
			//printf("env_list[1] = '%s'\n", env_list[1]);
		}
		else
		{
			//printf("else\n");
			env_list = add_str(env_list, &i);
			env_list[i] = ft_strdup(input);
			//printf("env_list[%d] = '%s'\n", i, env_list[i]);
			//printf("env_list[%d] = '%s'\n", (i + 1), env_list[i + 1]);
		}
		free(input);
		//print_db_char(env_list);
		input = get_next_line(fd);
	}
	n_env = (char ***)malloc(sizeof(char **));
	//n_env = &env_list;
	*n_env = env_list;
	//printf("\n\n\nend reading\n");
	//print_db_char(n_env[0]);
	return (n_env);
}

/*
char *str = malloc(sizeof(char));
char **db = malloc(sizeof(char *));
char ***tp = malloc(sizeof(char **));
*/