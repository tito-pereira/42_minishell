/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:05:50 by marvin            #+#    #+#             */
/*   Updated: 2024/04/04 19:05:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_mode_one(int mode)
{
	if (mode == 1)
	{
		sigaction(SIGINT, &sa_repeat, NULL);
		sigaction(SIGQUIT, &sa_ign, NULL);
	}
	else if (mode == 2)
	{
		sigaction(SIGINT, &sa_hd_repeat, NULL);
		sigaction(SIGQUIT, &sa_ign, NULL);
	}
	else if (mode == 3)
	{
		sigaction(SIGINT, &sa_global, NULL);
		sigaction(SIGQUIT, &sa_global, NULL);
	}
}

void	check_mode_two(int mode)
{
	if (mode == 4)
	{
		sigaction(SIGINT, &sa_dfl, NULL);
		sigaction(SIGQUIT, &sa_dfl, NULL);
	}
	else if (mode == 5)
	{
		sigaction(SIGINT, &sa_ign, NULL);
		sigaction(SIGQUIT, &sa_ign, NULL);
	}
}

void	sig_handlerr(int mode)
{
	struct	sigaction	sa_repeat;
	struct	sigaction	sa_hd_repeat;
	struct	sigaction	sa_global;
	struct	sigaction	sa_ign;
	struct	sigaction	sa_dfl;

	sa_repeat.sa_handler = &sig_repeat;
	sigemptyset(&sa_repeat.sa_mask);
	sa_repeat.sa_flags = 0;
	sa_hd_repeat.sa_handler = &sig_hd_repeat;
	sigemptyset(&sa_hd_repeat.sa_mask);
	sa_hd_repeat.sa_flags = 0;
	sa_global.sa_handler = &sig_global;
	sigemptyset(&sa_global.sa_mask);
	sa_global.sa_flags = 0;
	sa_ign.sa_handler = SIG_IGN;
	sigemptyset(&sa_ign.sa_mask);
	sa_ign.sa_flags = 0;
	sa_dfl.sa_handler = SIG_DFL;
	sigemptyset(&sa_dfl.sa_mask);
	sa_dfl.sa_flags = 0;
	check_modes_one(mode);
	check_modes_one(mode);
}
