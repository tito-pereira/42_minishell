/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:40 by marvin            #+#    #+#             */
/*   Updated: 2024/07/11 00:36:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_delim_error(t_execlist *execl, char *delim)
{
	if (ft_strncmp(delim, "<", 5) == 0)
		(*execl->exit_stt) = 40;
	else if (ft_strncmp(delim, "<<", 5) == 0)
		(*execl->exit_stt) = 45;
	else if (ft_strncmp(delim, ">", 5) == 0)
		(*execl->exit_stt) = 50;
	else if (ft_strncmp(delim, ">>", 5) == 0)
		(*execl->exit_stt) = 55;
	else if ((ft_strncmp(delim, "\"", 5) == 0)
		|| (ft_strncmp(delim, "'", 5) == 0))
		(*execl->exit_stt) = 10;
	if (ft_strncmp(delim, "<", 5) == 0 || ft_strncmp(delim, "<<", 5) == 0
		|| ft_strncmp(delim, ">", 5) == 0 || ft_strncmp(delim, ">>", 5) == 0
		|| ft_strncmp(delim, "\"", 5) == 0 || ft_strncmp(delim, "'", 5) == 0)
		return (0);
	return (1);
}

int	input_redir(int i, char *nwe, t_execlist *execl, int c)
{
	int	ret;
	
	i++;
	if (execl->chunk[c]->og[i] == '<')
	{
		execl->chunk[c]->heredoc = 1;
		while ((execl->chunk[c]->og[++i] == 9 || execl->chunk[c]->og[i] == 32)
			&& execl->chunk[c]->og[i] != '\0')
			continue ;
		if (execl->chunk[c]->og[i] == '\0' && empty_hd_err(&execl, c) == 1)
			return (-1);
		ret = valid_delim(&execl, c, i, &nwe);
		return (ret);
	}
	else if (execl->chunk[c]->og[i] != '<')
	{
		execl->chunk[c]->heredoc = 0;
		nwe = get_name(execl->chunk[c]->og, i, execl, c);
		if (nwe == NULL)
			return (-1);
		updt_rdr_lst(execl->chunk[c], 0, 0, nwe);
	}
	return (1);
}

int	output_redir(int i, char *nwe, t_execlist *execl, int c)
{
	i++;
	if(execl->chunk[c]->og[i] == '>')
	{
		i++;
		execl->chunk[c]->append = 1;
		nwe = get_name(execl->chunk[c]->og, i, execl, c);
		if (nwe == NULL)
			return (-1);
		updt_rdr_lst(execl->chunk[c], 1, 1, nwe);
		i--;
	}
	if (execl->chunk[c]->og[i] != '>')
	{
		execl->chunk[c]->append = 0;
		nwe = get_name(execl->chunk[c]->og, i, execl, c);
		if (nwe == NULL)
			return (-1);
		updt_rdr_lst(execl->chunk[c], 1, 0, nwe);
	}
	return(1);
}
