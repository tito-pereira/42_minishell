/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2e.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:48:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/10 03:48:04 by marvin           ###   ########.fr       */
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

int	gt_nm_errors(t_execlist **execl, char *str, int i, int c)
{
	if (str[i] == '\0')
	{
		if (execl->chunk[c + 1])
			(*execl->exit_stt) = 30;
		else if (!execl->chunk[c + 1])
			(*execl->exit_stt) = 20;
		return (0);
	}
	if (get_name_errors(execl, str, i) == 0)
		return (0);
	return (1);
}

char	*get_name(char *str, int i, t_execlist *execl, int c)
{
	int		flag;
	char	*chest;

	while (str[i] == 9 || str[i] == 32)
		i++;
	/*if (str[i] == '\0')
	{
		if (execl->chunk[c + 1])
			(*execl->exit_stt) = 30;
		else if (!execl->chunk[c + 1])
			(*execl->exit_stt) = 20;
		return (NULL);
	}
	if (get_name_errors(execl, str, i) == 0)
		return (NULL);*/
	if (gt_nm_errors(execl, str, i, c) == 0)
		return (NULL);
	flag = 0;
	chest = NULL;
	while (str[i] != '\0')
	{
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

/*
dividir a getname
*/