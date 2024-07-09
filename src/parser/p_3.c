/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:47 by marvin            #+#    #+#             */
/*   Updated: 2024/07/09 05:36:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
(3) - environment variable expander with '$'
*/

void	get_positions(int *a, int *b, int *i, char *chunk)
{
	*a = *i;
	(*i)++;
	while (chunk[*i] != 9 && chunk[*i] != 32 && chunk[*i] != '$'
		&& chunk[*i] != '\0' && chunk[*i] != 34 && chunk[*i] != '\n')
		(*i)++;
	*b = (*i) - 1;
}

char	*get_spec(int *a, int *b, char *chunk, t_execlist *execl)
{
	char	*env_name;
	char	*env_value;

	env_name = ft_substr(chunk, ((*a) + 1), ((*b) - (*a)));
	if (!env_name)
		return(NULL);
	if (env_name[0] == '?')
		env_value = ft_itoa(*(execl->exit_stt));
	else
		env_value = search_my_envp(execl, env_name);
	if (!env_value)
		return(NULL);
	free(env_name);
	return (env_value);
}

int	h_env_var(int *i, char **chunk, t_execlist *execl) //int *a, int *b, 
{
	char	*spec;
	int		a;
	int		b;

	a = 0;
	b = 0;
	get_positions(&a, &b, i, *chunk);
	spec = ft_strdup(get_spec(&a, &b, *chunk, execl));
	if (spec != NULL)
		*chunk = new_chnk(spec, *chunk, a, b);
	else
	{
		spec = (char *)ft_calloc(1, sizeof(char));
		spec[0] = '\0';
		*chunk = new_chnk(spec, *chunk, a, b);

	}
	if (*chunk == NULL)
	{
		ft_printf("minishell: error parsing ($) expander\n");
		return (0);
	}
	return (1);
}

int	spec_char_chunk(t_execlist *execl, int j)// int *a, int *b)
{
	int	i;
	int	flag;
	
	i = -1;
	flag = 1;
	while (execl->chunk[j]->og[++i] != '\0')
	{
		if (execl->chunk[j]->og[i] == 39)
			flag *= -1;
		if (execl->chunk[j]->og[i] == '$' && flag == 1)
		{
			if (execl->chunk[j]->og[i + 1]
				&& execl->chunk[j]->og[i + 1] != 32)
				h_env_var(&i, &execl->chunk[j]->og, execl);
		}
	}
	return (1);
}

int	spec_char_heredoc(t_execlist *execl, int j) //int *a, int *b)
{
	int	i;
	int	flag;
	int	inf;
	
	inf = -1;
	while (execl->chunk[j]->infiles[++inf] != NULL)
	{
		i = -1;
		flag = 1;
		while (execl->chunk[j]->here_dcs[inf] == 1
			&& execl->chunk[j]->infiles[inf][++i] != '\0')
		{
			if (execl->chunk[j]->infiles[inf][i] == 39)
				flag *= -1;
			if (execl->chunk[j]->infiles[inf][i] == '$' && flag == 1)
			{
				if (execl->chunk[j]->og[i + 1]
					&& execl->chunk[j]->og[i + 1] != 32)
					h_env_var(&i, &execl->chunk[j]->og, execl);
			}
		}
	}
	return (1);
}

int	special_char(t_execlist *execl)
{
	//int		a;
	//int		b;
	int		j;

	j = -1;
	//a = 0;
	//b = 0;
	while (execl->chunk[++j] != NULL)
	{
		if (spec_char_chunk(execl, j) == 0) //&a, &b
			return (0);
		if (execl->chunk[j]->infiles)
		{
			if (spec_char_heredoc(execl, j) == 0) //&a, &b
				return (0);
		}
	}
	return(1);
}
