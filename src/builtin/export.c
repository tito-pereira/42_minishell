/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:15 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/14 18:12:19 by tibarbos         ###   ########.fr       */
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
	//printf("check_exist\n");
	while (envp[++i] != NULL)
	{
		//printf("loop %d\n", i);
		//printf("'%s', '%s', %d\n", envp[i], var, j);
		if (ft_strncmp(envp[i], var, j) == 0)
			return (1);
	}
	return (0);
}

int	new_var_pos(char **envp)
{
	int	i;

	i = 0;
	//printf("new var pos\n");
	while (envp[i])
		i++;
	return (i);
}

static int	get_var_pos(char *var, char **envp)
{
	char	*var_temp;
	int		var_len;
	int		var_pos;

	//printf("exist var pos\n");
	if (ft_strchr (var, '='))
		var_len = ft_strchr (var, '=') - var;
	else
		var_len = ft_strlen(var);
	//printf("2, var len %d\n", var_len);
	var_pos = 0;
	var_temp = ft_calloc (var_len + 1, sizeof (char)); //+ 2
	//printf("3\n");
	ft_strlcpy (var_temp, var, var_len + 1); // + 2
	//printf("4\n");
	var_temp[var_len] = '\0';
	//printf("5\n");
	//var_temp[var_len + 1] = '\0';
	//printf("'%s', %d\n", var_temp, var_len);
	while (envp[var_pos] && ft_strncmp (envp[var_pos], var_temp, var_len))
		var_pos++;
	//printf("7\n");
	var_temp = free_str (var_temp);
	return (var_pos);
}

/*
tenho que mudar este while loop aqui, perceber porque nao reconhece as minhas
tem a ver com a questao do +1 ou +2
*/

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

/*
nao pode dar update se o novo nao possuir =
*/

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
	//printf("in export\n");
	if (!cmd[1])
	{
		//printf("!cmd[1]\n");
		print_sorted_env(envp[0]);
	}
	while (cmd[i])
	{
		//printf("looping cmd[%d] = '%s'\n", i, cmd[i]);
		if (valid_var (cmd[i]) == 1)
		{
			//printf("is valid\n");
			if (check_exist(*envp, cmd[i]) == 1)
				var_pos = get_var_pos (cmd[i], *envp);
			else
				var_pos = new_var_pos(*envp);
			//printf("pos got: %d\n", var_pos);
			update_var (cmd[i], var_pos, envp);
			//printf("updated\n");
		}
		else //if (!valid_var (cmd[i]))
		{
			ft_printf("minishell: export: %s: is not valid\n", cmd[i]);
			return (1);
		}
		i++;
	}
	//printf("out export\n");
	return (0);
}

/*


apenas testar isto
e depois unset
e o path deve comecar a dar direito

export new size mode
export new size mode
ja ficou a dar (erro da get_var_pos)

ja vejo os erros de export em termos de args e o crl
*/