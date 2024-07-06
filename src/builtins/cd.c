/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:19:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
