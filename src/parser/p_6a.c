/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_6a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:40:54 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/14 22:27:39 by tibarbos         ###   ########.fr       */
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
	env = ft_calloc(8, sizeof(char *));
	env[0] = ft_strdup("/usr/bin/find");
	env[1] = ft_strdup(path);
	env[2] = ft_strdup("-name");
	env[3] = ft_strdup(name);
	env[4] = ft_strdup("-type");
	env[5] = ft_strdup("f");
	env[6] = ft_strdup("-executable");
	env[7] = NULL;
	return (env);
}

/*
find /usr/bin -name "command_name" -type f -executable
find <path> -name <name> -type f -executable

find /usr/bin -name ls -type f -executable
/usr/bin/ls
*/

char	*get_path(char *name, char *path, t_execlist *execl)
{
	//char	*path;
	char	**env;
	int		*fd;
	int		pid;

	fd = malloc(2 * sizeof(int));
	pipe(fd);
	env = find_execve(path, name);
	//print_db(execl->my_envp[0]);
	pid = fork();
	if (pid == 0)
	{
		close (fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		execve(env[0], env, execl->my_envp[0]);
	}
	wait(0);
	env = free_db_str(env);
	close(fd[1]);
	path = get_next_line(fd[0]);
	close(fd[0]);
	free(fd);
	return (path);
}

/*
free old path
*/

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

/*
no PATH da segfault

separar aquela grande em 3
testar maios ou menos i guess
passar o tester
TESTAR UNSET PATH ETC

execve(env[0], env, ENV_VAR);

blt 1
X blt 2
so estou a utlizar o 2, X blt, que faz which

else if (option == 2)
	{
		env = ft_calloc(3, sizeof(char *));
		env[0] = ft_strdup("/usr/bin/which");
		env[1] = ft_strdup(name);
		env[2] = NULL;
	}

experimentar com o command -v
"/bin/sh"
char *argv[] = { "sh", "-c", "command -v ", name, NULL };

basicamente vou ter que iterar sobre as minhas proprias envps
find path, get path, find execve desaparecem

find path vai iterar sobre o meu proprio path, de : em :
pega nesse path

find /usr/bin -name "command_name" -type f -executable
find <path> -name "<>" command_name -type f -executable

ou retorna o path ou empty
*/





















/*
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
		env = ft_calloc(6, sizeof(char *));
		env[0] = ft_strdup("/bin/sh");
		env[1] = ft_strdup("-c");
		env[2] = ft_strdup("command");
		env[3] = ft_strdup("-v");
		env[4] = ft_strdup(name);
		env[5] = NULL;
	}
	return (env);
}

char	*get_path(char *name, int option, t_execlist *execl)
{
	char	*path;
	char	**env;
	int		*fd;
	int		pid;

	fd = malloc(2 * sizeof(int));
	//printf("get_path for '%s'\n", name); //
	pipe(fd);
	env = find_execve(name, option);
	print_db(execl->my_envp[0]);
	pid = fork();
	if (pid == 0)
	{
		close (fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		execve(env[0], env, execl->my_envp[0]);
	}
	wait(0);
	env = free_db_str(env);
	close(fd[1]);
	path = get_next_line(fd[0]);
	close(fd[0]);
	free(fd);
	return (path);
}

char	*find_path(char	*arg, int option, t_execlist *execl)
{
	char	*path;

	path = get_path(arg, option, execl);
	if (path == NULL)
		return (NULL);
	path = rmv_newline(path);
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
		path = find_path(chunk->cmd_n_args[0], 2, execl);
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
*/