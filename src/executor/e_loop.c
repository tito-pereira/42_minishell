/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:38:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/08 15:16:39 by marvin           ###   ########.fr       */
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
	int	n_file;
	int	tmp;
	int	ret;

	n_file = execl->chunk[i]->nmb_outf;
	tmp = 0;
	ret = 0;
	//printf("inside BLT action\n");
	close_pipes(execl, fd, i, 0, 1); //close non related
	if (execl->chunk[i]->outfiles)
	{
		//printf("if 1\n");
		if (execl->chunk[i]->app_dcs[n_file] == 1) //append
			tmp = open(execl->chunk[i]->outfiles[n_file], \
			O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (execl->chunk[i]->app_dcs[n_file] == 0) // truncate
			tmp = open(execl->chunk[i]->outfiles[n_file], \
			O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(tmp, STDOUT_FILENO);
		close(tmp); //outfile
		ret = blt_central(execl, i, exec_str[i]);
		close(tmp);
	}
	else if (!execl->chunk[i]->outfiles && (i + 1) < execl->valid_cmds) //outpipe
	{
		//printf("else if 2\n");
		dup2(fd[i + 1][1], STDOUT_FILENO);
		close(fd[i + 1][1]); //outpipe
		ret = blt_central(execl, i, exec_str[i]);
	}
	else
	{
		//printf("else if 3\n");
		ret = blt_central(execl, i, exec_str[i]); //terminal
	}
	//printf("getting out\n");
	close_pipes(execl, fd, i, 1, 0); //close related
	//printf("blt action will return %d\n", ret);
	return (ret);
}

/*
X input
outfile
	- append
	- trunc
X outfile
	- outpipe
	- terminal

/non/exist/cmd
minishell: /non/exist/cmd: No such file or directory
echo $?
127
*/

void	get_act_err_code(char *str) //---//
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
	//printf("begin exec action %d\n", i);
	//support_print(execl, i);
	ret = 0;
	sig_handlerr(4);
	if (execl->chunk[i]->blt == 0)
	{
		exec_input(execl, fd, i);
		exec_output(execl, fd, i);
		//printf("exec action '%s'\n", exec_str[i][0]);
		ret = execve(exec_str[i][0], exec_str[i], (*execl->my_envp));
		get_act_err_code(exec_str[i][0]);
		//printf("execve failed ret was %d\n", ret);
		//ft_printf("minishell: %s: No such file or directory\n", exec_str[i][0]);
		//exit(127);
	}
	else if (execl->chunk[i]->blt == 1)
	{
		//printf("BLT command %d\n", i);
		ret = blt_action(execl, fd, i, exec_str);
		if (execl->valid_cmds == 1 && check_changes(execl->chunk[0]) == 1)
		{
			//printf("inside BLT env pipe\n");
			close(execl->env_pipe[0]);
			//write(execl->env_pipe[1], execl->my_envp, sizeof(char ***));
			write_to_pipe(execl->env_pipe[1], execl->my_envp);
			//printf("in writing: closing writing [%d]\n", execl->env_pipe[1]);
			close(execl->env_pipe[1]);
		}
	}
	//printf("exec action will exit %d\n", ret);
	exit(ret);
}

int	exec_launch(t_execlist *execl, int **fd, int i, char ***exec_str)
{
	int	pid1;
	int	pid2;
	int status; //---//

	//printf("in exec launch. exit stt is %d\n", (*execl->exit_stt));
	status = 0;
	sig_handlerr(5);
	if ((i + 1) < execl->valid_cmds)
	{
		i++;
		//ft_printf("launching other [%d]\n", (i - 1));
		pid1 = fork();
		if (pid1 == 0)
		{
			exec_launch(execl, fd, i, exec_str);
			//ft_printf("out of launch [%d]\n", i);
			//exit(0);
		}
		i--;
	} 
	pid2 = fork();
	if (pid2 == 0)
		exec_action(execl, fd, i, exec_str); //redir
	else
	{
		close_pipes(execl, fd, i, 1, 1);
		//ft_printf("lets wait for first one[%d]\n", i);
		//wait (&status); //---// pid = wait(NULL); //
		/*if ((i + 1) < execl->valid_cmds)
		{
			ft_printf("lets wait for scnd one\n");
			//wait (&status); //---// wait(NULL); //
			waitpid(pid1, &status, 0);
			get_exit_code(status, execl->exit_stt);
		}*/
		waitpid(pid2, &status, 0);
		//printf("status returned was %d\n", status);
		get_exit_code(status, execl->exit_stt); //---//
		if ((i + 1) < execl->valid_cmds)
		{
			//ft_printf("lets wait for scnd one\n");
			//wait (&status); //---// wait(NULL); //
			waitpid(pid1, &status, 0);
			get_exit_code(status, execl->exit_stt);
		}
		//ft_printf("all waits done\n");
	}
	//ft_printf("fora action env = %s\n", execl->my_envp[0][52]);
	//get_exit_code(status, execl->exit_stt); //---//
	//printf("out exec_launch exit stt is %d\n", (*execl->exit_stt));
	exit ((*execl->exit_stt)); //---// exit(0);
	//return (1);
	//ft_printf("exec launch out [%d]\n", i);
}

int	exec_loop(t_execlist *execl, int **fd, char ***exec_str) //funcao tipo int
{
	int	i;
	int	pid;
	int	status; //---//
	//int	ret;
	//char ***tmpenv;

	i = 0;
	status = 0;
	//printf("in exec_loop. exit stt is %d\n", (*execl->exit_stt));
	//ft_printf("Inside exec_loop.\n\n\n");
	//print_db_char(execl->my_envp[0]);
	//ret = 0;
	//tmpenv = NULL;
	if (execl->valid_cmds == 1 && check_changes(execl->chunk[0]) == 1)
	{
		//printf("creating the envp pipes:\n");
		execl->env_pipe = (int *)ft_calloc(2, sizeof(int));
		pipe(execl->env_pipe);
		//if (ret == -1)
			//printf("pipe error\n");
		//else
			//printf("pipes created: [0] = %d, [1] = %d\n", execl->env_pipe[0], execl->env_pipe[1]);
	}
	//printf("after env pipe exec_loop. exit stt is %d\n", (*execl->exit_stt));
	open_all_redirs(execl);
	//printf("redir open return was %d\n", (*execl->exit_stt));
	if ((*execl->exit_stt) != 0)
		return ((*execl->exit_stt));
	//printf("after open redirs exec_loop. exit stt is %d\n", (*execl->exit_stt));
	ft_printf("Inside exec_loop.\n\n\n");
	pid = fork();
	if (pid == 0)
	{
		exec_launch(execl, fd, i, exec_str);
		exit(0);
	}
	close_pipes(execl, fd, i, 1, 1);
	//wait(&status); //---// wait(NULL);
	waitpid(pid, &status, 0);
	get_exit_code(status, execl->exit_stt); //---//
	if (execl->valid_cmds == 1 && check_changes(execl->chunk[0]) == 1)
	{
		//printf("cmds = %d, changes[0] = %d\n", execl->valid_cmds, check_changes(execl->chunk[0]));
		//printf("in read: closing writing [%d]\n", execl->env_pipe[1]);
		close(execl->env_pipe[1]);
		free_db_str(execl->my_envp[0]);
		//tmpenv = read_from_pipe(execl->env_pipe[0], execl);
		//execl->my_envp = tmpenv;
		execl->my_envp = read_from_pipe(execl->env_pipe[0], execl);
		/*if (execl->my_envp)
		{
			printf("\nnew envs\n");
			print_db_char(execl->my_envp[0]);
		}
		else
			printf("there are no new envs\n");*/
		close(execl->env_pipe[0]);
		//printf("also here\n");
	}
	ft_printf("\n\n\nexec_loop finished.\n");
	//printf("out exec_loop exit stt is %d\n", (*execl->exit_stt));
	//get_exit_code(status, execl->exit_stt); //---//
	//printf("out exec_loop exit stt is %d\n", (*execl->exit_stt));
	return ((*execl->exit_stt)); //---//
}

/*
exec_main
open_all_redirs
exec_loop V
exec_launch V

retornar exit_code para exec_main
fds compilou.. como comeco sequer a testar esta merda


2 instancias:

- open all redirs:
	- non existant file
	- permissions error
- exec_launch:
	- other execution errors
	- SIGINT (blocking commands)

exec (0, 1, 126, 127, 130)
c aqueles macros transformar qq erro nestes 4.

- wait() + get_exit_stt dentro do exec_loop e de cada exec_launch individual
2 wait dentro do launch.. nao me posso dar ao luxo de distinguir, fazer apenas pra 1

- talvez tenha q fazer de maneira diferente nos BLT n sei

- qual a ordem de hierarquia de erros? (ultimo pra ja)

(V) . Non-existent File Error: 127 (command && path not found)
(V) . Permissions Error: 126 (command invoked cannot execute, or permission denied errors)
. SIGINT (130)
. Error Code: 2 (typically used for incorrect usage or syntax errors, incorrect args ou isso
. fd error: 1

- exec error codes
- blt exec error codes
*/