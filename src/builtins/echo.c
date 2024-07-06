/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:19:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_echo_behind(t_parser *parser, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (ft_strcmp(parser->cmd_exec[j], "echo") == 0)
			return (true);
		j++;
	}
	return (false);
}

bool	invalid_echo_option(char *str, int fd)
{
	if (str && str[0] && str[0] == '-')
	{
		if (str && str[1] && str[1] != 'n')
		{
			write(fd, "minishell: invalid echo option", 30);
			return (true);
		}
	}
	return (false);
}

void	print_str(t_mshell *init, t_parser *parser, int fd, int *i)
{
	if (is_echo_behind(parser, *i) == false)
	{
		while (parser && parser->cmd_exec && \
		ft_strcmp(parser->cmd_exec[*i], "echo") != 0)
			(*i)++;
		(*i)++;
	}
	while (parser->cmd_exec[*i])
	{
		if (invalid_echo_option(parser->cmd_exec[*i], fd) == true)
			break ;
		if ((ft_strcmp(parser->cmd_exec[*i], "<<") == 0 || \
		ft_strcmp(parser->cmd_exec[*i], ">>") == 0 || \
		ft_strcmp(parser->cmd_exec[*i], "<") == 0 || \
		ft_strcmp(parser->cmd_exec[*i], ">") == 0 || \
		ft_strcmp(parser->cmd_exec[*i], "|") == 0))
			break ;
		if (ft_strcmp(parser->cmd_exec[*i], "^") != 0 && !init->var_nf)
			write(fd, parser->cmd_exec[*i], ft_strlen(parser->cmd_exec[*i]));
		if (parser->cmd_exec[*i + 1])
			write(fd, " ", 1);
		(*i)++;
	}
}

void	echo(t_mshell *init, t_parser *parser, t_lexer *lex_nd, int i)
{
	int		flag;
	int		j;

	flag = 0;
	j = 1;
	while (parser->cmd_exec && parser->cmd_exec[j] && \
	parser->cmd_exec[j][0] == '-' && parser->cmd_exec[j][1] == 'n')
	{
		i = 2;
		while (parser->cmd_exec[j][i] == 'n')
			i++;
		if (!parser->cmd_exec[j][i])
			flag = 1;
		else
			break ;
		j++;
	}
	i = 0;
	if (parser->cmd_exec[j] && parser->cmd_exec[j][i])
		print_str(init, parser, parser->output, &j);
	if (flag == 0 || !lex_nd)
		write(parser->output, "\n", 1);
	delete_lists(init);
	exit (0);
}
