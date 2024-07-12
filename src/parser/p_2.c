/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:34 by marvin            #+#    #+#             */
/*   Updated: 2024/07/12 23:23:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// (2) - reads and stores redirections and filenames inside each chunk

void	get_error_msg(t_execlist *execl, int ret)
{
	if (ret == 130)
	{
		(*execl->exit_stt) = 130;
		return ;
	}
	if ((*execl->exit_stt) == 10)
		printf("minishell: unclosed quotes\n");
	if ((*execl->exit_stt) == 20)
		printf("minishell: syntax error near unexpected token `newline'\n");
	if ((*execl->exit_stt) == 30)
		printf("minishell: syntax error near unexpected token `|'\n");
	if ((*execl->exit_stt) == 40)
		printf("minishell: syntax error near unexpected token `<'\n");
	if ((*execl->exit_stt) == 45)
		printf("minishell: syntax error near unexpected token `<<'\n");
	if ((*execl->exit_stt) == 50)
		printf("minishell: syntax error near unexpected token `>'\n");
	if ((*execl->exit_stt) == 55)
		printf("minishell: syntax error near unexpected token `>>'\n");
	(*execl->exit_stt) = 1;
}

int	input_checker(int **i, char **nwe, t_execlist **execl, int c)
{
	int	ret;

	ret = input_redir(**i, *nwe, *execl, c);
	if (ret == -1 || ret == 130)
	{
		get_error_msg(*execl, ret);
		return (0);
	}
	if ((*execl)->chunk[c]->og[**i + 1] == '<')
		(**i)++;
	return (1);
}

int	check_redir(t_execlist *execl, int *i, int c, int flag)
{
	char	*nwe;

	nwe = NULL;
	if (flag == 0 && execl->chunk[c]->og[*i] == '<')
	{
		if (input_checker(&i, &nwe, &execl, c) == 0)
			return (0);
	}
	else if (flag == 0 && execl->chunk[c]->og[*i] == '>')
	{
		if (output_redir(*i, nwe, execl, c) == -1)
		{
			get_error_msg(execl, -1);
			return (0);
		}
		if (execl->chunk[c]->og[*i + 1] == '>')
			(*i)++;
	}
	return (1);
}

void	chunk_init(t_execlist **execl, int c)
{
	(*execl)->chunk[c]->infiles = NULL;
	(*execl)->chunk[c]->nmb_inf = -1;
	(*execl)->chunk[c]->here_dcs = NULL;
	(*execl)->chunk[c]->heredoc = 0;
	(*execl)->chunk[c]->here_file = NULL;
	(*execl)->chunk[c]->delimiter = NULL;
	(*execl)->chunk[c]->outfiles = NULL;
	(*execl)->chunk[c]->nmb_outf = -1;
	(*execl)->chunk[c]->append = 0;
	(*execl)->chunk[c]->app_dcs = NULL;
	(*execl)->chunk[c]->inpipe = 0;
	(*execl)->chunk[c]->path = NULL;
	(*execl)->chunk[c]->cmd_n_args = NULL;
}

int	redir_checker(t_execlist *execl)
{
	int	i;
	int	c;
	int	flag;

	c = -1;
	flag = 0;
	while (execl->chunk[++c] != NULL)
	{
		chunk_init(&execl, c);
		i = -1;
		while (execl->chunk[c]->og[++i] != '\0')
		{
			parser_quote_flags(execl->chunk[c]->og[i], &flag);
			if (check_redir(execl, &i, c, flag) == 0)
				return (0);
		}
		if (flag != 0 && unc_qts_err(&execl) == 0)
			return (0);
		//support_print(execl, c);
	}
	return (1);
}
