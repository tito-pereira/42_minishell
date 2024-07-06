/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:14:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer_router(t_lexer *tokens)
{
	while (tokens)
	{
		if (!tokens->str)
			tokens->operator = CMD;
		else if (!ft_strcmp(tokens->str, "|"))
			tokens->operator = PIPE;
		else if (!ft_strcmp(tokens->str, ">"))
			tokens->operator = OUT_OWR;
		else if (!ft_strcmp(tokens->str, ">>"))
			tokens->operator = OUT_APND;
		else if (!ft_strcmp(tokens->str, "<"))
			tokens->operator = IN_READ;
		else if (!ft_strcmp(tokens->str, "<<"))
			tokens->operator = IN_HDOC;
		else
			tokens->operator = CMD;
		tokens = tokens->next;
	}
}

int	lexer_main(t_mshell *init, char ***envp_copy, int *exit_code)
{
	if (g_signo == 130)
		*exit_code = 130;
	if (ft_strlen(init->in) > 0)
	{
		lexer_split(init);
		lexer_router(init->lexer);
		expander(init, exit_code, NULL, init->lexer);
		if (new_var_checker(init, envp_copy) == 0)
			return (1);
	}
	return (0);
}
