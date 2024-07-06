/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 02:10:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_parser(t_mshell *init)
{
	int			i;
	t_parser	*parser;

	parser = init->parser;
	while (parser != NULL)
	{
		i = -1;
		if (parser->cmd_exec)
		{
			printf("cmd->");
			while (parser->cmd_exec[++i])
				printf("%s ", parser->cmd_exec[i]);
		}
		else
			printf("cmd-> NULL");
		printf("\n");
		printf("path-> %s\n", parser->path_exec);
		if (parser->redirs)
			printf("redirs-> %s\n", parser->redirs);
		printf("input-> %d\n", parser->input);
		printf("output-> %d\n", parser->output);
		printf("file_nf-> %d\n", parser->file_nf);
		printf("token_err-> %d\n\n", parser->token_err);
		parser = parser->next;
	}
}

/* Prints Lexer tokens */
void	print_lexer(t_mshell *init)
{
	t_lexer		*lexer;

	lexer = init->lexer;
	while (lexer)
	{
		printf("str:%s\n", lexer->str);
		printf("op:%d\n", lexer->operator);
		printf("previous: %p\n", lexer->prev);
		printf("next: %p\n\n", lexer->next);
		lexer = lexer->next;
	}
}

/* Prints Env table */
void	print_env(t_mshell *init)
{
	t_env	*env_table;

	env_table = init->env_table;
	while (env_table)
	{
		printf("%s=", env_table->var);
		if (env_table->content)
			printf("%s\n", env_table->content);
		env_table = env_table->next;
	}
}
