/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:12:29 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/11 10:48:14 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// (4) - remove redirections from the parsing string to simplify parsing process

void	temp_strings(char *og, char **new, int a, int b)
{
	char	*first;
	char	*secnd;

	first = NULL;
	if (a != 0)
		first = ft_substr(og, 0, a);
	secnd = NULL;
	if ((b + 1) != (int)ft_strlen(og))
		secnd = ft_substr(og, b, ((int)ft_strlen(og) - b));
	*new = NULL;
	if (!first && secnd)
		*new = secnd;
	else if (first && secnd)
	{
		*new = ft_strjoin(first, secnd);
		free(first);
		free(secnd);
	}
	else if (first && !secnd)
		*new = first;
}

void	find_redirs(char *og, int *a, int *b, int *i)
{
	int	flag;

	flag = 0;
	(*a) = (*i);
	while ((og[*i] == '<' || og[*i] == '>') && og[*i] != '\0')
		(*i)++;
	while ((og[*i] == 9 || og[*i] == 32) && og[*i] != '\0')
		(*i)++;
	while (og[*i] != '\0')
	{
		parser_quote_flags(og[*i], &flag);
		if (flag == 0 && (og[*i] == 9 || og[*i] == 32))
			break ;
		(*i)++;
	}
	(*b) = (*i);
}

void	find_red_pos(t_chunk *chunk, int *i)
{
	int		a;
	int		b;
	char	*new;

	a = 0;
	b = 0;
	new = NULL;
	if (chunk->og[*i] == '<' || chunk->og[*i] == '>')
	{
		find_redirs(chunk->og, &a, &b, i);
		temp_strings(chunk->og, &new, a, b);
		if (new)
		{
			free(chunk->og);
			chunk->og = new;
		}
		(*i) = a;
		if (chunk->og[(*i) + 1]
			&& ((chunk->og[*i] == '<' && chunk->og[(*i) + 1] == '<')
				|| (chunk->og[*i] == '>' && chunk->og[(*i) + 1] == '>')))
			(*i)++;
	}
}

int	scope_redirs(t_execlist *execl)
{
	int		c;
	int		i;
	int		flag;

	c = -1;
	i = -1;
	flag = 0;
	while (execl->chunk[++c] != NULL)
	{
		i = -1;
		while (execl->chunk[c]->og[++i] != '\0')
		{
			parser_quote_flags(execl->chunk[c]->og[i], &flag);
			if (flag == 0)
				find_red_pos(execl->chunk[c], &i);
		}
	}
	return (1);
}
