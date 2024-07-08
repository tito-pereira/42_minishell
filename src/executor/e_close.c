/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_close.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:30:22 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/22 18:08:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    close_non_related(t_execlist *execl, int **fd, int i)
{
    int c;
    
    c = -1;
	//(void) i;
	while (execl->chunk[++c] != NULL)
	//while (++c < execl->valid_cmds)
    {
        if (c != i && c != (i + 1))
        {
			//ft_printf("if (%d != %i && c != (i + 1))\n", c, i);
			close(fd[c][0]);
			close(fd[c][1]);
			//ft_printf("closed fd[%d][0] = %d\n", c, fd[c][0]);
			//ft_printf("closed fd[%d][1] = %d\n", c, fd[c][1]);
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

/*
void	close_pipes(t_execlist *execl, int **fd, int i, int rel, int non_rel)
{
	int c;
    
    c = -1;
	if (non_rel == 1)
	{
		while (execl->chunk[++c] != NULL)
		{
			if (c != i && c != (i + 1))
			{
				close(fd[c][0]);
				close(fd[c][1]);
			}
		}
	}
	if (rel == 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		if ((i + 1) < execl->valid_cmds)
		{
			close(fd[i + 1][0]);
			close(fd[i + 1][1]);
		}
	}
}
*/

//-----------------------

/*void	close_all_pipes(t_execlist *execl, int **fd, int i)
{
	close_non_related(execl, fd, i);
	close(fd[i][0]);
	close(fd[i][1]);
	if ((i + 1) < execl->valid_cmds)
	{
		close(fd[i + 1][0]);
		close(fd[i + 1][1]);
	}
}*/