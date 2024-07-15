/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:47 by marvin            #+#    #+#             */
/*   Updated: 2024/07/15 14:22:13 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// (3) - environment variable expander with '$'

int	spec_char_chunk(t_execlist *execl, int j)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (execl->chunk[j]->og[i] != '\0')
	{
		if (execl->chunk[j]->og[i] == 39)
			flag *= -1;
		if (execl->chunk[j]->og[i] == '$' && flag == 1)
		{
			if (execl->chunk[j]->og[i + 1] != '\0'
				&& execl->chunk[j]->og[i + 1] != 32 \
				&& execl->chunk[j]->og[i + 1] != 34)
				h_env_var(&i, &execl->chunk[j]->og, execl);
		}
		i++;
	}
	return (1);
}

int	spec_char_infiles(t_execlist *execl, int j)
{
	int	i;
	int	flag;
	int	inf;

	inf = -1;
	while (execl->chunk[j]->infiles[++inf] != NULL)
	{
		i = -1;
		flag = 1;
		while (execl->chunk[j]->infiles[inf][++i] != '\0')
		{
			if (execl->chunk[j]->infiles[inf][i] == 39)
				flag *= -1;
			if (execl->chunk[j]->infiles[inf][i] == '$' && flag == 1)
			{
				if (execl->chunk[j]->infiles[inf][i + 1]
					&& execl->chunk[j]->infiles[inf][i + 1] != 32 \
					&& execl->chunk[j]->infiles[inf][i + 1] != 34)
					h_env_var(&i, &execl->chunk[j]->infiles[inf], execl);
			}
		}
	}
	return (1);
}

int	spec_char_outfiles(t_execlist *execl, int j)
{
	int	i;
	int	flag;
	int	out;

	out = -1;
	while (execl->chunk[j]->outfiles[++out] != NULL)
	{
		i = -1;
		flag = 1;
		while (execl->chunk[j]->outfiles[out][++i] != '\0')
		{
			if (execl->chunk[j]->outfiles[out][i] == 39)
				flag *= -1;
			if (execl->chunk[j]->outfiles[out][i] == '$' && flag == 1)
			{
				if (execl->chunk[j]->outfiles[out][i + 1]
					&& execl->chunk[j]->outfiles[out][i + 1] != 32 \
					&& execl->chunk[j]->outfiles[out][i + 1] != 34)
					h_env_var(&i, &execl->chunk[j]->outfiles[out], execl);
			}
		}
	}
	return (1);
}

int	special_char(t_execlist *execl)
{
	int		j;

	j = -1;
	while (execl->chunk[++j] != NULL)
	{
		if (spec_char_chunk(execl, j) == 0)
			return (0);
		if (execl->chunk[j]->infiles)
		{
			if (spec_char_infiles(execl, j) == 0)
				return (0);
		}
		if (execl->chunk[j]->outfiles)
		{
			if (spec_char_outfiles(execl, j) == 0)
				return (0);
		}
	}
	return (1);
}
