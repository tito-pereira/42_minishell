/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:45:13 by marvin            #+#    #+#             */
/*   Updated: 2024/06/27 01:45:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_number(char *str, int *sig)
{
	int	i;

	i = 0;
	if (ft_isdigit (str[i]) || str[0] == '+' || str[0] == '-')
	{
		i++;
		if (str[0] == '-')
			*sig *= -1;
	}
	while (str && str[i])
	{
		if (!(ft_isdigit (str[i])))
			return (0);
		i++;
	}
	if ((*sig == 1 && ft_atol(str) > LLONG_MAX)
		|| (*sig == -1 && ft_atol(str) > ((unsigned long long)(LLONG_MAX) + 1)))
		return (0);
	return (1);
}

static int	is_only_zeros(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] != '0')
			return (0);
	}
	return (1);
}

void	exit_errors(t_execlist **execl, char **cmd)
{
	if (cmd[2])
	{
		ft_printf("minishell: exit: %s: too many arguments\n", cmd[2]);
		*((*execl)->exit_stt) = 1;
		return ;
	}
	ft_printf("minishell: exit: %s: Numeric argument required\n", cmd[1]);
	*((*execl)->exit_stt) = 2;
}

void	ft_exit(char **cmd, t_execlist **execl)
{
	unsigned long long	code;
	int					sign;

	sign = 1;
	if (((!cmd[1]) || (!cmd[2] && is_only_zeros(cmd[1]) == 1))
		&& (*execl)->cmd_nmb == 1)
	{
		free_exec(*execl, 2);
		exit(0);
	}
	if (!cmd[2] && is_valid_number(cmd[1], &sign) == 1
		&& (*execl)->cmd_nmb == 1)
	{
		code = ft_atol(cmd[1]);
		code = ((code * sign) % 256 + 256) % 256;
		free_exec(*execl, 2);
		ft_printf("minishell: exited with error code: %d\n", code);
		exit(code);
	}
	exit_errors(execl, cmd);
	/*if (cmd[2])
	{
		ft_printf("minishell: exit: %s: too many arguments\n", cmd[2]);
		*((*execl)->exit_stt) = 1;
		return ;
	}
	ft_printf("minishell: exit: %s: Numeric argument required\n", cmd[1]);
	*((*execl)->exit_stt) = 2;*/
}
