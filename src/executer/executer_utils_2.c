/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:16:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all_exit_code(t_mshell *init, char ***envp, int *exit_code)
{
	*exit_code = 0;
	delete_lists(init);
	ft_free_smatrix(*envp);
}

void	free_all(t_mshell *init, char ***envp)
{
	delete_lists(init);
	ft_free_smatrix(*envp);
}

void	free_hd_vars(char **redirs, char *input, int pipe_fd)
{
	ft_free_smatrix(redirs);
	if (input)
		free(input);
	close(pipe_fd);
}

void	free_exec_helper(t_mshell *init, t_parser *parser_node, char ***envp,
			char *file_err)
{
	printf("minishell: %s: %s\n", parser_node->cmd_exec[0], file_err);
	free_all(init, envp);
}

void	pre_env_exec(t_mshell *init, t_parser *parser_node, char ***envp)
{
	ft_free_smatrix(*envp);
	if (!parser_node->cmd_exec[1] || parser_node->cmd_exec[1][0] == '-')
		env(init, parser_node);
	printf("env: '%s': No such file or directory\n",
		parser_node->cmd_exec[1]);
	delete_lists(init);
	exit(127);
}
