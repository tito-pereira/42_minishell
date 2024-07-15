/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sup2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:49:47 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/15 12:52:48 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exist(char **envp, char *var)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (var[j] != '\0' && var[j] != '=')
		j++;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], var, j) == 0)
			return (1);
	}
	return (0);
}

int	new_var_pos(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	var_has_eq(char *var)
{
	int	i;

	i = -1;
	while (var[++i] != '\0')
	{
		if (var[i] == '=')
			return (1);
	}
	return (0);
}
