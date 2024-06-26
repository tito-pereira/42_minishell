/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:34 by marvin            #+#    #+#             */
/*   Updated: 2024/06/29 02:28:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
(2) - reads and stores redirections and filenames inside each token
inicializa cada chunk
*/

int	check_redir(t_execlist *execl, int *i, int c)
{
	char	*nwe;
	int		ret;

	nwe = NULL;
	ret = 0;
	if (execl->chunk[c]->og[*i] == '<')
	{
		ret = input_redir(execl->chunk[c], i, nwe);
		if (ret == -1 || ret == 130)
		{
			perror("Input redirection parsing error");
			*(execl->exit_stt) = 1;
			return (0);
		}
	}
	else if (execl->chunk[c]->og[*i] == '>')
	{
		if (output_redir(execl->chunk[c], i, nwe) == -1)
		{
			perror("Output redirection parsing error");
			*(execl->exit_stt) = 1;
			return (0);
		}
	}
	return (1);
}

int	redir_checker(t_execlist *execl)
{
	int	i;
	int	c;

	//ft_printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n"); //
	//ft_printf("Inside parsing (2): redir_checker;\n"); //
	c = -1;
	//sig_handlerr(2);
	//ft_printf("Is it here?\n"); //
	//if (execl == NULL) //
		//ft_printf("execl is NULL dumbass\n"); //
	while (execl->chunk[++c] != NULL)
	{
		//ft_printf("Loop [%d];\n", c);
		execl->chunk[c]->infiles = NULL;
		execl->chunk[c]->nmb_inf = -1;
		execl->chunk[c]->here_dcs = NULL;
		execl->chunk[c]->heredoc = 0; //?
		execl->chunk[c]->here_file = NULL; //?
		execl->chunk[c]->delimiter = NULL;
		execl->chunk[c]->outfiles = NULL;
		execl->chunk[c]->nmb_outf = -1;
		execl->chunk[c]->append = 0;
		execl->chunk[c]->app_dcs = NULL;
		execl->chunk[c]->inpipe = 0;
		execl->chunk[c]->path = NULL;
		execl->chunk[c]->cmd_n_args = NULL;
		i = -1;
		while (execl->chunk[c]->og[++i] != '\0')
		{
			if (check_redir(execl, &i, c) == 0)
			{
				//printf("parser 2 will return 0 to parser main\n");
				return (0);
			}
		}
		//support_print(execl, c);
	}
	return (1);
}

/*
infiles em chunks que nao sejam 0, nao esta a dar

.X cat <ex>f1|pwd >f2|pwd >f3|cat <ex>f4|pwd >f5 (X BLT)
.X cat <ex>f1|ls >f2|ls >f3|cat <ex>f4|ls >f5 (BLT)
4 nao funciona como previsto
*/