/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_multi_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:15:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_err_multi_cmds(t_mshell *init, t_parser *parser_node, \
			int *exit_code, char ***envp)
{
	*exit_code = redirs_error(init, parser_node, exit_code);
	free_all(init, envp);
	exit(*exit_code);
}

void	close_pipes(t_mshell *init, int i, int j)
{
	if (init->closed_pipes[i][j])
		exit (SUCCESS);
	if (close(init->pipe_fds[i][j]) == -1)
		ft_error("minishell: error closing parent fd 0", ERROR);
	init->closed_pipes[i][j] = 1;
}

void	close_parent_pipes(t_mshell *init)
{
	int	i;

	i = 0;
	while (init->pipe_fds[i])
	{
		close_pipes(init, i, 0);
		close_pipes(init, i, 1);
		i++;
	}
}

void	close_child_pipes(t_mshell *init)
{
	int	i;

	i = 0;
	if (!init->pipe_fds)
		return ;
	while (init->pipe_fds[i])
	{
		if (i != init->cmd_index - 2)
			close_pipes(init, i, 0);
		if (i != init->cmd_index - 1)
			close_pipes(init, i, 1);
		i++;
	}
}

void	close_redirs_pipes(t_mshell *init, t_parser *node)
{
	if (!init->pipe_fds)
		return ;
	if (init->cmd_index > 1)
		close_pipes(init, init->cmd_index - 2, 0);
	if (node->next)
		close_pipes(init, init->cmd_index - 1, 1);
}
