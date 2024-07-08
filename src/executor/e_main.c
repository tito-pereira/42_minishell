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

/////////////////////////

void	init_exec(t_execlist *execl, int **fd)
{
	int i;
	//int	j;
	//int	ret;
	
	i = -1;
	//ft_printf("Initializing the executor function.\n");
	while (++i < execl->valid_cmds)
	{
		//ft_printf("i: %d < cmds: %d\n", i, execl->valid_cmds);
		//redir[i] = ft_calloc(2, sizeof(int));
		fd[i] = ft_calloc(2, sizeof(int));
		/*j = -1;
		while (++j < 2)
		{
			ft_printf("j: %d\n", j);
			//redir[i][j] = -1;
			ft_printf("redir[%d][%d]: %d\n", i, j, redir[i][j]);
			//fd[i][j] = -1;
			ft_printf("fd[%d][%d]: %d\n", i, j, fd[i][j]);
		}*/
		pipe(fd[i]);
		/*if (ret == 0)
		{
			ft_printf("pipe[%d] success\n", i);
			ft_printf("fd[%d][0]: %d\nfd[%d][1]: %d\n", i, fd[i][0], i, fd[i][1]);
		}
		else
			ft_printf("pipe[%d] failed\n", i);*/
	}
	//ft_printf("fd && redir initialized.\n");
}

void	end_exec(t_execlist *execl, int **fd, char ***exec_str)
{
	int i;
	
	i = -1;
	ft_printf("Ending the executor function.\n");
	while (++i < execl->valid_cmds)
	{
		exec_str[i] = free_db_str(exec_str[i]);
		//free(redir[i]);
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
	}
	//free(redir);
	free(fd);
	free(exec_str);
	//ft_printf("All frees done.\n");
}

////////////////////////////////

void	get_exec_str(t_execlist *execl, char ***exec_str)
{
	int	i;
	int	c;

	c = -1;
	//ft_printf("Creating all the exec_str structs.\n");
	while (execl->chunk[++c] != NULL)
	{
		i = 0;
		//ft_printf("Command[%d]\n", c);
		while (execl->chunk[c]->cmd_n_args[i] != NULL)
			i++;
		//ft_printf("Size[%d]: %d\n", c, i);
		exec_str[c] = malloc((i + 1 /*+ execl->chunk[c]->blt*/) * sizeof(char *));
		//ft_printf("Malloc[%d]: %d\n", c, (i + 1 + execl->chunk[c]->blt));
		//if (execl->chunk[c]->blt == 1)
			//exec_str[c][0] = ft_strdup(execl->chunk[c]->path);
		i = -1;
		while (execl->chunk[c]->cmd_n_args[++i] != NULL)
		{
			exec_str[c][i /*+ execl->chunk[c]->blt*/] = ft_strdup(execl->chunk[c]->cmd_n_args[i]);
			//ft_printf("exec_str[%d][%d]:%s ", c, (i + execl->chunk[c]->blt), exec_str[c][i + execl->chunk[c]->blt]);
			//ft_printf("= execl->chunk[%d]->cmd_n_args[%d]:%s;\n", c, i, execl->chunk[c]->cmd_n_args[i]);
		}
		exec_str[c][i /*+ execl->chunk[c]->blt*/] = NULL;
		//ft_printf("exec_str[%d][%d]:NULL;\n", c, (i + execl->chunk[c]->blt));
	}
	//ft_printf("All the exec_str created.\n");
}

////////////////////////////////
void	get_exit_code(int status, int *exit_code) //---//
{
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		//printf("Child terminated by signal %d\n", WTERMSIG(status));
		*exit_code = WTERMSIG(status);
	}
	else if (WIFSTOPPED(status))
		*exit_code = WSTOPSIG(status);
	else
		*exit_code = 1;
}

int	exec_main(t_execlist *execl)
{
	int		**fd;
	//int		**redir;
	char	***exec_str;

	//printf("exec. exit stt is %d\n", (*execl->exit_stt));
	fd = (int **)ft_calloc(execl->valid_cmds, sizeof(int *));
	//redir = (int **)ft_calloc(execl->valid_cmds, sizeof(int *));
	exec_str = (char ***)ft_calloc(execl->valid_cmds, sizeof(char **));
	if (!fd || !exec_str)
	{
		if (fd)
			free(fd);
		if (exec_str)
			free(exec_str);
		return (0);
	}
	//ft_printf("All mallocs succesfull\n");
	sig_handlerr(3);
	/*if (execl->valid_cmds)
		printf("valid_cmds = %d\n", execl->valid_cmds);
	else
		printf("there are no valid_cmds\n");*/
	init_exec(execl, fd); // V
	get_exec_str(execl, exec_str); // V
	printf("in exit stt is %d\n", (*execl->exit_stt));
	printf("entering exec loop\n\n\n");
	exec_loop(execl, fd, exec_str); // (*execl->exit_stt) = exec loop
	/*if (execl->my_envp)
	{
		printf("\n\n\nenvp exists\n");
		print_db_char(execl->my_envp[0]);
	}
	else
		printf("envp is NULL somehow\n");*/
	//ft_printf("after exec loop env = %s\n", execl->my_envp[0][51]);
	end_exec(execl, fd, exec_str); // X
	printf("out exec. exit stt is %d\n", (*execl->exit_stt));
	printf("out exec global is %d\n", g_sig);
	return (1);
}

/*
receber do exec_loop

open all redirs
usando errno diretamente
V permission denied - EACCES - 126
V non existant - ENOENT - 127

faltam-me testes + BLT

launch

BLT (so vai haver erro 1 then)
.-> cd (V)
.echo X
.env (V) (If you specify invalid options or arguments with env, it may result in an error,
	but these are typically related to command-line syntax rather than the command itself.)
.-> exit (parece feito, testar)
.-> export (?)
.pwd (X) (n tem erros, caga nos args a mais)
.unset (X) (n tem erros, caga nos args a mais)

testar
exit V
cd (V) ?HOME
export 
*/