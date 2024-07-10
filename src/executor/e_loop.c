/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:38:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/10 00:33:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_changes(t_chunk *chunk)
{
	int	ret;

	ret = 0;
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
	sig_handlerr(4);
	if (execl->chunk[i]->blt == 0)
	{
		exec_input(execl, fd, i);
		exec_output(execl, fd, i);
		ret = execve(exec_str[i][0], exec_str[i], (*execl->my_envp));
		get_act_err_code(exec_str[i][0]);
	}
	else if (execl->chunk[i]->blt == 1)
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
	if (execl->valid_cmds == 1 && check_changes(execl->chunk[0]) == 1)
	{
		execl->env_pipe = (int *)ft_calloc(2, sizeof(int));
		pipe(execl->env_pipe);
	}
	open_all_redirs(execl);
	if ((*execl->exit_stt) != 0)
		return ((*execl->exit_stt));
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
	return ((*execl->exit_stt));
}

/*
e_loop - blt action, exec launch, exec loop

int	blt_action(t_execlist *execl, int **fd, int i, char ***exec_str)
{
	int	n_file;
	int	tmp;
	int	ret;

	n_file = execl->chunk[i]->nmb_outf;
	tmp = 0;
	ret = 0;
	close_pipes(execl, fd, i, 2);
	if (execl->chunk[i]->outfiles)
	{
		if (execl->chunk[i]->app_dcs[n_file] == 1)
			tmp = open(execl->chunk[i]->outfiles[n_file], \
			O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (execl->chunk[i]->app_dcs[n_file] == 0)
			tmp = open(execl->chunk[i]->outfiles[n_file], \
			O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(tmp, STDOUT_FILENO);
		close(tmp);
		ret = blt_central(execl, i, exec_str[i]);
		close(tmp);
	}
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

int	exec_launch(t_execlist *execl, int **fd, int i, char ***exec_str)
{
	int	pid1;
	int	pid2;
	int status;

	status = 0;
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
		waitpid(pid2, &status, 0);
		get_exit_code(status, execl->exit_stt);
		if ((i + 1) < execl->valid_cmds)
		{
			waitpid(pid1, &status, 0);
			get_exit_code(status, execl->exit_stt);
		}
	}
	exit ((*execl->exit_stt));
}

int	exec_loop(t_execlist *execl, int **fd, char ***exec_str)
{
	int	i;
	int	pid;
	int	status;

	i = 0;
	status = 0;
	if (execl->valid_cmds == 1 && check_changes(execl->chunk[0]) == 1)
	{
		execl->env_pipe = (int *)ft_calloc(2, sizeof(int));
		pipe(execl->env_pipe);
	}
	open_all_redirs(execl);
	if ((*execl->exit_stt) != 0)
		return ((*execl->exit_stt));
	pid = fork();
	if (pid == 0)
	{
		exec_launch(execl, fd, i, exec_str);
		exit(0);
	}
	close_pipes(execl, fd, i, 3);
	waitpid(pid, &status, 0);
	get_exit_code(status, execl->exit_stt);
	if (execl->valid_cmds == 1 && check_changes(execl->chunk[0]) == 1)
	{
		close(execl->env_pipe[1]);
		free_db_str(execl->my_envp[0]);
		execl->my_envp = read_from_pipe(execl->env_pipe[0], execl);
		close(execl->env_pipe[0]);
	}
	return ((*execl->exit_stt));
}

*/