/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:14:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*fetch_macro(t_mshell *init, t_env *env_node, t_lexer *lexer_node)
{
	init->exp->macro_len = 1;
	while (lexer_node->str[init->exp->i + init->exp->macro_len] && \
	!ft_iswhitespace(lexer_node->str[init->exp->i + \
	init->exp->macro_len]) && lexer_node->str[init->exp->i + \
	init->exp->macro_len] != '\"' \
	&& lexer_node->str[init->exp->i + init->exp->macro_len] != '\'' && \
	lexer_node->str[init->exp->i + init->exp->macro_len] != '$')
		init->exp->macro_len++;
	while (env_node && (ft_strncmp(lexer_node->str + init->exp->i + 1, \
	env_node->var, init->exp->macro_len - 1) != 0 || \
	(int)ft_strlen(env_node->var) != init->exp->macro_len - 1))
		env_node = env_node->next;
	init->exp->d_quote = 1;
	return (env_node);
}

void	update_input(t_mshell *init, t_lexer *lexer_node)
{
	free(lexer_node->str);
	lexer_node->str = ft_strdup(init->exp->new_input);
	free(init->exp->new_input);
}

void	clear_macro(t_mshell *init, t_lexer *lexer_node)
{
	init->exp->new_input = ft_strldup(lexer_node->str, init->exp->i);
	init->exp->new_input = ft_strupdate(init->exp->new_input, \
	lexer_node->str + init->exp->i + init->exp->macro_len);
	update_input(init, lexer_node);
}

t_env	*macro_check_fetch(t_mshell *init, t_env *env_nd, t_lexer *lexer_nd)
{
	if (lexer_nd->str[init->exp->i] == '\'' && init->exp->s_quote == 1 \
	&& init->exp->d_quote == 1)
		init->exp->s_quote = 0;
	else if (lexer_nd->str[init->exp->i] == '\'' && init->exp->s_quote == 0 \
	&& init->exp->d_quote == 1)
		init->exp->s_quote = 1;
	else if (lexer_nd->str[init->exp->i] == '\"' && init->exp->s_quote == 1 \
	&& init->exp->d_quote == 1)
		init->exp->d_quote = 0;
	else if (lexer_nd->str[init->exp->i] == '\"' && init->exp->s_quote == 1 \
	&& init->exp->d_quote == 0)
		init->exp->d_quote = 1;
	else if (lexer_nd->str[init->exp->i] == '$' && lexer_nd->str[init->exp->i \
	+ 1] && !ft_iswhitespace(lexer_nd->str[init->exp->i + 1]) && init->\
	in[init->exp->i + 1] != '\"')
		env_nd = fetch_macro(init, env_nd, lexer_nd);
	return (env_nd);
}

void	ignore_eof_macro(t_mshell *init, t_lexer *lexer_node)
{
	init->exp->i += 2;
	while (lexer_node->str[init->exp->i] && \
	ft_iswhitespace(lexer_node->str[init->exp->i]))
		init->exp->i++;
	while (lexer_node->str[init->exp->i] && \
	!ft_iswhitespace(lexer_node->str[init->exp->i]) && \
	(lexer_node->str[init->exp->i] != '\'' || \
		lexer_node->str[init->exp->i] != '\"'))
		init->exp->i++;
}
