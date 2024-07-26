/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:19 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/26 21:17:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_var(char *var, char ***envp)
{
	size_t	i;
	char	*temp_var;

	i = 0;
	if (!var || !envp)
		return ;
	temp_var = ft_strdup(var);
	while (envp[0][i] && ft_strncmp(envp[0][i], temp_var, ft_strlen(temp_var)))
		i++;
	if (*envp && envp[0][i])
	{
		envp[0][i] = free_str (envp[0][i]);
		envp[0][i] = envp[0][i + 1];
		i++;
		while (envp[0][i])
		{
			envp[0][i] = envp[0][i + 1];
			i++;
		}
		envp[0][i] = NULL;
	}
	temp_var = free_str (temp_var);
}

void	ft_unset(char **cmd, char ***envp)
{
	int	i;

	if (cmd[1] && cmd[1][0] && cmd[1][0] == '-')
	{
    	ft_printf("minishell: unset: options aren't supported\n");
		return ;
	}
	i = 0;
	while (cmd[++i])
		remove_var (cmd[i], envp);
}
