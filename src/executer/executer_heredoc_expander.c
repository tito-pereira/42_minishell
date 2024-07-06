/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_heredoc_expander.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:15:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*heredoc_fetch_macro(t_mshell *init, char **input, t_env *env_node)
{
	init->exp->macro_len = 1;
	while ((*input)[init->exp->i + init->exp->macro_len] && \
	!ft_iswhitespace((*input)[init->exp->i + \
	init->exp->macro_len]) && (*input)[init->exp->i + \
	init->exp->macro_len] != '\"' \
	&& (*input)[init->exp->i + init->exp->macro_len] != '\'' && \
	(*input)[init->exp->i + init->exp->macro_len] != '$')
		init->exp->macro_len++;
	while (env_node && (ft_strncmp((*input) + init->exp->i + 1, \
	env_node->var, init->exp->macro_len - 1) != 0 || \
	(int)ft_strlen(env_node->var) != init->exp->macro_len - 1))
		env_node = env_node->next;
	return (env_node);
}

void	heredoc_clear_macro(t_mshell *init, char **input)
{
	init->exp->new_input = ft_strldup(*input, init->exp->i);
	init->exp->new_input = ft_strupdate(init->exp->new_input, \
	(*input) + init->exp->i + init->exp->macro_len);
	free(*input);
	*input = ft_strdup(init->exp->new_input);
	free(init->exp->new_input);
}

t_env	*heredoc_macro_check_and_fetch(t_mshell *init, char **input, \
			t_env *env_node)
{
	if ((*input)[init->exp->i] == '$' && (*input)[init->exp->i \
	+ 1] && !ft_iswhitespace((*input)[init->exp->i + 1]) && init->\
	in[init->exp->i + 1] != '\"')
		env_node = heredoc_fetch_macro(init, input, env_node);
	return (env_node);
}

void	heredoc_expand(t_mshell *init, char **input, t_env *env_node, \
			int *exit_code)
{
	t_expand	*i_exp;
	char		*alph_exit_code;

	i_exp = init->exp;
	alph_exit_code = ft_itoa(*exit_code);
	if (env_node == NULL && ((*input)[i_exp->i] != '$' || \
	(*input)[i_exp->i + 1] != '?' || i_exp->s_quote != 1))
		heredoc_clear_macro(init, input);
	else
	{
		i_exp->new_input = ft_strldup(*input, i_exp->i);
		if ((*input)[i_exp->i] == '$' && (*input)[i_exp->i + 1] == '?' \
		&& i_exp->s_quote == 1)
			i_exp->new_input = ft_strupdate(i_exp->new_input, alph_exit_code);
		else
			i_exp->new_input = ft_strupdate(i_exp->new_input, \
			env_node->content);
		i_exp->new_input = ft_strupdate(i_exp->new_input, \
		(*input) + i_exp->i + i_exp->macro_len);
		free(*input);
		*input = ft_strdup(init->exp->new_input);
		free(init->exp->new_input);
	}
	free(alph_exit_code);
	i_exp->i = 0;
}

void	heredoc_expander(t_mshell *init, char **input, int *exit_code)
{
	t_env	*env_node;

	init->exp = (t_expand *)malloc(sizeof(t_expand));
	expander_init(init->exp);
	while ((*input)[init->exp->i])
	{
		env_node = init->env_table;
		env_node = heredoc_macro_check_and_fetch(init, input, env_node);
		if ((*input)[init->exp->i] == '$' && (*input)[init->exp->i + 1] \
		&& (ft_iswhitespace((*input)[init->exp->i + 1]) || \
		(*input)[init->exp->i + 1] == '\"') && init->exp->s_quote == 1)
			init->exp->i++;
		else if ((*input)[init->exp->i] != '$' || ((*input)[init->exp->i] == \
		'$' && init->exp->s_quote == 0))
			init->exp->i++;
		else
			heredoc_expand(init, input, env_node, exit_code);
	}
	free(init->exp);
}
