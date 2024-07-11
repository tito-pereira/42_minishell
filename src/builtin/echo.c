/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:08 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/11 10:32:29 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	the_printer(char **cmd, int i, int j, int *newline)
{
	while (cmd && cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		j = 2;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			break ;
		*newline = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[++i])
			ft_putchar_fd(' ', 1);
	}
}

void	ft_echo(char **cmd)
{
	int	newline;
	int	i;
	int	j;

	newline = 1;
	i = 1;
	j = 0;
	if (cmd && cmd[1] && ft_strlen(cmd[1]) >= 2
		&& cmd[1][0] == '-' && cmd[1][1] != 'n')
	{
		ft_printf("minishell: invalid echo option\n");
		return ;
	}
	the_printer(cmd, i, j, &newline);
	if (newline)
		ft_printf("\n");
}
