/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_action.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:10 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/09 22:29:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	input_end(int **fd, int **nfd, int i)
{
	close((*nfd)[0]);
	close((*nfd)[1]);
	free(*nfd);
	close(fd[i][1]);
	close(fd[i][0]);
}

void	exec_input(t_execlist *execl, int **fd, int i)
{
	int	n_file;
	int	*nfd;

	n_file = execl->chunk[i]->nmb_inf;
	nfd = (int *)ft_calloc(2, sizeof(int));
	pipe(nfd);
    close_pipes(execl, fd, i, 2);
	if (execl->chunk[i]->infiles && execl->chunk[i]->here_dcs[n_file] == 1 )
	{
        write_heredoc(execl, fd, i, nfd);
		dup2(nfd[0], STDIN_FILENO);
	}
    else if (execl->chunk[i]->infiles && execl->chunk[i]->here_dcs[n_file] == 0)
    {
		write_infile(execl, fd, i, nfd);
		dup2(nfd[0], STDIN_FILENO);
    }
	else if (!execl->chunk[i]->infiles && i > 0)
        dup2(fd[i][0], STDIN_FILENO);
	input_end(fd, &nfd, i);
}

void	ex_redir_file(t_execlist *execl, int i)
{
	int	tmp;
	int	n_file;

	tmp = 0;
	n_file = execl->chunk[i]->nmb_outf;
	if (execl->chunk[i]->app_dcs[n_file] == 1)
		tmp = open(execl->chunk[i]->outfiles[n_file], \
		O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		tmp = open(execl->chunk[i]->outfiles[n_file], \
		O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(tmp, STDOUT_FILENO);
	close(tmp);
}

void	exec_output(t_execlist *execl, int **fd, int i)
{
	if ((i + 1) < execl->valid_cmds)
		close(fd[i + 1][0]);
	if (execl->chunk[i]->outfiles != NULL)
	{
		ex_redir_file(execl, i);
		return ;
	}
	else if ((i + 1) < execl->valid_cmds && execl->chunk[i]->outfiles == NULL)
		dup2(fd[i + 1][1], STDOUT_FILENO);
	if ((i + 1) < execl->valid_cmds)
		close(fd[i + 1][1]);
}
