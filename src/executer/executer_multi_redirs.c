/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_multi_redirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:15:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	multi_check_input(t_mshell *init, t_parser *node, int i)
{
	char	**red_full;

	node->input_t = NO_RED;
	if (node->redirs)
	{
		red_full = ft_split(node->redirs, '\t');
		if (red_full[1] == NULL || check_red_error(red_full[1]) == ERROR)
		{
			node->token_err = true;
			node->input_t = INVALID;
			ft_free_smatrix(red_full);
			return ;
		}
		while (red_full[++i])
		{
			if (!ft_strncmp(red_full[i], "<<", 2))
				node->input_t = IN_HD;
			else if (!ft_strncmp(red_full[i], "<", 1))
				node->input_t = IN_FILE;
		}
		ft_free_smatrix(red_full);
	}
	if (node->input_t != IN_HD && node->input_t != IN_FILE && \
									init->cmd_index != 1)
		node->input_t = IO_PIPE;
}

void	multi_check_output(t_mshell *init, t_parser *node, int i)
{
	char	**red_full;

	(void)init;
	node->output_t = NO_RED;
	if (node->redirs)
	{
		red_full = ft_split(node->redirs, '\t');
		if (red_full[1] == NULL || check_red_error(red_full[1]) == ERROR)
		{
			node->token_err = true;
			node->output_t = INVALID;
			ft_free_smatrix(red_full);
			return ;
		}
		while (red_full[++i])
		{
			if (!ft_strncmp(red_full[i], ">>", 2))
				node->output_t = OUT_FAPND;
			else if (!ft_strncmp(red_full[i], ">", 1))
				node->output_t = OUT_FOWR;
		}
		ft_free_smatrix(red_full);
	}
	if (node->next && node->output_t != OUT_FAPND && node->output_t != OUT_FOWR)
		node->output_t = IO_PIPE;
}

void	multi_redir_input(t_mshell *init, t_parser *node, int *exit_code)
{
	int		i;

	i = -1;
	if (node->input_t == IN_HD || node->input_t == IN_FILE)
	{
		init->redirs = ft_split(node->redirs, '\t');
		while (init->redirs[++i])
		{
			if (!ft_strncmp(init->redirs[i], "<<", 2))
				node->input = process_here_doc(init, \
					settle_eof(init, init->redirs[i + 1]), \
					exit_code, 0);
			else if (!ft_strncmp(init->redirs[i], "<", 1))
				node->input = process_file(init, init->redirs[i + 1], \
					IN_FILE);
		}
		if (node->input == -1)
			node->file_nf = true;
		ft_free_smatrix(init->redirs);
	}
	else if (node->input_t == IO_PIPE)
		node->input = init->pipe_fds[init->cmd_index - 2][0];
	if (node->input_t != NO_RED)
		dup2(node->input, STDIN_FILENO);
}

void	multi_redir_output(t_mshell *init, t_parser *node)
{
	int		i;
	char	**red_full;

	i = -1;
	if (node->output_t == OUT_FAPND || node->output_t == OUT_FOWR)
	{
		red_full = ft_split(node->redirs, '\t');
		while (red_full[++i] && node->output != -1)
		{
			if (!ft_strncmp(red_full[i], ">>", 2))
				node->output = process_file(init, red_full[i + 1], \
					OUT_FAPND);
			else if (!ft_strncmp(red_full[i], ">", 1))
				node->output = process_file(init, red_full[i + 1], \
					OUT_FOWR);
		}
		if (node->output == -1)
			node->file_nf = true;
		ft_free_smatrix(red_full);
	}
	else if (node->output_t == IO_PIPE)
		node->output = init->pipe_fds[init->cmd_index - 1][1];
	if (node->output_t != NO_RED)
		dup2(node->output, STDOUT_FILENO);
}

void	multi_redirs_router(t_mshell *init, t_parser *node, int *exit_code)
{
	multi_check_input(init, node, -1);
	multi_check_output(init, node, -1);
	multi_redir_input(init, node, exit_code);
	multi_redir_output(init, node);
	close_redirs_pipes(init, node);
}
