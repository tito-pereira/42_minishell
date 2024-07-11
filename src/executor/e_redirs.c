/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:29:03 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/11 11:04:09 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_ex_code(int *exit_code, char *str)
{
	if (errno == EACCES)
	{
		ft_printf("minishell: %s: Permission denied\n", str);
		*exit_code = 1;
	}
	else if (errno == ENOENT)
	{
		ft_printf("minishell: %s: No such file or directory\n", str);
		*exit_code = 1;
	}
	else
	{
		ft_printf("minishell: unspecified file redirection error\n");
		*exit_code = 1;
	}
}

int	init_redirs(t_chunk *chunk, int *nfile, int *tmp, int mode)
{
	if (mode == 1)
		*nfile = chunk->nmb_inf;
	else if (mode == 2)
		*nfile = chunk->nmb_outf;
	*tmp = 0;
	return (-1);
}

int	open_all_infs(t_chunk *chunk, t_execlist *execl)
{
	int	i;
	int	tmp;
	int	nfile;

	i = init_redirs(chunk, &nfile, &tmp, 1);
	if (chunk->infiles)
	{
		while (++i <= nfile)
		{
			if (chunk->here_dcs[i] == 0)
			{
				tmp = open(chunk->infiles[i], O_RDONLY);
				if (tmp == -1)
				{
					get_ex_code(execl->exit_stt, chunk->infiles[i]);
					return (-1);
				}
				if (tmp != -1)
					close(tmp);
			}
		}
	}
	return (0);
}

int	open_all_outfs(t_chunk *c, t_execlist *execl)
{
	int	i;
	int	tmp;
	int	nfile;

	i = init_redirs(c, &nfile, &tmp, 2);
	if (c->outfiles != NULL)
	{
		while (++i <= nfile)
		{
			if (c->app_dcs[i] == 0)
				tmp = open(c->outfiles[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (c->app_dcs[i] == 1)
				tmp = open(c->outfiles[i], O_RDWR | O_CREAT | O_APPEND, 0644);
			if (tmp == -1)
			{
				get_ex_code(execl->exit_stt, c->outfiles[i]);
				return (-1);
			}
			if (tmp != -1)
				close(tmp);
		}
	}
	return (0);
}

int	open_all_redirs(t_execlist *execl)
{
	int	c;

	c = -1;
	while (execl->chunk[++c])
	{
		if (execl->chunk[c]->infiles != NULL)
		{
			if (open_all_infs(execl->chunk[c], execl) != 0)
				return ((*execl->exit_stt));
		}
		if (execl->chunk[c]->outfiles != NULL)
		{
			if (open_all_outfs(execl->chunk[c], execl) != 0)
				return ((*execl->exit_stt));
		}
	}
	return (0);
}
