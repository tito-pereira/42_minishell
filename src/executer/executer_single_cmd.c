/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_single_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:16:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	single_cmd_isdir(char *cmd)
{
	char	*file_err;

	file_err = NULL;
	file_err = strerror(errno);
	printf("minishell: %s: %s\n", cmd, file_err);
	if (errno >= 13)
		return (126);
	else
		return (127);
}

int	single_cmd_notfound(t_mshell *in, int file_fd, DIR *dir)
{
	file_fd = open(in->parser->cmd_exec[0], O_WRONLY);
	dir = opendir(in->parser->cmd_exec[0]);
	if ((dir != NULL) && (in->parser->cmd_exec[0][0]) == '/')
	{
		safe_closedir(dir);
		printf("minishell: %s: Is a directory\n", in->parser->cmd_exec[0]);
		return (126);
	}
	else if ((file_fd == -1 && in->parser->cmd_exec[0] \
		[ft_strlen(in->parser->cmd_exec[0]) - 1] == '/') || \
		(access(in->parser->cmd_exec[0], F_OK) == -1 && \
		check_forwardslash(in->parser->cmd_exec[0]) == 0))
	{
		safe_closedir(dir);
		safe_close(file_fd);
		printf("minishell: %s: %s\n", in->parser->cmd_exec[0], strerror(errno));
		if (errno >= 13)
			return (126);
		else
			return (127);
	}
	safe_closedir(dir);
	safe_close(file_fd);
	printf("%s: command not found\n", in->parser->cmd_exec[0]);
	return (127);
}

/* Fork single command */
void	fork_single_cmd(t_mshell *init, t_parser *parser_node, char ***envp,
			int *exit_code)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR);
	if (pid == 0 && parser_node->cmd_exec != NULL)
	{
		executer_cmd_router(init, parser_node, envp, exit_code);
		safe_close(pid);
	}
	else
	{
		if (waitpid(pid, &status, 0) != -1)
			get_exit_code(status, exit_code);
		else
			ft_error("waitpid() failed", EXIT_FAILURE);
	}
}

/* Process single command */
void	process_single_cmd(t_mshell *ini, char ***envp, int *exit_code)
{
	if (ini->parser->redirs)
		single_redirs_router(ini, ini->parser, exit_code, -1);
	if (ini->parser->token_err || ini->parser->file_nf || ini->parser->var_nf)
		*exit_code = redirs_error(ini, ini->parser, exit_code);
	else if (!ini->parser->path_exec && ini->parser->redirs)
		*exit_code = 1;
	else if (!ft_strcmp(ini->parser->path_exec, "notfound"))
	{
		if (access(ini->parser->cmd_exec[0], X_OK) == -1 && \
				(ini->parser->cmd_exec[0] \
				[ft_strlen(ini->parser->cmd_exec[0]) - 1] == '/' || \
				ini->parser->cmd_exec[0][0] == '/'))
			*exit_code = single_cmd_isdir(ini->parser->cmd_exec[0]);
		else
			*exit_code = single_cmd_notfound(ini, 0, NULL);
	}
	else if (!ft_strncmp(ini->parser->cmd_exec[0], "cd", 2))
		cd(ini, ini->parser, exit_code, envp);
	else if (!ft_strncmp(ini->parser->cmd_exec[0], "unset", 5))
		unset(ini, envp);
	else if (!ft_strncmp(ini->parser->cmd_exec[0], "export", 6))
		export(ini, envp, exit_code);
	else if (ini->parser->cmd_exec != NULL)
		fork_single_cmd(ini, ini->parser, envp, exit_code);
	return ;
}

void	single_redirs_router(t_mshell *init, t_parser *node, int *exit_code,
			int i)
{
	init->redirs = ft_split(node->redirs, '\t');
	while (init->redirs[++i])
	{
		if (!ft_strncmp(init->redirs[i], "<<", 2))
			node->input = process_here_doc(init, \
			settle_eof(init, init->redirs[i + 1]), exit_code, 0);
		else if (!ft_strncmp(init->redirs[i], "<", 1))
			node->input = process_file(init, init->redirs[i + 1], IN_FILE);
		else if (!ft_strncmp(init->redirs[i], ">>", 2))
			node->output = process_file(init, init->redirs[i + 1], OUT_FAPND);
		else if (!ft_strncmp(init->redirs[i], ">", 1))
			node->output = process_file(init, init->redirs[i + 1], OUT_FOWR);
		if (node->output == -1 || node->input == -1)
		{
			node->file_nf = true;
			ft_free_smatrix(init->redirs);
			return ;
		}
	}
	ft_free_smatrix(init->redirs);
}
