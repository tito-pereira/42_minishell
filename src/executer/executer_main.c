/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:15:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_exit_code(int status, int *exit_code)
{
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_code = WTERMSIG(status);
	else if (WIFSTOPPED(status))
		*exit_code = WSTOPSIG(status);
	else
		printf("Something strange just happened.\n");
}

void	executer_fork_router(t_mshell *init, char ***env, int *exit_code, int i)
{
	t_parser	*parser_node;

	if (init->nbr_pipes == 0)
		process_single_cmd(init, env, exit_code);
	else if (init->parser->cmd_exec || init->parser->redirs)
	{
		process_pipes(init);
		parser_node = init->parser;
		init->child_pids = (int *)malloc(sizeof(int) * (init->nbr_pipes + 1));
		malloc_error(init->child_pids);
		signal(SIGPIPE, sigpipe_handler);
		while (i++ <= init->nbr_pipes)
		{
			init->child_pids[i - 1] = fork();
			fork_error(init->child_pids[i - 1]);
			if (init->child_pids[i - 1] == 0)
			{
				init->cmd_index = i;
				process_child(init, parser_node, env, exit_code);
			}
			parser_node = parser_node->next;
		}
		process_parent(init, exit_code);
	}
}

void	executer_main(t_mshell *init, char ***envp_copy, int *exit_code)
{
	if (init->stop_exec)
	{
		*exit_code = 2;
		return ;
	}
	signal(SIGINT, sighandler_fork);
	signal(SIGQUIT, sighandler_fork);
	executer_fork_router(init, envp_copy, exit_code, 0);
	dup2(init->og_stdin, STDIN_FILENO);
	dup2(init->og_stdout, STDOUT_FILENO);
}

/*
as macros aqui são os códigos que usamos para saber
que tipo de execucao, multi, single, heredoc, etc

- pre executor signal handling (apenas global change)
- exit code com errno MACROS
- exec_fork_router (main executor) com SIGPIPE handling
*/