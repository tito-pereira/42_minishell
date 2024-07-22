/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:44:10 by marvin            #+#    #+#             */
/*   Updated: 2024/05/22 22:44:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_char_p(char **old, char *n_str)
{
	char	**new;
	int		i;

	i = 0;
	while (old[i] != NULL)
		i++;
	new = (char **)ft_calloc((i + 2), sizeof(char *));
	i = -1;
	while (old[++i] != NULL)
		new[i] = ft_strdup(old[i]);
	new[i] = n_str;
	new[++i] = NULL;
	free_db_str(old);
	old = NULL;
	return (new);
}

int	*add_int_p(int *old, int flag)
{
	int		*new;
	int		i;

	i = 0;
	while (old[i] != -1)
		i++;
	new = (int *)ft_calloc((i + 2), sizeof(int));
	i = -1;
	while (old[++i] != -1)
		new[i] = old[i];
	new[i] = flag;
	new[++i] = -1;
	free(old);
	old = NULL;
	return (new);
}

void	update_char_p(char ***in_or_out, char *n_str, int *c)
{
	if (*c == -1)
	{
		*in_or_out = (char **)ft_calloc(2, sizeof(char *));
		(*in_or_out)[0] = n_str;
		(*in_or_out)[1] = NULL;
		(*c)++;
	}
	else
	{
		*in_or_out = add_char_p(*in_or_out, n_str);
		(*c)++;
	}
}

void	update_int_p(int **in_or_out, int flag, int c)
{
	if (c == 0)
	{
		*in_or_out = (int *)ft_calloc(2, sizeof(int));
		(*in_or_out)[0] = flag;
		(*in_or_out)[1] = -1;
	}
	else
		*in_or_out = add_int_p(*in_or_out, flag);
}

void	updt_rdr_lst(t_chunk *chunk, int in_out, int flag, char *n_str)
{
	if (in_out == 0)
	{
		update_char_p(&(chunk->infiles), n_str, &(chunk->nmb_inf));
		update_int_p(&(chunk->here_dcs), flag, chunk->nmb_inf);
	}
	else if (in_out == 1)
	{
		update_char_p(&(chunk->outfiles), n_str, &(chunk->nmb_outf));
		update_int_p(&(chunk->app_dcs), flag, chunk->nmb_outf);
	}
}
