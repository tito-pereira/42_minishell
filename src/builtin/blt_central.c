/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_central.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:01:23 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/14 15:46:13 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	blt_central(t_execlist *execl, int i, char **exec_str)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(exec_str[0], "echo", 5) == 0)
		ft_echo(execl->chunk[i]->cmd_n_args);
	else if (ft_strncmp(exec_str[0], "env", 4) == 0)
		ret = ft_env(execl->chunk[i]->cmd_n_args, execl->my_envp);
	else if (ft_strncmp(exec_str[0], "export", 7) == 0)
		ret = ft_export(execl->chunk[i]->cmd_n_args, execl->my_envp);
	else if (ft_strncmp(exec_str[0], "pwd", 4) == 0)
		ret = ft_pwd(execl->chunk[i]->cmd_n_args, *(execl->my_envp));
	else if (ft_strncmp(exec_str[0], "unset", 6) == 0)
		ft_unset(execl->chunk[i]->cmd_n_args, execl->my_envp);
	return (ret);
}
