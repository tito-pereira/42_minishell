/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:14:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer_elements_aid(char const *s, size_t *i)
{
	char	quote;

	while (!ft_iswhitespace(s[*i]) && s[*i])
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			quote = s[(*i)++];
			while (s[*i] != quote && s[*i])
				(*i)++;
		}
		(*i)++;
	}
}

int	lexer_elements(char const *s)
{
	size_t	i;
	size_t	elements;

	i = 0;
	elements = 0;
	while (s[i])
	{
		while ((s[i] == '\"' && s[i + 1] == '\"') || \
		(s[i] == '\'' && s[i + 1] == '\''))
			i += 2;
		if (!ft_iswhitespace(s[i]) && s[i])
			elements++;
		lexer_elements_aid(s, &i);
		while (ft_iswhitespace(s[i]) && s[i])
			i++;
	}
	return (elements);
}
