/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:29 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 15:50:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
(1) - valid pipe counter and divide in tokens
inicializa a "global" struct execl
*/

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

	//ft_printf("Inside chunk_create.\n"); //
	og_group = divide_pipes(execl, input);
	i = 0;
	while (og_group[i] != NULL)
		i++;
	/*if (i != execl->cmd_nmb)
	{
		perror("Pipe parsing error");
		*(execl->exit_stt) = 1;
		return(0);
	}*/
	i = -1;
	while (++i < execl->cmd_nmb)
	{
		execl->chunk[i] = (t_chunk *)ft_calloc(1, sizeof(t_chunk));
		execl->chunk[i]->og = og_group[i]; //ft_strdup
		//printf("chunk[%d]->og '%s'\n", i, execl->chunk[i]->og); //
	}
	free (og_group); //se calhar usar free_db
	return(1);
}

int	pipe_chunks(t_execlist **execl, char *input, int *ex_stt, char ***env)
{
	int		c;
	//int		end;

	//ft_printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n"); //
	//ft_printf("Inside parsing (1): pipe_chunks;\n"); //
	//if (*execl == NULL) //
		//ft_printf("execl is NULL dumbass\n"); //
	*execl = (t_execlist *)ft_calloc(1, sizeof(t_execlist));
	//end = 0;
	/*if (!(*execl))
	{
		perror("Memory allocation problem in the parser");
		*ex_stt = 1;
		return(0);
	}*/
	c = pipe_counter(input, *execl);
	if (c == -1)
	{
		//perror("Invalid pipe placement");
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

/*
-> p_1
. invalid pipe placement, da segfault ao retornar erro
	acho que está
. also, nao reconhece o "|" logo no inicio como erro (p_1)
	acho que está

| echo
echo |
echo || echo
echo "stuff ''' | stuff" | echo more_stuff (testar tmb com '')
echo "stuff 'stuff" | echo stuff (testar tmb com '')
echo "stuff | and '|more|' stuff ||||||" (testar tmb com '')

. mudei estas mallocs para callocs, testar
. retirei erros de malloc (da execlist)
e pipe != cmds (chunk create),
n acho que sirvam para nada p nao confundir

error code: 2
perror: (-bash: syntax error near unexpected token '|')
ou deixar estar assim

linha 62 mudei de malloc para
execl->chunk[i] = (t_chunk *)ft_calloc(sizeof(t_chunk));
*/