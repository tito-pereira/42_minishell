/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_6.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:35:51 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/14 03:08:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// (6) - builtin vs shell command identifier + absolute/relative paths handler

int	check_absolute(t_chunk *chunk)
{
	int	i;

	i = 0;
	//printf("abso\n"); //
	while (chunk->cmd_n_args && chunk->cmd_n_args[0]
		&& chunk->cmd_n_args[0][i] && chunk->cmd_n_args[0][i] != '\0')
		i++;
	//printf("lute\n"); //
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

int	check_empty(t_execlist *execl, int i)
{
	printf("check empty %d\n", i);
	printf("'%s'\n", execl->chunk[i]->cmd_n_args[0]);
	/*if (execl->chunk[i]->cmd_n_args)
		printf("step 1\n");
	if (execl->chunk[i]->cmd_n_args[0])
		printf("step 2\n");
	if (execl->chunk[i]->cmd_n_args[0] == NULL)
		printf("step 3\n");*/
	//&& execl->chunk[i]->cmd_n_args[0]
	if (execl->chunk[i]->cmd_n_args && execl->chunk[i]->cmd_n_args[0] == NULL)
	{
		ft_printf("'': invalid command\n", \
		execl->chunk[i]->cmd_n_args[0]);
		if (execl->chunk[i]->cmd_n_args)
			free_db_str(execl->chunk[i]->cmd_n_args);
		execl->chunk[i]->cmd_n_args = NULL;
		*(execl->exit_stt) = 127;
		return (0);
	}
	return (1);
}

void	check_p6_error(t_execlist *execl, int i, int r)
{
	if (r == 0)
	{
		if (ft_strncmp(execl->chunk[i]->cmd_n_args[0], "", 1) == 0)
			ft_printf("'%s': invalid command\n", \
			execl->chunk[i]->cmd_n_args[0]);
		else
			ft_printf("%s: invalid command\n", \
			execl->chunk[i]->cmd_n_args[0]);
		//if (execl->chunk[i]->infiles || execl->chunk[i]->outfiles)
		if (execl->chunk[i]->cmd_n_args)
			free_db_str(execl->chunk[i]->cmd_n_args);
		execl->chunk[i]->cmd_n_args = NULL;
		if (!execl->chunk[i + 1]) //more commands after
			*(execl->exit_stt) = 127;
	}
}

int	arg_id(t_execlist *execl)
{
	int	i;
	int	r;

	i = -1;
	//printf("inside p6\n"); //
	//printf("cmd is actually '%s'\n", execl->chunk[0]->cmd_n_args[0]);
	while (execl->chunk[++i] != NULL)
	{
		if (i == 0)
			execl->chunk[i]->inpipe = 1;
		if (execl->chunk[i] && !execl->chunk[i]->cmd_n_args) //|| (check_empty(execl, i) == 0))//
			continue ; //
		if (check_absolute(execl->chunk[i]) == 0)
		{
			execl->chunk[i]->blt = \
			check_builtin(execl->chunk[i]->cmd_n_args[0]);
			if (execl->chunk[i]->blt == 1)
				r = chunk_id(execl->chunk[i], 1);
			else if (execl->chunk[i]->blt == 0)
				r = chunk_id(execl->chunk[i], 2);
			check_p6_error(execl, i, r); //if == 0, return 0
		}
	}
	return (1);
}

/*
int	check_p6_error(t_execlist *execl, int i, int r)
{
	if (r == 128)
	{
		ft_printf("'': invalid command\n", \
		execl->chunk[i]->cmd_n_args[0]);
		if (execl->chunk[i]->cmd_n_args)
			free_db_str(execl->chunk[i]->cmd_n_args);
		execl->chunk[i]->cmd_n_args = NULL;
		*(execl->exit_stt) = 127;
	}
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
*/