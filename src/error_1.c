/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 02:07:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Deal with malloc failure */
int	malloc_error(void *input)
{
	if (input == NULL)
		ft_error("minishell: malloc failed", ERROR);
	return (EXIT_FAILURE);
}

/* Deal with fork failure */
int	fork_error(int pid)
{
	if (pid < 0)
		ft_error("minishell: fork error", ERROR);
	return (EXIT_FAILURE);
}

/* Deal with pipe failure */
int	pipe_error(int pid)
{
	if (pid < 0)
		ft_error("minishell: pipe error", ERROR);
	return (EXIT_FAILURE);
}

/* Deal with bad arguments */
int	args_error(void)
{
	printf("minishell usage: ./minishell\n");
	exit(EXIT_FAILURE);
}

/* Deal with unclosed quotes */
int	quotes_error(void)
{
	printf("minishell: unclosed quotes\n");
	exit(EXIT_FAILURE);
}
