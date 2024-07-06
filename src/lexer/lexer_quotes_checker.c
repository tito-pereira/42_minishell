/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:05:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_hist_unquotes(char const *input)
{
	add_history(input);
	free((char *)input);
	printf("minishell: unclosed quotes\n");
}

void	quotes_checker_aid(char const *s, int *i, int *count, char quote_type)
{
	if (s[*i] == quote_type)
	{
		(*count)++;
		(*i)++;
		while (s[*i] != quote_type && s[*i])
			(*i)++;
		if (s[*i] && s[*i] == quote_type)
			(*count)++;
	}
}

int	quotes_checker(char const *s)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while ((size_t)i < ft_strlen(s))
	{
		if (s[i] == '\'')
			quotes_checker_aid(s, &i, &s_quote, '\'');
		else if (s[i] == '\"')
			quotes_checker_aid(s, &i, &d_quote, '\"');
		i++;
	}
	if (((s_quote % 2) + (d_quote % 2)) != 0)
	{
		add_hist_unquotes(s);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
