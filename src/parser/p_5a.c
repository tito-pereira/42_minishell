/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_5a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:01 by marvin            #+#    #+#             */
/*   Updated: 2024/07/11 10:50:27 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	quote_handler(int option, char c, int *qt, int *qts)
{
	if (option == 1)
	{
		if (c == 39)
			*qt *= -1;
		else if (c == 34)
			*qts *= -1;
	}
	if (option == 2)
	{
		if (*qt == -1)
			return (-1);
		if (*qts == -1)
			return (-1);
	}
	return (1);
}

int	non_white(int *a, int *b, t_chunk *chunk, int *i)
{
	int	quote;
	int	quotes;

	quote = 1;
	quotes = 1;
	*a = *i;
	while ((chunk->og[*i] != '\0')
		&& ((chunk->og[*i] != 9 && chunk->og[*i] != 32)
			|| ((chunk->og[*i] == 9 || chunk->og[*i] == 32)
				&& quote_handler(2, chunk->og[*i], &quote, &quotes) == -1)))
	{
		quote_handler(1, chunk->og[*i], &quote, &quotes);
		(*i)++;
	}
	if (chunk->og[*i] == 9 || chunk->og[*i] == 32
		|| chunk->og[*i] == '\0' || (!quote && !quotes))
		*b = *i - 1;
	return (1);
}

int	cmd_separator(t_chunk *chunk)
{
	int		i;
	int		a;
	int		b;
	char	*sub;

	i = -1;
	a = 0;
	b = 0;
	while (chunk->og[++i])
	{
		if (chunk->og[i] != 9 && chunk->og[i] != 32)
		{
			if (non_white(&a, &b, chunk, &i) == -1)
				return (-1);
			sub = ft_substr(chunk->og, a, (b - a + 1));
			add_arg(chunk, &sub);
		}
		if (chunk->og[i] == '\0')
			return (1);
	}
	if (a == b && chunk->cmd_n_args == NULL)
		return (0);
	return (1);
}
