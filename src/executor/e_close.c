/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_close.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:30:22 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/08 16:59:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    close_non_related(t_execlist *execl, int **fd, int i)
{
    int c;
    
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

void	close_pipes(t_execlist *execl, int **fd, int i, int rel, int non_rel)
{
	if (rel == 1)
		close_related(execl, fd, i);
	if (non_rel == 1)
		close_non_related(execl, fd, i);
}
