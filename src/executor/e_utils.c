/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 22:20:24 by marvin            #+#    #+#             */
/*   Updated: 2024/07/09 22:20:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    write_heredoc(t_execlist *execl, int **fd, int i, int *nfd)
{
    int pid;
	int	n_file;

	n_file = execl->chunk[i]->nmb_inf;
	pid = fork();
    if (pid == 0)
    {
		close_pipes(execl, fd, i, 1);
		close(nfd[0]);
		write(nfd[1], execl->chunk[i]->infiles[n_file], \
		ft_strlen(execl->chunk[i]->infiles[n_file]));
		close(nfd[1]);
		exit(0);
	}
    wait(0);
}

void	write_infile(t_execlist *execl, int **fd, int i, int *nfd)
{
	int 	pid;
	int		infile;
	char	*shovel;

	pid = fork();
    if (pid == 0)
    {
		close_pipes(execl, fd, i, 1);
		close(nfd[0]);
		infile = open(execl->chunk[i]->infiles[execl->chunk[i]->nmb_inf], \
		O_RDONLY);
		shovel = get_next_line(infile);
		while (shovel != NULL)
		{
			write(nfd[1], shovel, ft_strlen(shovel));
			free(shovel);
			shovel = get_next_line(infile);
		}
		close(infile);
		close(nfd[1]);
		exit(0);
	}
    wait(0);
}

void	blt_action_outf(t_execlist *execl, int i, int *ret, char ***exec_str)
{
	int	n_file;
	int	tmp;

	n_file = execl->chunk[i]->nmb_outf;
	if (execl->chunk[i]->app_dcs[n_file] == 1)
		tmp = open(execl->chunk[i]->outfiles[n_file], \
		O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (execl->chunk[i]->app_dcs[n_file] == 0)
		tmp = open(execl->chunk[i]->outfiles[n_file], \
		O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(tmp, STDOUT_FILENO);
	close(tmp);
	*ret = blt_central(execl, i, exec_str[i]);
	close(tmp);
}

void	receive_new_env(t_execlist **execl)
{
	close((*execl)->env_pipe[1]);
	free_db_str((*execl)->my_envp[0]);
	(*execl)->my_envp = read_from_pipe((*execl)->env_pipe[0], *execl);
	close((*execl)->env_pipe[0]);
}