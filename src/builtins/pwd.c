/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:18:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_mshell *init, t_parser *parser)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	write(parser->output, dir, ft_strlen(dir));
	write(parser->output, "\n", 1);
	free(dir);
	delete_lists(init);
	exit(EXIT_SUCCESS);
}
