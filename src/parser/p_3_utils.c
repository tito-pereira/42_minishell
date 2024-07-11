/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_3_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:13:30 by marvin            #+#    #+#             */
/*   Updated: 2024/07/10 03:13:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_positions(int *a, int *b, int *i, char *chunk)
{
	*a = *i;
	(*i)++;
	if (chunk[*i] == '?')
	{
		*b = (*i);
		return ;
	}
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
		return (NULL);
	if (env_name[0] == '?')
		env_value = ft_itoa(*(execl->exit_stt));
	else
		env_value = search_my_envp(execl, env_name);
	if (!env_value)
		return (NULL);
	free(env_name);
	return (env_value);
}

int	h_env_var(int *i, char **chunk, t_execlist *execl)
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
