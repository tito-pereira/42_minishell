/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_launch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:49:41 by marvin            #+#    #+#             */
/*   Updated: 2024/07/09 23:49:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_big_boys(t_execlist *execl, int **fd, char ***str, int ret)
{
	int	i;

	i = -1;
	while (++i < execl->valid_cmds)
	{
		if (str[i] != NULL)
			str[i] = free_db_str(str[i]);
		free(fd[i]);
	}
	free(fd);
	free(str);
	free_exec(execl, 2);
	return (ret);
}

void	wait_and_get_code(t_execlist *execl, int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	get_exit_code(status, execl->exit_stt);
}

int	exit_launch(t_execlist *execl, int **fd, char ***exec_str)
{
	int	ret;

	ret = (*execl->exit_stt);
	free_big_boys(execl, fd, exec_str, 0);
	return (ret);
}

int	exec_launch(t_execlist *execl, int **fd, int i, char ***exec_str)
{
	int	pid1;
	int	pid2;

	sig_handlerr(5);
	if ((i + 1) < execl->valid_cmds)
	{
		i++;
		pid1 = fork();
		if (pid1 == 0)
			exec_launch(execl, fd, i, exec_str);
		i--;
	}
	pid2 = fork();
	if (pid2 == 0)
		exec_action(execl, fd, i, exec_str);
	else
	{
		close_pipes(execl, fd, i, 3);
		wait_and_get_code(execl, pid2);
		if ((i + 1) < execl->valid_cmds)
			wait_and_get_code(execl, pid1);
	}
	exit (exit_launch(execl, fd, exec_str));
}

/*

int	exec_launch(t_execlist *execl, int **fd, int i, char ***exec_str)
{
	int	pid1;
	int	pid2;

	sig_handlerr(5);
	if ((i + 1) < execl->valid_cmds)
	{
		i++;
		pid1 = fork();
		if (pid1 == 0)
			exec_launch(execl, fd, i, exec_str);
		i--;
	}
	pid2 = fork();
	if (pid2 == 0)
		exec_action(execl, fd, i, exec_str);
	else
	{
		close_pipes(execl, fd, i, 3);
		wait_and_get_code(execl, pid2);
		if ((i + 1) < execl->valid_cmds)
			wait_and_get_code(execl, pid1);
	}
	exit ((*execl->exit_stt));
}
*/
