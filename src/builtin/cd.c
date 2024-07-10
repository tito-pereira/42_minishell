/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:04 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/10 02:05:36 by marvin           ###   ########.fr       */
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
	temp = getcwd (temp, 4096);
	if (chdir (dir))
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", dir);
		temp = free_str(temp);
		var = free_db_str(var);
		return (1);
	}
	else
	{
		var[1] = ft_strjoin ("OLDPWD=", temp);
		ft_export (var, envp);
		temp = free_str(temp);
		var[1] = free_str(var[1]);
		temp = getcwd (temp, 4096);
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
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp (*envp, "HOME=", 5))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	home = *envp + 5;
	return (home);
}

int	ft_cd(char **cmd, char ***envp)
{
	int		ret;
	char	*home;

	ret = 0;
	if (cmd[1] && !cmd[2])
		ret = set_dir (cmd[1], envp);
	else if (!cmd[1])
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

/*
cd <empty> -> minishell: cd: HOME not set (ze: 1, bash: 1)
cd dir1 <empty> -> minishell: cd: %s: No such file or directory (ze: 0, bash: 1)
cd dir1 morestuff -> minishell: cd: too many arguments (ze: 1, bash: 1)

unset HOME
cd
minishell: cd: HOME not set
echo $?
1, 1

cd /non/exist
minishell: cd: /non/exist: No such file or directory
bash: cd: /non/exist: No such file or directory
echo $?
0, 1

cd /non/exist/path edefew
minishell: cd: too many arguments
echo $?
1, 1

cd BUFFER_SIZE??

X cd
    - cd : not a directory, 1
    - cd: invalid usage, 1

- cd HOME not defined
    cd simples, sem args, vai para a HOME
*/