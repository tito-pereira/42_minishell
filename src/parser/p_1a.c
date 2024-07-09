/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_1a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:52:51 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/09 02:17:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parser_quote_flags(char c, int *flag)
{
	if (c == 34 && *flag == 0)
		*flag = 34;
	else if (c == 34 && *flag == 34)
		*flag = 0;
	else if (c == 39 && *flag == 0)
		*flag = 39;
	else if (c == 39 && *flag == 39)
		*flag = 0;
}

void	pipe_atr_loop(t_execlist *execl, char *input, int flag, int i)
{
	int	j;

	j = 0;
	while (input[++i] != '\0')
	{
		/*if (input[i] == 34 && flag == 0)
			flag = 34;
		else if (input[i] == 34 && flag == 34)
			flag = 0;
		else if (input[i] == 39 && flag == 0)
			flag = 39;
		else if (input[i] == 39 && flag == 39)
			flag = 0;*/
		parser_quote_flags(input[i], &flag);
		if (input[i] == '|' && input[i + 1] != '|' && flag == 0)
		{
			execl->pipe_loc[j] = i;
			j++;
		}
	}
	execl->pipe_loc[j] = '\0';
}

int	pipe_cnt_loop(t_execlist *execl, char *input, int flag, int *c)
{
	int	i;

	i = -1;
	while (input[++i] != '\0')
	{
		/*if (input[i] == 34 && flag == 0)
			flag = 34;
		else if (input[i] == 34 && flag == 34)
			flag = 0;
		else if (input[i] == 39 && flag == 0)
			flag = 39;
		else if (input[i] == 39 && flag == 39)
			flag = 0;*/
		parser_quote_flags(input[i], &flag);
		if (input[i] == '|' && flag == 0)
		{
			if (input[i + 1] == '|' || i == 0 || input[i + 1] == '\0')
				return (-1);
			if (input[i + 1] != '|')
			{
				(execl->valid_cmds)++;
				(*c)++;
			}
		}
	}
	return (1);
}

int	pipe_counter(char *input, t_execlist *execl)
{
	int	c;
	//int	i;

	c = 0;
	//i = -1;
	execl->valid_cmds = 1;
	if (pipe_cnt_loop(execl, input, 0, &c) == -1)
		return (-1);
	execl->pipe_loc = malloc((execl->valid_cmds + 1) * sizeof(int));
	i = -1;
	pipe_atr_loop(execl, input, 0, i);
	return (c);
}
