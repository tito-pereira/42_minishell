/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_outf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:25:54 by tibarbos          #+#    #+#             */
/*   Updated: 2024/06/28 19:47:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
void	ex_end(char *buff, int *nfd)
{
	if (buff)
		free(buff);
	if (nfd)
		free(nfd);
	buff = NULL;
	nfd = NULL;
}
*/
/*
void	ex_redir_file(t_execlist *execl, int i, char *buff, int *nfd, \
	char ***exec_str)
{
	int	tmp;
	int	n_file;

	tmp = 0;
	n_file = execl->chunk[i]->nmb_outf;
	if (buff)
		temp_pipe(nfd, buff); //cria o artifical infile e dup2 input
	//ex_end(buff, nfd);
	if (execl->chunk[i]->app_dcs[n_file] == 1) //append
		tmp = open(execl->chunk[i]->outfiles[n_file], \
		O_RDWR | O_CREAT | O_APPEND, 0644);
	else // truncate
		tmp = open(execl->chunk[i]->outfiles[n_file], \
		O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(tmp, STDOUT_FILENO);
	close(tmp); //depois de dup, fecha-se
	execve(exec_str[i][0], exec_str[i], *(execl->my_envp));
}
*/
/* 
nem sei se execl->chunk[i]->append ainda está em uso ou se é
execl->chunk[i]->app_dcs[n_file] == 1
*/
/*
void	ex_redir_pipe(int **fd, int i, char *buff, int *nfd)
{
	if (buff)
		temp_pipe(nfd, buff);
	dup2(fd[i + 1][1], STDOUT_FILENO);
	close(fd[i + 1][1]);
}

void	ex_outfile(t_execlist *execl, int **fd, int i, char ***exec_str)
{
	char	*buff;
	int		*nfd;
	int 	pid;
	
	printf("inside outfile in [%d]\n", i);
	buff = empty_pipe(fd[i][0], execl, i);
	//printf("buff:%s;\n", buff);
	nfd = ft_calloc(2, sizeof(int));
	pid = fork();
	if (pid == 0)
	{
		if ((i + 1) < execl->valid_cmds) //sera que é valid_cmds ou cmd_nmb?
			close(fd[i + 1][1]);
		//if (execl->chunk[i]->blt == 0)
		ex_redir_file(execl, i, buff, nfd, exec_str);
	}
	wait(NULL);
	if ((i + 1) < execl->valid_cmds) //outfile inside pipeline
	{
		//printf("inside last if in [%d]\n", i);
		ex_redir_pipe(fd, i, buff, nfd);
		//execve(exec_str[i][0], exec_str[i], *(execl->my_envp));
		ex_end(buff, nfd);
	}
}
*/
/*
- file output redirections override pipe redirections
- input redirections work in every single fucking pipe

X buff
X nfd
X fork
V redir file
V redir pipe

(a dupla distribuicao do buff e esvaziar infiles)
- outfiles sem pipes
	- com infile
	- sem infile
- outfiles com pipes
	- com infile
	- sem infile

ou seja tenho que testar outfile + outpipe.. ok lets see
(acho que esta funcao inteira é para qualquer tipo de outfiles)
(V) cat <example>f1|cat <example>f2
pwd >f1 >f2 >f3 | cat <example >f4 >f5
pwd >f1 >f2 >>f3 | cat <example >f4 >>f5
echo stuff >f1>f1|cat <example>f3>f4|pwd >f5>f6
tou ainda no cat <example >f1 | cat <example >f2

temp pipe
como eu esvaziei o original infile, crio um pipe artificial só
para simular um infile e ter um actual file descriptor para usar como
dup2*/