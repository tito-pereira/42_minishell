/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_close.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:30:22 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/11 10:40:23 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_non_related(t_execlist *execl, int **fd, int i)
{
	int	c;

	c = -1;
	while (execl->chunk[++c] != NULL)
	{
		if (c != i && c != (i + 1))
		{
			close(fd[c][0]);
			close(fd[c][1]);
		}
	}
}

void	close_related(t_execlist *execl, int **fd, int i)
{
	close(fd[i][0]);
	close(fd[i][1]);
	if ((i + 1) < execl->valid_cmds)
	{
		close(fd[i + 1][0]);
		close(fd[i + 1][1]);
	}
}

void	close_pipes(t_execlist *execl, int **fd, int i, int mode) //rel, non rel
{
	if (mode == 1 || mode == 3)
		close_related(execl, fd, i);
	if (mode == 2 || mode == 3)
		close_non_related(execl, fd, i);
}

/*
e_close - close_pipes (transformar aqueles related ou non numa so flag de 1 a 3)

rel 1, non rel 0 - mode 1
rel 0, non rel 1 - mode 2
rel 1, non rel 1 - mode 3
*/