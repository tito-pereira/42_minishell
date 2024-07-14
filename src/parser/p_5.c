/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:51:26 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/14 02:02:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// (5) - commands && arguments separator by whitespaces + quotes handler

int	arg_separator(t_execlist *execl)
{
	int		c;
	int		ret;

	c = -1;
	while (execl->chunk[++c] != NULL)
	{
		ret = cmd_separator(execl->chunk[c]);
		if (ret == 0)
		{
			if (!execl->chunk[c]->infiles && !execl->chunk[c]->outfiles)
			{
				ft_printf("minishell: syntax error near unexpected token `|'\n");
				*(execl->exit_stt) = 2;
				return (0);
			}
			//printf("chunk %d is empty\n", c);
			//return (1); // antes, 0
			continue ;
		}
		else if (ret == -1)
		{
			ft_printf("minishell: unclosed quotes\n");
			*(execl->exit_stt) = 1;
			return (0);
		}
		//printf("final cmd & args[%c]:\n", c);
		//printf("[0]: '%s'\n", execl->chunk[c]->cmd_n_args[0]);
		//printf("[1]: '%s'\n", execl->chunk[c]->cmd_n_args[1]);
	}
	return (1);
}

void	create_cmds(t_chunk *chunk, char **str)
{
	//printf("create\n");
	chunk->cmd_n_args = malloc(2 * sizeof(char *));
	chunk->cmd_n_args[0] = *str;
	if (chunk->cmd_n_args[0] == NULL)
		chunk->cmd_n_args[0] = ft_strdup("");
	chunk->cmd_n_args[1] = NULL;
}

void	add_arg(t_chunk *chunk, char **str)
{
	int		c;
	char	**new;

	c = 0; //0
	//printf("adding '%s' string\n", *str);
	if (chunk->cmd_n_args == NULL)
	{
		create_cmds(chunk, str);
		/*chunk->cmd_n_args = malloc(2 * sizeof(char *));
		chunk->cmd_n_args[0] = *str;
		if (chunk->cmd_n_args[0] == NULL)
			chunk->cmd_n_args[0] = ft_strdup("");
		chunk->cmd_n_args[1] = NULL;*/
	}
	else
	{
		//printf("exist\n");
		while (chunk->cmd_n_args[c] != NULL)
			c++;
		new = malloc((c + 2) * sizeof(char *));
		c = -1;
		while (chunk->cmd_n_args[++c] != NULL)
			new[c] = ft_strdup(chunk->cmd_n_args[c]);
		new[c] = *str;
		new[c + 1] = NULL;
		chunk->cmd_n_args = free_db_str(chunk->cmd_n_args);
		chunk->cmd_n_args = new;
	}
}
