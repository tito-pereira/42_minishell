/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:24:37 by marvin            #+#    #+#             */
/*   Updated: 2024/06/25 19:24:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*empty_heredoc(int fd)
{
	char	*shovel;
	char	*chest;
	char	*old;

	shovel = get_next_line(fd);
	chest = NULL;
	while (shovel != NULL)
	{
		if (!chest)
			chest = ft_strdup(shovel);
		else
		{
			old = chest;
			chest = ft_strjoin(chest, shovel);
			free(shovel);
			shovel = NULL;
			free(old);
		}
		shovel = get_next_line(fd);
	}
	close(fd);
	return (chest);
}

void	heredoc_chest(char **chest, char **input)
{
	char	*old;

	if (!(*chest))
		*chest = ft_strdup(*input);
	else
	{
		old = *chest;
		*chest = ft_strjoin(*chest, *input);
		free (old);
	}
	old = *chest;
	*chest = ft_strjoin(*chest, "\n");
	free(old);
	free(*input);
}

char	*heredoc_rd(char *lim)
{
	char	*input;
	char	*chest;

	input = NULL;
	chest = NULL;
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
		{
			ft_printf("minishell: warning: here-document delimited by ");
			ft_printf("end-of-file (wanted `%s')\n", lim);
			return (NULL);
		}
		if (ft_strncmp(lim, input, 4096) == 0)
		{
			free(input);
			break ;
		}
		heredoc_chest(&chest, &input);
	}
	return (chest);
}

void	forked_sup(char **input, int *fd, char *lim)
{
	close(fd[0]);
	sig_handlerr(2);
	*input = heredoc_rd(lim);
	if (!(*input))
	{
		close(fd[1]);
		exit(0);
	}
	write(fd[1], *input, ft_strlen(*input));
	free(*input);
	close(fd[1]);
	exit(0);
}

char	*heredoc_read(char *lim)
{
	int		*fd;
	int		pid;
	char	*input;
	char	*ret;

	fd = (int *)ft_calloc(2, sizeof(int));
	sig_handlerr(3);
	pipe(fd);
	pid = fork();
	if (pid == 0)
		forked_sup(&input, fd, lim);
	close(fd[1]);
	wait(NULL);
	if (g_sig == 130)
	{
		close(fd[0]);
		free(fd);
		return (NULL);
	}
	ret = empty_heredoc(fd[0]);
	close(fd[0]);
	free(fd);
	return (ret);
}
