/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_6.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:35:51 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/12 22:01:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// (6) - builtin vs shell command identifier + absolute/relative paths handler

int	check_absolute(t_chunk *chunk)
{
	int	i;

	i = 0;
	while (chunk->cmd_n_args[0][i] != '\0')
		i++;
	if ((i >= 1 && chunk->cmd_n_args[0][0] == '/')
		|| (i >= 1 && chunk->cmd_n_args[0][0] == '~')
		|| (i >= 2 && chunk->cmd_n_args[0][0] == '.'
		&& chunk->cmd_n_args[0][1] == '/')
		|| (i >= 3 && chunk->cmd_n_args[0][0] == '.'
		&& chunk->cmd_n_args[0][1] == '.'
		&& chunk->cmd_n_args[0][2] == '/'))
		return (1);
	return (0);
}

int	check_builtin(char *arg)
{
	if (ft_strncmp("echo", arg, 256) == 0
		|| ft_strncmp("cd", arg, 256) == 0
		|| ft_strncmp("pwd", arg, 256) == 0
		|| ft_strncmp("export", arg, 256) == 0
		|| ft_strncmp("unset", arg, 256) == 0
		|| ft_strncmp("env", arg, 256) == 0
		|| ft_strncmp("exit", arg, 256) == 0)
		return (1);
	return (0);
}

int	check_p6_error(t_execlist *execl, int i, int r)
{
	if (r == 0)
	{
		ft_printf("%s: invalid command\n", \
		execl->chunk[i]->cmd_n_args[0]);
		if (execl->chunk[i]->infiles || execl->chunk[i]->outfiles)
		{
			if (execl->chunk[i]->cmd_n_args)
				free_db_str(execl->chunk[i]->cmd_n_args);
			execl->chunk[i]->cmd_n_args = NULL;
			return (1);
		}
		*(execl->exit_stt) = 127;
		return (0);
	}
	return (1);
}

int	arg_id(t_execlist *execl)
{
	int	i;
	int	r;

	i = -1;
	while (execl->chunk[++i] != NULL)
	{
		if (i == 0)
			execl->chunk[i]->inpipe = 1;
		if (execl->chunk[i] && !execl->chunk[i]->cmd_n_args) //
			continue ; //
		if (check_absolute(execl->chunk[i]) == 0)
		{
			execl->chunk[i]->blt = \
			check_builtin(execl->chunk[i]->cmd_n_args[0]);
			if (execl->chunk[i]->blt == 1)
				r = chunk_id(execl->chunk[i], 1);
			else if (execl->chunk[i]->blt == 0)
				r = chunk_id(execl->chunk[i], 2);
			if (check_p6_error(execl, i, r) == 0)
				return (0);
		}
	}
	return (1);
}
