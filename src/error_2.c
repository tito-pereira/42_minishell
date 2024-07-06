/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 02:08:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Deal with file/directory not found */
int	file_error(char *file_name)
{
	printf("minishell: %s: No such file or directory", file_name);
	exit(EXIT_FAILURE);
}

/* Deal with error definning redirs tokens */
int	redirs_error(t_mshell *init, t_parser *parser_node, int *exit_code)
{
	if (*exit_code == 130)
		return (130);
	if (parser_node->token_err)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (2);
	}
	else if (parser_node->file_nf)
		return (1);
	else
	{
		dup2(init->og_stdin, STDIN_FILENO);
		dup2(init->og_stdout, STDOUT_FILENO);
		return (0);
	}
}

/* Deal with file descriptor failure */
int	fd_error(int fd)
{
	if (fd < 0)
		ft_error("minishell: file error", ERROR);
	return (EXIT_FAILURE);
}

void	safe_close(int fd)
{
	if (fd < 0)
		return ;
	close(fd);
}
