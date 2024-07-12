/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:11 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/07 23:44:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(char **cmd, char ***envp)
{
	size_t	i;

	if (cmd[1] && cmd[1][0] == '-')
	{
		ft_printf("minishell: env: does not accept any options\n");
		return (125);
	}
	if (cmd[1])
	{
		ft_printf("minishell: env: does not accept any arguments\n", cmd[1]);
		return (127);
	}
	else
	{
		i = 0;
		while (envp && *envp && envp[0][i])
		{
			if (ft_strchr (envp[0][i], '='))
				ft_printf ("%s\n", envp[0][i]);
			i++;
		}
	}
	return (0);
}
