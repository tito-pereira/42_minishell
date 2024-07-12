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

#include "../../minishell.h"

void	wait_and_get_code(t_execlist *execl, int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	get_exit_code(status, execl->exit_stt);
}

int	exec_launch(t_execlist *execl, int **fd, int i, char ***exec_str)
{
	int	pid1;
	int	pid2;

	sig_handlerr(5);
	printf("in exec launch\n");
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
	printf("out exec launch\n");
	exit ((*execl->exit_stt));
}
