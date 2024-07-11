/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_6a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:40:54 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/11 15:46:31 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rmv_newline(char *old)
{
	char				*new;
	unsigned int		len;

	len = ft_strlen(old);
	if (old[len - 1] == '\n')
	{
		new = malloc(len * sizeof(char));
		ft_strlcpy(new, old, len);
		free(old);
		return (new);
	}
	return (old);
}

char	**find_execve(char *name, int option)
{
	char	**env;

	env = NULL;
	if (option == 1)
	{
		env = ft_calloc(5, sizeof(char *));
		env[0] = ft_strdup("/usr/bin/find");
		env[1] = ft_strdup(".");
		env[2] = ft_strdup("-name");
		env[3] = ft_strdup(name);
		env[4] = NULL;
	}
	else if (option == 2)
	{
		env = ft_calloc(3, sizeof(char *));
		env[0] = ft_strdup("/usr/bin/which");
		env[1] = ft_strdup(name);
		env[2] = NULL;
	}
	return (env);
}

char	*get_path(char *name, int option)
{
	char	*path;
	char	**env;
	int		*fd;
	int		pid;

	fd = malloc(2 * sizeof(int));
	pipe(fd);
	env = find_execve(name, option);
	pid = fork();
	if (pid == 0)
	{
		close (fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		execve(env[0], env, ENV_VAR);
	}
	wait(0);
	env = free_db_str(env);
	close(fd[1]);
	path = get_next_line(fd[0]);
	close(fd[0]);
	free(fd);
	return (path);
}

char	*find_path(char	*arg, int option)
{
	char	*path;

	path = get_path(arg, option);
	if (path == NULL)
		return (NULL);
	path = rmv_newline(path);
	return (path);
}

int	chunk_id(t_chunk *chunk, int opt)
{
	char	*path;
	char	*old;

	path = NULL;
	if (opt == 1)
	{
		path = NULL;
		chunk->path = NULL;
	}
	else if (opt == 2)
		path = find_path(chunk->cmd_n_args[0], 2);
	if (opt == 2 && path == NULL)
		return (0);
	else if (opt == 2)
	{
		old = chunk->cmd_n_args[0];
		chunk->cmd_n_args[0] = path;
		free (old);
	}
	return (1);
}
