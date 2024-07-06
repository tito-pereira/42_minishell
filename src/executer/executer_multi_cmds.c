/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_multi_cmds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:15:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	multi_cmd_isdir(t_mshell *init, char *cmd)
{
	char	*file_err;

	dup2(init->og_stdin, STDIN_FILENO);
	dup2(init->og_stdout, STDOUT_FILENO);
	file_err = strerror(errno);
	printf("minishell: %s: %s\n", cmd, file_err);
	if (errno >= 13)
		return (126);
	else
		return (127);
}

int	multi_cmd_notfound(t_mshell *init, t_parser *psr_nde, int file_fd, DIR *dir)
{
	dir = opendir(psr_nde->cmd_exec[0]);
	file_fd = open(psr_nde->cmd_exec[0], O_WRONLY);
	dup2(init->og_stdin, STDIN_FILENO);
	dup2(init->og_stdout, STDOUT_FILENO);
	if ((dir != NULL) && (psr_nde->cmd_exec[0][0]) == '/')
	{
		safe_closedir(dir);
		printf("minishell: %s: Is a directory\n", psr_nde->cmd_exec[0]);
		return (126);
	}
	else if ((file_fd == -1 && psr_nde->cmd_exec[0] \
		[ft_strlen(psr_nde->cmd_exec[0]) - 1] == '/') || \
		(access(psr_nde->cmd_exec[0], F_OK) == -1 && \
		check_forwardslash(psr_nde->cmd_exec[0]) == 0))
	{
		safe_closedir_fd(dir, file_fd);
		printf("minishell: %s: %s\n", psr_nde->cmd_exec[0], strerror(errno));
		if (errno >= 13)
			return (126);
		else
			return (127);
	}
	safe_closedir_fd(dir, file_fd);
	printf("%s: command not found\n", psr_nde->cmd_exec[0]);
	return (127);
}

void	process_pipes(t_mshell *init)
{
	int	i;

	i = -1;
	if (init->nbr_pipes == 0)
		return ;
	init->pipe_fds = (int **)malloc(sizeof(int *) * (init->nbr_pipes + 1));
	malloc_error(init->pipe_fds);
	init->closed_pipes = (int **)malloc(sizeof(int *) * (init->nbr_pipes + 1));
	malloc_error(init->closed_pipes);
	init->pipe_fds[init->nbr_pipes] = NULL;
	init->closed_pipes[init->nbr_pipes] = NULL;
	while (++i < init->nbr_pipes)
	{
		init->pipe_fds[i] = (int *)malloc(sizeof(int) * 2);
		malloc_error(init->pipe_fds[i]);
		init->closed_pipes[i] = (int *)malloc(sizeof(int) * 2);
		malloc_error(init->closed_pipes[i]);
		init->closed_pipes[i][0] = 0;
		init->closed_pipes[i][1] = 0;
		if (pipe(init->pipe_fds[i]) == -1)
			ft_error("minishell: failed creating pipe", ERROR);
	}
}

void	process_child(t_mshell *init, t_parser *parser_node, char ***envp,
			int *exit_code)
{
	close_child_pipes(init);
	multi_redirs_router(init, parser_node, exit_code);
	if (parser_node->token_err || parser_node->file_nf)
		exit_err_multi_cmds(init, parser_node, exit_code, envp);
	else if (!parser_node->path_exec && parser_node->redirs)
	{
		free_all_exit_code(init, envp, exit_code);
		return ;
	}
	else if (!ft_strcmp(parser_node->path_exec, "notfound"))
	{
		if (parser_node->var_nf)
			*exit_code = 0;
		else if (access(parser_node->cmd_exec[0], X_OK) == -1 && \
				(parser_node->cmd_exec[0] \
				[ft_strlen(parser_node->cmd_exec[0]) - 1] == '/' || \
				parser_node->cmd_exec[0][0] == '/'))
			*exit_code = multi_cmd_isdir(init, parser_node->cmd_exec[0]);
		else
			*exit_code = multi_cmd_notfound(init, parser_node, 0, NULL);
		free_all(init, envp);
		exit(*exit_code);
	}
	if (parser_node->cmd_exec != NULL)
		executer_cmd_router(init, parser_node, envp, exit_code);
}

void	process_parent(t_mshell *init, int *exit_code)
{
	int	i;
	int	status;

	i = -1;
	close_parent_pipes(init);
	while (++i < (init->nbr_pipes + 1))
	{
		if (waitpid(init->child_pids[i], &status, 0) != -1)
			get_exit_code(status, exit_code);
	}
}
