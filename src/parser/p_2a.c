/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:40 by marvin            #+#    #+#             */
/*   Updated: 2024/07/10 03:50:16 by marvin           ###   ########.fr       */
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

/*
p2a - getname, input redir

char	*get_name(char *str, int i, t_execlist *execl, int c)
{
	int		flag;
	char	*chest;

	while (str[i] == 9 || str[i] == 32)
		i++;
	if (str[i] == '\0')
	{
		if (execl->chunk[c + 1])
			(*execl->exit_stt) = 30;
		else if (!execl->chunk[c + 1])
			(*execl->exit_stt) = 20;
		return (NULL);
	}
	if (get_name_errors(execl, str, i) == 0)
		return (NULL);
	flag = 0;
	chest = NULL;
	while (str[i] != '\0')
	{
		//if (str[i] == 34 && flag == 0)
			flag = 34;
		else if (str[i] == 34 && flag == 34)
			flag = 0;
		else if (str[i] == 39 && flag == 0)
			flag = 39;
		else if (str[i] == 39 && flag == 39)
			flag = 0;//
		parser_quote_flags(str[i], &flag);
		if (flag == 0 && (str[i] == 9 || str[i] == 32
			|| str[i] == '>' || str[i] == '<'))
			break ;
		if ((str[i] != 34 && str[i] != 39)
			|| (str[i] == 34 && flag == 39)
			|| (str[i] == 39 && flag == 34))
			getname_chest(&chest, str[i]);
		i++;
	}
	if (flag != 0)
	{
		(*execl->exit_stt) = 10;
		return (NULL);
	}
	return (chest);
}


int	input_redir(int i, char *nwe, t_execlist *execl, int c)
{
	i++;
	if (execl->chunk[c]->og[i] == '<')
	{
		execl->chunk[c]->heredoc = 1;
		while ((execl->chunk[c]->og[++i] == 9 || execl->chunk[c]->og[i] == 32)
			&& execl->chunk[c]->og[i] != '\0')
			continue ;
		if (execl->chunk[c]->og[i] == '\0')
		{
			if (execl->chunk[c + 1])
				(*execl->exit_stt) = 30;
			else if (!execl->chunk[c + 1])
				(*execl->exit_stt) = 20;
			return (-1);
		}
		if (execl->chunk[c]->delimiter != NULL)
			free(execl->chunk[c]->delimiter);
		execl->chunk[c]->delimiter = get_name(execl->chunk[c]->og, i, execl, c);
		if (execl->chunk[c]->delimiter == NULL
			|| check_delim_error(execl, execl->chunk[c]->delimiter) == 0)
			return (-1);
		nwe = heredoc_read(execl->chunk[c]->delimiter);
		if (nwe == NULL)
			return (130);
		updt_rdr_lst(execl->chunk[c], 0, 1, nwe);
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
*/