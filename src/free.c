/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:43:48 by marvin            #+#    #+#             */
/*   Updated: 2024/07/22 10:55:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_str(char *str)
{
	free(str);
	return (NULL);
}

char	**free_db_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		free_str(str[i]);
	free(str);
	return (NULL);
}

int	*free_int_arr(int *str)
{
	free(str);
	return (NULL);
}

t_chunk	*free_chunk(t_chunk *chunk)
{
	if (chunk->infiles)
		(chunk)->infiles = free_db_str(chunk->infiles);
	if (chunk->here_dcs)
		(chunk)->here_dcs = free_int_arr(chunk->here_dcs);
	if (chunk->here_file)
		(chunk)->here_file = free_str(chunk->here_file);
	if (chunk->delimiter)
		(chunk)->delimiter = free_str(chunk->delimiter);
	if (chunk->outfiles)
		(chunk)->outfiles = free_db_str(chunk->outfiles);
	if (chunk->app_dcs)
		(chunk)->app_dcs = free_int_arr(chunk->app_dcs);
	if (chunk->og)
		(chunk)->og = free_str(chunk->og);
	if (chunk->cmd_n_args)
		(chunk)->cmd_n_args = free_db_str(chunk->cmd_n_args);
	if (chunk->path)
		(chunk)->path = free_str(chunk->path);
	free(chunk);
	return (NULL);
}

t_execlist	*free_exec(t_execlist *execl, int mode)
{
	int	i;

	i = -1;
	if (!execl)
		return (NULL);
	if (execl->chunk)
	{
		while (execl->chunk[++i])
			execl->chunk[i] = free_chunk(execl->chunk[i]);
		free(execl->chunk);
	}
	if (execl->my_envp && mode == 2)
	{
		*(execl->my_envp) = free_db_str(*(execl->my_envp));
		free(*(execl->my_envp));
		execl->my_envp = NULL;
	}
	if (execl->pipe_loc)
		(execl)->pipe_loc = free_int_arr(execl->pipe_loc);
	if (execl->env_pipe)
		(execl)->env_pipe = free_int_arr(execl->env_pipe);
	free(execl);
	return (NULL);
}
