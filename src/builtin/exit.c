/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:13 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/06/27 01:40:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!(ft_isdigit (str[i]) || str[i] == '+'))
			return (0);
		i++;
	}
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

void	ft_exit(int *err, char **cmd, t_execlist *execl)
{
	int	code;
	
	/*if (execl->cmd_nmb != 1)
	{
		printf("multiple commands, no effect\n");
		return ;
	}*/
	if (!cmd[1])
	{
		cmd = free_db_str(cmd);
		*err = 0;
	}
	if (is_only_zeros(cmd[1]))
	{
		cmd = free_db_str(cmd);
		*err = 0;
	}
	if (!cmd[2] && is_valid_number (cmd[1]))
	{
		code = ft_atoi(cmd[1]);
		cmd = free_db_str(cmd);
		ft_printf("Exited with error code: %d", code);
		*err = code;
	}
	cmd = free_db_str(cmd);
	ft_printf("minishell >> : exit : invalid usage");
	//*(execl->to_end) = 1;
}

/*
aqui dentro apenas trato da gestao de argumentos
se é apenas um argumento
se é valido ou nao

o resto trato na main
se for um unico comando exit isolado e nao houver erros, entao
saio com exit(0) de sucesso na main, e este to_end pode ir c o crl
*/