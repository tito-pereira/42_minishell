/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_envs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:41:51 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/09 22:38:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	write_to_pipe(int fd, char ***envs)
{
	int	i;

	i = -1;
	while(envs && envs[0][++i])
	{
		ft_putstr_fd(envs[0][i], fd);
		ft_putchar_fd('\n', fd);
	}
	ft_putchar_fd('\0', fd);
}

char	**add_str(char **list, int *i)
{
	char 	**new;
	int		j;
	
	(*i) = 0;
	j = 0;
	while (list[*i] != NULL)
		(*i)++;
	new = (char **)malloc(((*i) + 2) * sizeof(char *));
	(*i) = 0;
	while (list[(*i)] != NULL)
	{
		new[j] = ft_strdup(list[(*i)]);
		j++;
		(*i)++;
	}
	new[j] = NULL;
	new[j + 1] = NULL;
	free_db_str(list);
	return (new);
}

void	mng_env_list(char ***env_list, char *input, int *i)
{
	if (!(*env_list))
	{
		(*env_list) = (char **)malloc(2 * sizeof(char *));
		(*env_list)[0] = ft_strdup(input);
		(*env_list)[1] = NULL;
	}
	else
	{
		(*env_list) = add_str(*env_list, i);
		(*env_list)[*i] = ft_strdup(input);
	}
}

char	***read_from_pipe(int fd, t_execlist *execl)
{
	char	***n_env;
	char	**env_list;
	char	*input;
	int		i;

	(void) execl;
	input = get_next_line(fd);
	env_list = NULL;
	i = 0;
	if (!input)
		return (NULL);
	while (input != NULL)
	{
		input = rmv_newline(input);
		mng_env_list(&env_list, input, &i);
		free(input);
		input = get_next_line(fd);
	}
	n_env = (char ***)malloc(sizeof(char **));
	*n_env = env_list;
	return (n_env);
}
