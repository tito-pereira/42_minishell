/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_5a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:01 by marvin            #+#    #+#             */
/*   Updated: 2024/07/11 12:33:22 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	separator_chest(char **chest, char c)
{
	char	*old;
	char	*input;

	input = (char *)ft_calloc(2, sizeof(char));
	input[0] = c;
	input[1] = '\0';
	if (!(*chest))
		*chest = ft_strdup(input);
	else
	{
		old = *chest;
		*chest = ft_strjoin(*chest, input);
		free (old);
	}
	free(input);
}

int	separator_options(char **chest, int flag, char *str, int i)
{
	if (flag == 0 && (str[i] == 9 || str[i] == 32))
		return (0);
	if ((str[i] != 34 && str[i] != 39)
		|| (str[i] == 34 && flag == 39)
		|| (str[i] == 39 && flag == 34))
		separator_chest(chest, str[i]);
	return (1);
}

int	non_white(char **chest, t_chunk *chunk, int *i)
{
	int	flag;

	flag = 0;
	*chest = NULL;
	while (chunk->og[*i] != '\0')
	{
		parser_quote_flags(chunk->og[*i], &flag);
		if (separator_options(chest, flag, chunk->og, *i) == 0)
			break ;
		(*i)++;
	}
	if (flag != 0)
		return (-1);
	return (1);
}

int	cmd_separator(t_chunk *chunk)
{
	int		i;
	char	*chest;

	i = -1;
	chest = NULL;
	while (chunk->og[++i])
	{
		if (chunk->og[i] != 9 && chunk->og[i] != 32)
		{
			if (non_white(&chest, chunk, &i) == -1)
				return (-1);
			add_arg(chunk, &chest);
		}
		if (chunk->og[i] == '\0')
			return (1);
	}
	if (chunk->cmd_n_args == NULL)
		return (0);
	return (1);
}
