/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:21:30 by marvin            #+#    #+#             */
/*   Updated: 2024/06/24 20:21:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
void	print_db_char(char **str)
{
	int	w;

	w = 0;
	while (str[w] != NULL)
		w++;
	ft_printf("cmd_n_args has %d elements;\n", w);
	for (int i = 0; str[i] != NULL; i++) {
		ft_printf("str[%d]: %s;\n", i, str[i]);
	}
}

void	print_db(char **str)
{
	int i = -1;
	while (str[++i] != NULL)
		ft_printf("%s\n", str[i]);
}

void	support_print(t_execlist *execl, int c)
{
	printf("CHUNK %d REDIR LISTS:\n", c);
	if (execl->chunk[c]->infiles)
	{
		printf("infiles:\n");
		for (int i = 0; execl->chunk[c]->infiles[i] != NULL; i++)
			printf("%s\n", execl->chunk[c]->infiles[i]);
	}
	if (execl->chunk[c]->here_dcs)
	{
		printf("inf_flags:\n");
		for (int i = 0; execl->chunk[c]->here_dcs[i] != -1; i++)
			printf("%d\n", execl->chunk[c]->here_dcs[i]);
	}
	if (execl->chunk[c]->outfiles)
	{
		printf("outfiles:\n");
		for (int i = 0; execl->chunk[c]->outfiles[i] != NULL; i++)
			printf("%s\n", execl->chunk[c]->outfiles[i]);
	}
	if (execl->chunk[c]->app_dcs)
	{
		printf("outf_flags:\n");
		for (int i = 0; execl->chunk[c]->app_dcs[i] != -1; i++)
			printf("%d\n", execl->chunk[c]->app_dcs[i]);
	}
}
*/

/*
void	print_exec(t_execlist *execl)
{
	ft_printf("-.-.-.-.-.-.-.-.-.-\n");
	ft_printf(".	PRINT CHUNKS	.\n");
	ft_printf("-.-.-.-.-.-.-.-.-.-\n");
	ft_printf("General overview:\nNumber of commands: %d;", execl->cmd_nmb);
	ft_printf("\nNumber of pipes: %d;\n", execl->pipe_nmb);
	ft_printf("-.-.-.-.-.-.-.-.-.-.\n-.-.-.-.-.-.-.-.-.-.\n");
	for (int i = 0; execl->chunk[i] != NULL; i++) {
		ft_printf("Chunk nª%d\n", i);
		print_db_char(execl->chunk[i]->cmd_n_args);
		if (execl->chunk[i]->blt == 1)
			ft_printf("PATH: %s;\n", execl->chunk[i]->path);
		else
			ft_printf("PATH: NULL;\n");;
		ft_printf("Heredoc: %d;\nAppend: %d;\n", execl->chunk[i]->heredoc, execl->chunk[i]->append);
		if (execl->chunk[i]->infile)
			ft_printf("infile: %s;\n", execl->chunk[i]->infile);
		else
			ft_printf("infile: NULL\n");
		if (execl->chunk[i]->outfile)
			ft_printf("outfile: %s;\n", execl->chunk[i]->outfile);
		else
			ft_printf("outfile: NULL\n");
		ft_printf("-.-.-.-.-.-.-.-.-.-.\n-.-.-.-.-.-.-.-.-.-.\n");
	}
}*/
///////////////////////////////////////////////
