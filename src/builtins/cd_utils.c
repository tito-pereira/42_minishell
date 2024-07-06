/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:19:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_oldpwd(t_mshell *init)
{
	t_env	*env_node;

	env_node = init->env_table;
	while (env_node)
	{
		if (ft_strcmp(env_node->var, "OLDPWD") == 0)
			if (env_node->content)
				return (env_node->content);
		env_node = env_node->next;
	}
	return (NULL);
}
