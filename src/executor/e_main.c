/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_old.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:32:48 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/10 11:32:48 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_exec(t_execlist *execl, int **fd)
{
	int	i;

	i = -1;
	while (++i < execl->valid_cmds)
	{
		fd[i] = ft_calloc(2, sizeof(int));
		pipe(fd[i]);
	}
}

void	end_exec(t_execlist *execl, int **fd, char ***exec_str)
{
	int	i;

	i = -1;
	while (++i < execl->valid_cmds)
	{
		if (exec_str[i] != NULL)
			exec_str[i] = free_db_str(exec_str[i]);
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
	}
	free(fd);
	free(exec_str);
}

void	get_exec_str(t_execlist *execl, char ***exec_str)
{
	int	i;
	int	c;

	c = -1;
	while (execl->chunk[++c] != NULL)
	{
		i = 0;
		if (!execl->chunk[c]->cmd_n_args)
		{
			exec_str[c] = NULL;
			continue ;
		}
		while (execl->chunk[c]->cmd_n_args[i] != NULL)
			i++;
		exec_str[c] = (char **)ft_calloc((i + 1), sizeof(char *));
		i = -1;
		while (execl->chunk[c]->cmd_n_args[++i] != NULL)
			exec_str[c][i] = ft_strdup(execl->chunk[c]->cmd_n_args[i]);
		exec_str[c][i] = NULL;
	}
}

void	get_exit_code(int status, int *exit_code)
{
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_code = WTERMSIG(status);
	else if (WIFSTOPPED(status))
		*exit_code = WSTOPSIG(status);
	else
		*exit_code = 1;
}

int	exec_main(t_execlist *execl)
{
	int		**fd;
	char	***exec_str;

	fd = (int **)ft_calloc(execl->valid_cmds, sizeof(int *));
	exec_str = (char ***)ft_calloc(execl->valid_cmds, sizeof(char **));
	if (!fd || !exec_str)
	{
		if (fd)
			free(fd);
		if (exec_str)
			free(exec_str);
		return (0);
	}
	sig_handlerr(3);
	init_exec(execl, fd);
	get_exec_str(execl, exec_str);
	exec_loop(execl, fd, exec_str);
	end_exec(execl, fd, exec_str);
	return (1);
}
