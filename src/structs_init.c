/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 02:10:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_table_init(t_env *env_table)
{
	env_table->var = NULL;
	env_table->content = NULL;
	env_table->visibility = 0;
	env_table->next = NULL;
}

void	expander_init(t_expand *expander)
{
	expander->i = 0;
	expander->macro_len = 0;
	expander->s_quote = 1;
	expander->d_quote = 1;
	expander->new_input = NULL;
}

void	lexer_init(t_lexer *lexer)
{
	lexer->str = NULL;
	lexer->operator = 0;
	lexer->i = 0;
	lexer->d_quote_expand = 0;
	lexer->is_node = 0;
	lexer->true_sign = true;
	lexer->next = NULL;
	lexer->prev = NULL;
}

void	parser_init(t_parser *parser)
{
	parser->cmd_exec = NULL;
	parser->path_exec = NULL;
	parser->redirs = NULL;
	parser->file_nf = false;
	parser->token_err = false;
	parser->var_nf = true;
	parser->cmd_type = 0;
	parser->input = 0;
	parser->output = 0;
	parser->next = NULL;
}

t_mshell	*mshell_init(t_mshell *init, char *input, char **envp)
{
	add_history(input);
	init = (t_mshell *)malloc(sizeof(t_mshell));
	init->in = ft_strdup(input);
	init->origin_in = ft_strdup(input);
	init->set_var = false;
	init->nbr_pipes = 0;
	init->tcmd_full = NULL;
	init->tcmd_path = NULL;
	init->tredirs = NULL;
	init->eof = NULL;
	init->redirs = NULL;
	init->pipe_fds = NULL;
	init->closed_pipes = NULL;
	init->child_pids = NULL;
	init->cmd_index = 0;
	init->og_stdin = dup(STDIN_FILENO);
	init->og_stdout = dup(STDOUT_FILENO);
	init->red_input = STDIN_FILENO;
	init->red_output = STDOUT_FILENO;
	init->stop_exec = false;
	init->exp = NULL;
	init->lexer = NULL;
	init->parser = NULL;
	create_env_list(init, envp);
	return (init);
}
