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