/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:14:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*settle_eof(t_mshell *init, char *eof)
{
	init->expand_heredoc = true;
	if ((eof[0] == '\'' && eof[ft_strlen(eof) - 1] == '\'') || \
	(eof[0] == '\"' && eof[ft_strlen(eof) - 1] == '\"'))
	{
		init->expand_heredoc = false;
		if (init->eof)
			free(init->eof);
		init->eof = ft_strldup(eof + 1, ft_strlen(eof) - 2);
	}
	else
	{
		if (init->eof)
			free(init->eof);
		init->eof = ft_strdup(eof);
	}
	return (init->eof);
}
