/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:04 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/07 23:08:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_dir(char *dir, char ***envp)
{
	char	*temp;
	char	**var;

	temp = NULL;
	var = ft_calloc (3, sizeof (char *));
	var[0] = ft_strdup ("export");
	temp = getcwd (temp, BUFFER_SIZE);
	if (chdir (dir))
	{
		ft_printf("minishell >> : cd : not a directory");
		temp = free_str(temp);
		var = free_db_str(var);
		return (1);
	}
	else
	{
		//printf("Directory changed\n\n\n");
		var[1] = ft_strjoin ("OLDPWD=", temp);
		ft_export (var, envp);
		temp = free_str(temp);
		var[1] = free_str(var[1]);
		temp = getcwd (temp, BUFFER_SIZE);
		var[1] = ft_strjoin ("PWD=", temp);
		ft_export (var, envp);
	}
	temp = free_str(temp);
	var = free_db_str(var);
	return (0);
}

static char	*get_home(char **envp)
{
	char	*home;

	while (envp && ft_strncmp (*envp, "HOME=", 5))
		envp++;
	/*if (!ft_strncmp (*envp, "HOME=", 5)) //
	{
		ft_printf("Home not found.\n");
		return (NULL);
	}*/
	home = *envp + 5;
	return (home);
}

int	ft_cd(char **cmd, char ***envp)
{
	int	ret;

	ret = 0;
	if (cmd[1] && !cmd[2])
		ret = set_dir (cmd[1], envp);
	else if (!cmd[1])
	{
	/*
		if (!get_home)
		{
			ft_printf("Home not found.\n");
			return (1);
		}
	*/
		ret = set_dir (get_home (*envp), envp);
	}
	else
	{
		ft_printf("minishell >> : cd: invalid usage\n", 2);
		return (1);
	}
	if (ret == 1)
		return (1);
	//print_db_char(envp[0]);
	return (0);
}

/*
	cd (V)
		exit_code -> cd_error_checker
		cd_error_checker, exit_code = 1 (HOME not set, too many args)
		update_dir, file_err = strerror(errno);
*/