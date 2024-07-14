/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:17 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/14 15:48:46 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(char **cmd, char **envp)
{
	size_t	i;

	//(void)cmd;
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
