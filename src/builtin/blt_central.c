/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_central.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:01:23 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/07 23:07:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	blt_central(t_execlist *execl, int i, char **exec_str)
{
	int	ret;
	
	//printf("BLT central\n");
	ret = 0;
	if (ft_strncmp(exec_str[0], "cd", 3) == 0) //err
		ret = ft_cd(execl->chunk[i]->cmd_n_args, execl->my_envp);
	else if (ft_strncmp(exec_str[0], "echo", 5) == 0)
		ft_echo(execl->chunk[i]->cmd_n_args);
	else if (ft_strncmp(exec_str[0], "env", 4) == 0)
		ret = ft_env(execl->chunk[i]->cmd_n_args, execl->my_envp);
    else if (ft_strncmp(exec_str[0], "export", 7) == 0) //err
		ret = ft_export(execl->chunk[i]->cmd_n_args, execl->my_envp);
    else if (ft_strncmp(exec_str[0], "pwd", 4) == 0)
		ft_pwd(execl->chunk[i]->cmd_n_args, *(execl->my_envp));
    else if (ft_strncmp(exec_str[0], "unset", 6) == 0)
		ft_unset(execl->chunk[i]->cmd_n_args, execl->my_envp);
	//ft_printf("\nleaving blt central env\n");
	//print_db_char(execl->my_envp[0]);
	//printf("ble central will return %d\n", ret);
	return (ret);
}
