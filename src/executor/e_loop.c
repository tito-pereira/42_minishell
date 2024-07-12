/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:38:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/13 00:30:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_changes(t_chunk *chunk)
{
	int	ret;

	ret = 0;
	if (!chunk->cmd_n_args)
		return (0);
	if (ft_strncmp(chunk->cmd_n_args[0], "cd", 3) == 0)
		ret = 1;
	if (ft_strncmp(chunk->cmd_n_args[0], "export", 7) == 0)
		ret = 1;
	if (ft_strncmp(chunk->cmd_n_args[0], "unset", 6) == 0)
		ret = 1;
	return (ret);
}

int	blt_action(t_execlist *execl, int **fd, int i, char ***exec_str)
{
	int	ret;

	ret = 0;
	close_pipes(execl, fd, i, 2);
	if (execl->chunk[i]->outfiles)
		blt_action_outf(execl, i, &ret, exec_str);
	else if (!execl->chunk[i]->outfiles && (i + 1) < execl->valid_cmds)
	{
		dup2(fd[i + 1][1], STDOUT_FILENO);
		close(fd[i + 1][1]);
		ret = blt_central(execl, i, exec_str[i]);
	}
	else
		ret = blt_central(execl, i, exec_str[i]);
	close_pipes(execl, fd, i, 1);
	return (ret);
}

void	get_act_err_code(char *str)
{
	if (errno == 13)
	{
		ft_printf("minishell: %s: Is a directory\n", str);
		exit (126);
	}
	if (errno == EISDIR)
	{
		ft_printf("minishell: %s: Permission denied\n", str);
		exit (126);
	}
	else if (errno == ENOENT)
	{
		ft_printf("minishell: %s: No such file or directory\n", str);
		exit (127);
	}
}

void	exec_action(t_execlist *execl, int **fd, int i, char ***exec_str)
{
	int	ret;

	ret = 0;
	//printf("exec action %d\n", i); //
	sig_handlerr(4);
	chk_emp_exec(execl, fd, i, exec_str); //
	if (execl->chunk[i]->blt == 0) // && ret == 0
	{
		//printf("execve %d\n", i); //
		exec_input(execl, fd, i);
		exec_output(execl, fd, i);
		//printf("GOGO %d\n", i); //
		ret = execve(exec_str[i][0], exec_str[i], (*execl->my_envp));
		get_act_err_code(exec_str[i][0]);
	}
	else if (execl->chunk[i]->blt == 1) // && ret == 0
	{
		ret = blt_action(execl, fd, i, exec_str);
		if (execl->valid_cmds == 1 && check_changes(execl->chunk[0]) == 1)
		{
			close(execl->env_pipe[0]);
			write_to_pipe(execl->env_pipe[1], execl->my_envp);
			close(execl->env_pipe[1]);
		}
	}
	exit(ret);
}

int	exec_loop(t_execlist *execl, int **fd, char ***exec_str)
{
	int	i;
	int	pid;

	i = 0;
	//printf("in exec loop\n"); //
	if (execl->valid_cmds == 1 && check_changes(execl->chunk[0]) == 1)
	{
		execl->env_pipe = (int *)ft_calloc(2, sizeof(int));
		pipe(execl->env_pipe);
	}
	//open_all_redirs(execl);
	//if ((*execl->exit_stt) != 0)
		//return ((*execl->exit_stt));
	pid = fork();
	if (pid == 0)
	{
		exec_launch(execl, fd, i, exec_str);
		exit(0);
	}
	close_pipes(execl, fd, i, 3);
	wait_and_get_code(execl, pid);
	if (execl->valid_cmds == 1 && check_changes(execl->chunk[0]) == 1)
		receive_new_env(&execl);
	//printf("out exec loop\n"); //
	return ((*execl->exit_stt));
}
