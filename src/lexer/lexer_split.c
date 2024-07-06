/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:05:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_s_quote_str(t_mshell *init, size_t *i, size_t *len)
{
	if (init->in[*i] && init->in[*i] == '\'')
	{
		(*len)++;
		while (init->in[*i + *len] != '\'')
			(*len)++;
		(*len)++;
		(*i) += *len;
		init->lexer->str = ft_substr(init->in, *i - *len, *len);
		return (true);
	}
	return (false);
}

void	create_token(t_mshell *init, size_t *i)
{
	size_t	len;

	len = 0;
	if (is_s_quote_str(init, i, &len) == true)
		return ;
	else if (ft_strnstr(init->origin_in, init->in + *i, ft_strlen(init->origin_in)) && init->in[*i] != '\'')
	{
		if ((init->in[*i] == '<' && init->in[*i + 1] == '<' ) || \
		(init->in[*i] == '>' && init->in[*i + 1] == '>' ))
		{
			len = 2;
			*i += 2;
		}
		else if (init->in[*i] == '|' || init->in[*i] == '<' \
		|| init->in[*i] == '>')
		{
			len = 1;
			(*i)++;
		}
		else
			len = lexer_size_of_word(init->in, i, init);
	}
	else
		len = special_lexer_size_of_word(init->in, i, init);
	init->lexer->str = ft_lexer_substr(init->in, *i - len, len);
}

void	malloc_tokens(t_mshell *init, int i)
{
	if (init->in[i] && !init->lexer)
	{
		init->lexer = (t_lexer *)malloc(sizeof(t_lexer));
		lexer_init(init->lexer);
	}
	else if (init->in[i] && !init->lexer->next)
	{
		init->lexer->next = (t_lexer *)malloc(sizeof(t_lexer));
		lexer_init(init->lexer->next);
		init->lexer->next->prev = init->lexer;
		init->lexer = init->lexer->next;
	}
}

void	create_all_tokens(t_mshell *init, size_t i)
{
	t_lexer	*lexer_head;
	size_t	in_len;

	lexer_head = NULL;
	in_len = ft_strlen(init->in);
	while (init->in[i])
	{
		while (ft_iswhitespace(init->in[i]) && init->in[i])
			i++;
		malloc_tokens(init, i);
		if (!lexer_head)
			lexer_head = init->lexer;
		if (i < in_len - 1 && (ft_iswhitespace(init->in[i + 2]) \
				|| !init->in[i + 2]) \
				&& ((init->in[i] == '\"' && init->in[i + 1] == '\"')
				|| (init->in[i] == '\'' && init->in[i + 1] == '\'')))
		{
			init->lexer->str = ft_strdup("''");
			init->lexer->true_sign = false;
			i += 2;
		}
		else if (init->in[i] && !ft_iswhitespace(init->in[i]))
			create_token(init, &i);
	}
	init->lexer = lexer_head;
}

void	lexer_split(t_mshell *init)
{
	init->lexer = NULL;
	create_all_tokens(init, 0);
	free(init->origin_in);
	return ;
}
