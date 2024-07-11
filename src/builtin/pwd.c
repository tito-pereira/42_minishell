/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:17 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/11 15:25:26 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(char **cmd, char **envp)
{
	size_t	i;

	(void)cmd;
	i = 0;
	while (envp && ft_strncmp (envp[i], "PWD=", 4))
		i++;
	if (envp && envp[i])
		ft_printf ("%s\n", envp[i] + 4);
}
