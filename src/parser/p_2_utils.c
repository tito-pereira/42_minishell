/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:53:23 by marvin            #+#    #+#             */
/*   Updated: 2024/07/09 19:53:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unc_qts_err(t_execlist **execl)
{
	ft_printf("minishell: unclosed quotes\n");
	*((*execl)->exit_stt) = 1;
	return (0);
}

int	empty_hd_err(t_execlist **execl, int c)
{
	if ((*execl)->chunk[c + 1])
		(*(*execl)->exit_stt) = 30;
	else if (!(*execl)->chunk[c + 1])
		(*(*execl)->exit_stt) = 20;
	return (1);
}

int	valid_delim(t_execlist **execl, int c, int i, char **nwe)
{
	if ((*execl)->chunk[c]->delimiter != NULL)
		free((*execl)->chunk[c]->delimiter);
	(*execl)->chunk[c]->delimiter = get_name((*execl)->chunk[c]->og, \
	i, *execl, c);
	if ((*execl)->chunk[c]->delimiter == NULL
		|| check_delim_error((*execl), (*execl)->chunk[c]->delimiter) == 0)
		return (-1);
	*nwe = heredoc_read((*execl)->chunk[c]->delimiter);
	if (*nwe == NULL)
		return (130);
	updt_rdr_lst((*execl)->chunk[c], 0, 1, *nwe);
	return (1);
}
