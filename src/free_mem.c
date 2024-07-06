/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 02:08:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Free Parser nodes */
void	free_parser(t_parser *parser)
{
	t_parser	*temp_parser;

	while (parser)
	{
		temp_parser = parser;
		if (parser->cmd_exec)
			ft_free_smatrix(parser->cmd_exec);
		if (parser->path_exec)
			free(parser->path_exec);
		if (parser->redirs)
			free(parser->redirs);
		parser->input = 0;
		parser->output = 0;
		parser = parser->next;
		free(temp_parser);
	}
}

/* Free Env table */
void	free_env(t_env *env)
{
	t_env	*temp_env;

	while (env)
	{
		temp_env = env;
		free(env->var);
		free(env->content);
		env = env->next;
		free(temp_env);
	}
}

/* Free Lexer tokens */
void	free_lexer(t_lexer *lexer)
{
	t_lexer	*temp_lex;

	while (lexer)
	{
		temp_lex = lexer;
		free(lexer->str);
		lexer->operator = 0;
		lexer->i = 0;
		lexer->prev = NULL;
		lexer = lexer->next;
		free(temp_lex);
	}
}

void	delete_lists(t_mshell *init)
{
	if (init->lexer)
		free_lexer(init->lexer);
	if (init->env_table)
		free_env(init->env_table);
	if (init->parser)
		free_parser(init->parser);
	if (init->in)
		free(init->in);
	if (init->pipe_fds)
		ft_free_imatrix(init->pipe_fds);
	if (init->closed_pipes)
		ft_free_imatrix(init->closed_pipes);
	if (init->child_pids)
		free(init->child_pids);
	if (init->eof)
		free(init->eof);
	init->cmd_index = 0;
	init->nbr_pipes = 0;
	close(init->og_stdin);
	close(init->og_stdout);
	free(init);
}
