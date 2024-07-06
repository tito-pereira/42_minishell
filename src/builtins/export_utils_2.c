/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:18:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_content(char **export_split, t_env *env_node)
{
	int	j;

	j = 1;
	env_node->content = ft_strdup(export_split[j]);
	if (!export_split[j + 1])
		return ;
	while (export_split[++j])
	{
		env_node->content = ft_strupdate(env_node->content, "=");
		env_node->content = ft_strupdate(env_node->content, export_split[j]);
	}
	return ;
}
