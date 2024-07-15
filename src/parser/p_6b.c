/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_6b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 22:26:42 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/15 13:22:50 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_path_var(t_execlist *execl)
{
	int	i;

	i = -1;
	while (execl->my_envp[0][++i])
	{
		if (ft_strncmp(execl->my_envp[0][i], "PATH=", 5) == 0)
			return (i);
	}
	return (-1);
}

int	set_indexes(int *a, int *b, int *i, t_execlist *execl)
{
	int	j;

	j = 0;
	*i = 5;
	*a = 5;
	*b = 0;
	j = find_path_var(execl);
	return (j);
}

char	*the_loop(t_execlist *execl, char *arg, int j, int *a)
{
	char	*path;
	int		i;
	int		b;

	i = 5;
	*a = 5;
	b = 0;
	while (execl->my_envp[0][j][++i] && execl->my_envp[0][j][i] != '\0')
	{
		if (execl->my_envp[0][j][i] == ':')
		{
			b = i;
			path = ft_substr(execl->my_envp[0][j], *a, (b - *a));
			path = get_path(arg, path, execl);
			if (path != NULL)
				return (path);
			*a = b + 1;
		}
	}
	return (NULL);
}

char	*the_last(t_execlist *execl, char *arg, int j, int *a)
{
	char	*path;
	int		i;
	int		b;

	i = 5;
	b = 5;
	while (execl->my_envp[0][j][i] && execl->my_envp[0][j][i] != '\0')
	{
		i++;
		b++;
	}
	if (*a < i)
	{
		b = i;
		path = ft_substr(execl->my_envp[0][j], *a, (b - *a));
		path = get_path(arg, path, execl);
		if (path != NULL)
			return (path);
	}
	return (NULL);
}

char	*find_path(char	*arg, t_execlist *execl)
{
	int		j;
	int		a;
	char	*path;

	j = find_path_var(execl);
	if (j == -1)
		return (NULL);
	path = the_loop(execl, arg, j, &a);
	if (path)
	{
		path = rmv_newline(path);
		return (path);
	}
	path = the_last(execl, arg, j, &a);
	if (path)
	{
		path = rmv_newline(path);
		return (path);
	}
	return (NULL);
}
