/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:40 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 16:31:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	getname_chest(char **chest, char c)
{
	char	*old;
	char	*input;

	input = (char *)ft_calloc(2, sizeof(char));
	input[0] = c;
	input[1] = '\0';
	if (!(*chest))
		*chest = ft_strdup(input);
	else
	{
		old = *chest;
		*chest = ft_strjoin(*chest, input);
		free (old);
	}
	free(input);
}

int		get_name_errors(t_execlist *execl, char *str, int i)
{
	if (str[i] == '<')
	{
		if (str[i + 1] && str[i + 1] == '<')
			(*execl->exit_stt) = 45;
		else if (str[i + 1] && str[i + 1] != '<')
			(*execl->exit_stt) = 40;
		return (0);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] && str[i + 1] == '>')
			(*execl->exit_stt) = 55;
		else if (str[i + 1] && str[i + 1] != '>')
			(*execl->exit_stt) = 50;
		return (0);
	}
	return (1);
}

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
		if (str[i] == 34 && flag == 0)
			flag = 34;
		else if (str[i] == 34 && flag == 34)
			flag = 0;
		else if (str[i] == 39 && flag == 0)
			flag = 39;
		else if (str[i] == 39 && flag == 39)
			flag = 0;
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

int	input_redir(t_chunk *chunk, int i, char *nwe, t_execlist *execl, int c)
{
	i++;
	if (chunk->og[i] == '<')
	{
		chunk->heredoc = 1;
		while ((chunk->og[++i] == 9 || chunk->og[i] == 32)
			&& chunk->og[i] != '\0')
			continue ;
		if (chunk->og[i] == '\0')
		{
			if (execl->chunk[c + 1])
				(*execl->exit_stt) = 30;
			else if (!execl->chunk[c + 1])
				(*execl->exit_stt) = 20;
			return (-1);
		}
		if (chunk->delimiter != NULL)
			free(chunk->delimiter);
		chunk->delimiter = get_name(chunk->og, i, execl, c);
		if (chunk->delimiter == NULL
			|| check_delim_error(execl, chunk->delimiter) == 0)
			return (-1);
		nwe = heredoc_read(chunk->delimiter);
		if (nwe == NULL)
			return (130);
		updt_rdr_lst(chunk, 0, 1, nwe);
	}
	else if (chunk->og[i] != '<')
	{
		chunk->heredoc = 0;
		nwe = get_name(chunk->og, i, execl, c);
		if (nwe == NULL)
			return (-1);
		updt_rdr_lst(chunk, 0, 0, nwe);
	}
	return (1);
}

int	output_redir(t_chunk *chunk, int i, char *nwe, t_execlist *execl, int c)
{
	i++;
	if(chunk->og[i] == '>')
	{
		i++;
		chunk->append = 1;
		nwe = get_name(chunk->og, i, execl, c);
		if (nwe == NULL)
			return (-1);
		updt_rdr_lst(chunk, 1, 1, nwe);
		i--;
	}
	if (chunk->og[i] != '>')
	{
		chunk->append = 0;
		nwe = get_name(chunk->og, i, execl, c);
		if (nwe == NULL)
			return (-1);
		updt_rdr_lst(chunk, 1, 0, nwe);
	}
	return(1);
}
