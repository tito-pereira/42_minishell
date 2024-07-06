/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:04:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Return the type of the command, Shell native or Builtin */
int	cmd_router(char *cmd)
{
	if (!cmd)
		return (SHELL_CMD);
	else if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || \
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") || \
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") || \
		!ft_strcmp(cmd, "exit"))
		return (BUILTIN_CMD);
	else
		return (SHELL_CMD);
}

/* Find 'PATH=' in envp file and return the paths delimited by ':' */
char	**parse_path(char **envp)
{
	char	*envp_dup;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	envp_dup = ft_strdup(envp[i] + 5);
	if (envp_dup == NULL)
		return (NULL);
	paths = ft_split(envp_dup, ':');
	free(envp_dup);
	if (paths == NULL)
		return (NULL);
	return (paths);
}

/* Get the full path for the command to execute */
char	*get_cmd_path(char **envp_paths, char *cmd, char *tpath, char *newpath)
{
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	if (!ft_strncmp(cmd, "./", 2))
	{
		newpath = ft_strdup(cmd);
		return (newpath);
	}
	if (!envp_paths)
		return (NULL);
	while (envp_paths[++i])
	{
		tpath = ft_strjoin(envp_paths[i], "/");
		newpath = ft_strjoin(tpath, cmd);
		free(tpath);
		if (newpath == NULL)
			return (NULL);
		if (access(newpath, X_OK) == 0)
			return (newpath);
		free(newpath);
	}
	return (NULL);
}

/* Check if command exists and return it's path */
char	*find_cmd(char *cmd, t_mshell *init, char ***envp_copy, char *not_found)
{
	char	*cmd_path;

	if (cmd_router(cmd) == BUILTIN_CMD)
		return (ft_strdup("builtin"));
	init->paths = parse_path(*envp_copy);
	cmd_path = get_cmd_path(init->paths, cmd, NULL, NULL);
	if (cmd_path == NULL)
	{
		parser_main_aux3(init);
		if (!init->var_nf)
		{
			if (!ft_strcmp(cmd, getenv("PWD")))
				not_found = ft_strdup("notfound");
			else if (access(cmd, X_OK) == 0 && \
					(cmd[ft_strlen(cmd) - 1] != '/' && cmd[0] == '/'))
				not_found = ft_strdup(cmd);
			else
				not_found = ft_strdup("notfound");
		}
		else
			not_found = ft_strdup("notfound");
		return (not_found);
	}
	parser_main_aux3(init);
	return (cmd_path);
}
