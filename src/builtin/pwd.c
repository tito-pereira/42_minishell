/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:17 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/22 11:01:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **cmd, char **envp)
{
	size_t	i;

	if (cmd[1])
	{
		ft_printf("minishell: pwd: options are not supported\n", cmd[1]);
		return (127);
	}
	i = 0;
	while (envp && ft_strncmp (envp[i], "PWD=", 4))
		i++;
	if (envp && envp[i])
		ft_printf ("%s\n", envp[i] + 4);
	return (0);
}
