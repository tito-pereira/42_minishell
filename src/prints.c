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

#include "minishell.h"

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
