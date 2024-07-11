/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:04 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/11 02:45:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

/*
char	*get_home(t_mshell *init)
{
	t_env	*node_home;
	t_env	*node_pwd;

	node_home = init->env_table;
	while (node_home && ft_strcmp("HOME", node_home->var) != 0)
		node_home = node_home->next;
	if (!node_home)
		return (NULL);
	node_pwd = init->env_table;
	while (node_pwd && ft_strcmp("PWD", node_pwd->var) != 0)
		node_pwd = node_pwd->next;
	if (ft_strcmp("PWD", node_pwd->var) == 0)
	{
		free(node_pwd->content),
		node_pwd->content = ft_strdup(node_home->content);
	}
	return (node_home->content);
}

void	manage_oldpwd(t_env *node, char *old_dir)
{
	while (ft_strcmp("OLDPWD", node->var) != 0)
	{
		if (!node->next)
		{
			node->next = (t_env *)malloc(sizeof(t_env));
			node->next->var = ft_strdup("OLDPWD");
			node->next->content = NULL;
			node->next->next = NULL;
			node->next->visibility = 0;
		}
		node = node->next;
	}
	if (node->content)
		free(node->content);
	node->content = ft_strdup(old_dir);
	free(old_dir);
}

void	update_dir(t_mshell *init, t_parser *parser, char **new_dir, \
															t_env *node)
{
	char	*file_err;

	if (parser->cmd_exec[1] == NULL || ft_strcmp(parser->cmd_exec[1], "~") == 0)
	{
		*new_dir = ft_strdup(get_home(init));
		chdir(*new_dir);
	}
	else if (ft_strcmp(parser->cmd_exec[1], "-") == 0)
	{
		*new_dir = ft_strdup(get_oldpwd(init));
		chdir(*new_dir);
	}
	else if (chdir(parser->cmd_exec[1]) != 0)
	{
		file_err = strerror(errno);
		printf("minishell: cd: %s: %s\n", parser->cmd_exec[1], file_err);
	}
	*new_dir = getcwd(NULL, 0);
	while (node && ft_strcmp(node->var, "PWD") != 0)
		node = node->next;
	if (!node)
		return ;
	free(node->content);
	node->content = ft_strdup(*new_dir);
}

int	cd_error_checker(t_mshell *init, t_parser *parser, int *exit_code)
{
	if (parser->cmd_exec[1] == NULL && get_home(init) == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		*exit_code = 1;
		return (1);
	}
	else if (parser->cmd_exec[1] && parser->cmd_exec[2])
	{
		printf("minishell: cd: too many arguments\n");
		*exit_code = 1;
		return (1);
	}
	return (0);
}

void	cd(t_mshell *init, t_parser *parser, int *exit_code, char ***envp_copy)
{
	t_env	*node;
	char	*old_dir;
	char	*new_dir;

	if (ft_strcmp(init->in, "cd \"\"") == 0)
		return ;
	if (cd_error_checker(init, parser, exit_code) == 1)
		return ;
	node = init->env_table;
	old_dir = getcwd(NULL, 0);
	update_dir(init, parser, &new_dir, node);
	free(new_dir);
	node = init->env_table;
	manage_oldpwd(node, old_dir);
	*envp_copy = update_envp_copy(init, envp_copy, 0, NULL);
}

*/

/*
HOME not set ta a dar problemas agr

unistd
getcwd() -> update olddir com getcwd()
chdir() -> para actually change dir

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
*/