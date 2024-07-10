/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:29 by marvin            #+#    #+#             */
/*   Updated: 2024/07/10 02:20:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// (1) - valid pipe counter and divide in chunks

char	**divide_pipes(t_execlist *execl, char *input)
{
	char	**og_group;
	int		i;
	int		beg;
	int		end;

	og_group = malloc((execl->valid_cmds + 1) * sizeof(char *));
	i = -1;
	beg = 0;
	while(++i < execl->valid_cmds)
	{
		end = ft_strlen(input);
		if (execl->pipe_loc[i] != '\0')
			end = execl->pipe_loc[i];
		og_group[i] = ft_substr(input, beg, end - beg);
		if (execl->pipe_loc[i] != '\0')
			beg = execl->pipe_loc[i] + 1;
	}
	og_group[i] = NULL;
	return (og_group);
}

int	chunk_create(char *input, t_execlist *execl)
{
	char	**og_group;
	int		i;

	og_group = divide_pipes(execl, input);
	i = 0;
	while (og_group[i] != NULL)
		i++;
	i = -1;
	while (++i < execl->cmd_nmb)
	{
		execl->chunk[i] = (t_chunk *)ft_calloc(1, sizeof(t_chunk));
		execl->chunk[i]->og = og_group[i];
	}
	free (og_group);
	return(1);
}

int	pipe_chunks(t_execlist **execl, char *input, int *ex_stt, char ***env)
{
	int		c;

	*execl = (t_execlist *)ft_calloc(1, sizeof(t_execlist));
	c = pipe_counter(input, *execl);
	if (c == -1)
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		*ex_stt = 2;
		return(0);
	}
	(*execl)->chunk = (t_chunk **)ft_calloc((c + 2), sizeof(t_chunk *));
	(*execl)->cmd_nmb = c + 1;
	(*execl)->pipe_nmb = c;
	(*execl)->my_envp = env;
	(*execl)->exit_stt = ex_stt;
	(*execl)->env_pipe = NULL;
	(*execl)->chunk[c + 1] = NULL;
	if (chunk_create(input, *execl) == 0)
		return(0);
	return(1);
}
