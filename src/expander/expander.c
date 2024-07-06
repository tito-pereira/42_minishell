/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:14:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_aux(char *alph_exit_code)
{
	free(alph_exit_code);
	return (0);
}

void	expand(t_mshell *init, t_lexer *lex_nd, t_env *env_nd, int *exit_code)
{
	char		*i_inp;
	t_expand	*i_exp;
	char		*alph_exit_code;

	i_inp = lex_nd->str;
	i_exp = init->exp;
	alph_exit_code = ft_itoa(*exit_code);
	if (env_nd == NULL && (i_inp[i_exp->i] != '$' || \
	i_inp[i_exp->i + 1] != '?' || i_exp->s_quote != 1))
		clear_macro(init, lex_nd);
	else
	{
		i_exp->new_input = ft_strldup(i_inp, i_exp->i);
		if (i_inp[i_exp->i] == '$' && i_inp[i_exp->i + 1] == '?' \
		&& i_exp->s_quote == 1)
			i_exp->new_input = ft_strupdate(i_exp->new_input, alph_exit_code);
		else
			i_exp->new_input = ft_strupdate(i_exp->new_input, \
			env_nd->content);
		i_exp->new_input = ft_strupdate(i_exp->new_input, \
		i_inp + i_exp->i + i_exp->macro_len);
		update_input(init, lex_nd);
		lex_nd->true_sign = false;
	}
	i_exp->i = expand_aux(alph_exit_code);
}

void	expander(t_mshell *init, int *ext_cd, t_env *env_nd, t_lexer *lex_nd)
{
	while (lex_nd)
	{
		init->exp = (t_expand *)malloc(sizeof(t_expand));
		expander_init(init->exp);
		while (lex_nd->str[init->exp->i])
		{
			env_nd = macro_check_fetch(init, init->env_table, lex_nd);
			if (lex_nd->str[init->exp->i] == '<' && \
			lex_nd->str[init->exp->i + 1] == '<')
				ignore_eof_macro(init, lex_nd);
			else if (lex_nd->str[init->exp->i] == '$' && \
			(!lex_nd->str[init->exp->i + 1] || (lex_nd->str[init->exp->i + 1] \
			&& (ft_iswhitespace(lex_nd->str[init->exp->i + 1]) || \
			lex_nd->str[init->exp->i + 1] == '\"') && init->exp->s_quote == 1)))
				init->exp->i++;
			else if (lex_nd->str[0] == '\'')
			{
				char *temp = ft_strdup(lex_nd->str);
				free(lex_nd->str);
				lex_nd->str = ft_substr(temp, 1, ft_strlen(temp) - 2);
				free(temp);
			}
			else if (lex_nd->str[init->exp->i] != '$' || \
				(lex_nd->str[init->exp->i] == \
			'$' && init->exp->s_quote == 0))
				init->exp->i++;
			else
				expand(init, lex_nd, env_nd, ext_cd);
		}
		lex_nd = lex_nd->next;
		free(init->exp);
	}
}
