/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:04 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/22 11:00:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_dir_sup(char ***var, char **temp, char ***envp)
{
	(*var)[1] = ft_strjoin ("OLDPWD=", *temp);
	ft_export (*var, envp);
	*temp = free_str(*temp);
	(*var)[1] = free_str((*var)[1]);
	*temp = getcwd (*temp, 4096);
	(*var)[1] = ft_strjoin ("PWD=", *temp);
	ft_export (*var, envp);
}

int	set_dir(char *dir, char ***envp)
{
	char	*temp;
	char	**var;

	temp = NULL;
	var = ft_calloc (3, sizeof (char *));
	var[0] = ft_strdup ("export");
	temp = getcwd (temp, 4096);
	if (chdir (dir))
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", dir);
		temp = free_str(temp);
		var = free_db_str(var);
		return (1);
	}
	else
		set_dir_sup(&var, &temp, envp);
	temp = free_str(temp);
	var = free_db_str(var);
	return (0);
}

static char	*get_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (env[i][0] && env[i][0] == 'H' && env[i][1] && env[i][1] == 'O'
			&& env[i][2] && env[i][2] == 'M' && env[i][3] && env[i][3] == 'E'
			&& env[i][4] && env[i][4] == '=' && env[i][5])
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	home = env[i] + 5;
	return (home);
}

int	ft_cd(char **cmd, char ***envp)
{
	int		ret;
	char	*home;

	ret = 0;
	if (cmd[1] && ft_strncmp(cmd[1], "~", 3) != 0 && !cmd[2])
		ret = set_dir (cmd[1], envp);
	else if ((!cmd[1]) || (ft_strncmp(cmd[1], "~", 3) == 0 && !cmd[2]))
	{
		home = get_home(*envp);
		if (home)
			set_dir(home, envp);
		else
		{
			ft_printf("minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (ret);
}
