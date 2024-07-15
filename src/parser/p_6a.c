/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_6a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:40:54 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/15 13:21:57 by tibarbos         ###   ########.fr       */
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

char	**find_execve(char *path, char *name)
{
	char	**env;

	env = NULL;
	env = ft_calloc(5, sizeof(char *));
	env[0] = ft_strdup("/usr/bin/find");
	if (path)
		env[1] = ft_strdup(path);
	env[2] = ft_strdup("-name");
	if (name)
		env[3] = ft_strdup(name);
	env[4] = NULL;
	if (path)
		free(path);
	return (env);
}

void	the_fork_help(t_execlist *execl, int *fd, char **env)
{
	int	dev_null;

	close (fd[0]);
	dev_null = open("/dev/null", O_WRONLY);
	dup2(dev_null, STDERR_FILENO);
	close(dev_null);
	dup2(fd[1], STDOUT_FILENO);
	close (fd[1]);
	execve(env[0], env, execl->my_envp[0]);
}

char	*get_path(char *name, char *path, t_execlist *execl)
{
	char	**env;
	int		*fd;
	int		pid;

	fd = (int *)ft_calloc(2, sizeof(int));
	pipe(fd);
	env = find_execve(path, name);
	pid = fork();
	if (pid == 0)
		the_fork_help(execl, fd, env);
	wait(0);
	env = free_db_str(env);
	close(fd[1]);
	path = get_next_line(fd[0]);
	close(fd[0]);
	free(fd);
	return (path);
}

int	chunk_id(t_chunk *chunk, int opt, t_execlist *execl)
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
		path = find_path(chunk->cmd_n_args[0], execl);
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
