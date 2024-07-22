/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:15 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/22 11:00:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_var_pos(char *var, char **envp)
{
	char	*var_temp;
	int		var_len;
	int		var_pos;

	if (ft_strchr (var, '='))
		var_len = ft_strchr (var, '=') - var;
	else
		var_len = ft_strlen(var);
	var_pos = 0;
	var_temp = ft_calloc (var_len + 1, sizeof (char));
	ft_strlcpy (var_temp, var, var_len + 1);
	var_temp[var_len] = '\0';
	while (envp[var_pos] && ft_strncmp (envp[var_pos], var_temp, var_len))
		var_pos++;
	var_temp = free_str (var_temp);
	return (var_pos);
}

static void	update_var(char *var, int var_pos, char ***envp)
{
	char	**envp_temp;

	if (!envp[0][var_pos])
	{
		envp_temp = ft_calloc (var_pos + 2, sizeof (char *));
		envp_temp[var_pos] = ft_strdup (var);
		while (var_pos--)
			envp_temp[var_pos] = ft_strdup (envp[0][var_pos]);
		*envp = free_db_str(*envp);
		*envp = envp_temp;
	}
	else
	{
		if (var_has_eq(var) == 1)
		{
			envp[0][var_pos] = free_str (envp[0][var_pos]);
			envp[0][var_pos] = ft_strdup (var);
		}
	}
}

static int	valid_var(char *var)
{
	int	i;
	int	ret;

	ret = 1;
	if (!var || (var && var[0] == '='))
		ret = 0;
	if (ft_isdigit (var[0]))
		ret = 0;
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			ret = 0;
		i++;
	}
	return (ret);
}

int	ft_export(char **cmd, char ***envp)
{
	int	i;
	int	var_pos;

	i = 1;
	if (!cmd[1])
		print_sorted_env(envp[0]);
	while (cmd[i])
	{
		if (valid_var (cmd[i]) == 1)
		{
			if (check_exist(*envp, cmd[i]) == 1)
				var_pos = get_var_pos (cmd[i], *envp);
			else
				var_pos = new_var_pos(*envp);
			update_var (cmd[i], var_pos, envp);
		}
		else
		{
			ft_printf("minishell: export: %s: is not valid\n", cmd[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
