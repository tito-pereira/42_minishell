/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:03:23 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 16:03:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_global(int num)
{
	if (num == SIGINT || num == SIGQUIT)
		g_sig = 128 + num;
}

void	sig_hd_repeat(int num)
{
	if (num == SIGINT)
	{
		g_sig = 128 + SIGINT;
		write(1, "\n", 1);
		exit(g_sig);
	}
}

void	sig_repeat(int num)
{
	if (num == SIGINT)
	{
		g_sig = 128 + SIGINT;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
