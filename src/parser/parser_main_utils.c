/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:03:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parser	**create_parser_node_aux(t_mshell *init, t_parser **node)
{
	(*node)->input = init->red_input;
	(*node)->output = init->red_output;
	(*node)->next = NULL;
	(*node)->token_err = false;
	(*node)->file_nf = false;
	return (node);
}

void	parser_main_aux1(t_mshell *init, t_lexer **lexer)
{
	if ((*lexer)->operator == PIPE)
	{
		init->parser_flag = 0;
		(*lexer) = (*lexer)->next;
	}
	if ((*lexer) && (*lexer)->str && ft_strcmp((*lexer)->str, "echo") == 0)
		init->parser_flag = 1;
}

void	parser_main_aux2(t_mshell *init, t_lexer **lexer)
{
	if (ft_strcmp((*lexer)->str, "''") == 0 && ((*lexer)->true_sign == true || \
		init->parser_flag == 1))
	{
		free((*lexer)->str);
		(*lexer)->str = ft_strdup("");
	}
	else if (!(*lexer)->str || ((*lexer)->str && ft_strlen((*lexer)->str) == 0))
	{
		free((*lexer)->str);
		if (init->parser_flag == 0 && (*lexer)->true_sign == false)
			(*lexer)->str = ft_strdup("''");
		else
		{
			(*lexer)->str = ft_strdup("^");
			init->var_nf = true;
		}
	}
}

void	parser_main_aux3(t_mshell *init)
{
	if (init->paths)
		ft_free_smatrix(init->paths);
}
