/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_3b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:14:26 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/08 16:38:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		match_var(t_execlist *execl, int i, char *env_name)
{
	int	j;

	j = 0;
	while ((env_name[j] != '\0') && (env_name[j] == execl->my_envp[0][i][j]))
		j++;
	if (env_name[j] == '\0' && execl->my_envp[0][i][j] == '=')
		return (1);
	return (0);
}

char	*search_my_envp(t_execlist *execl, char *env_name)
{
	int	i;
	
	i = -1;
	while (execl->my_envp[0][++i] != NULL)
	{
		if (match_var(execl, i, env_name) == 1)
		{
			return (ft_substr(execl->my_envp[0][i], (ft_strlen(env_name) + 1), \
				ft_strlen(execl->my_envp[0][i])));
		}
	}
	return (NULL);
}
