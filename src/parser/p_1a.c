/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_1a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:52:51 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/05 04:05:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_atr_loop(t_execlist *execl, char *input, int flag, int i)
{
	int	j;

	j = 0;
	while (input[++i] != '\0')
	{
		if (input[i] == 34 && flag == 0)
			flag = 34;
		else if (input[i] == 34 && flag == 34)
			flag = 0;
		else if (input[i] == 39 && flag == 0)
			flag = 39;
		else if (input[i] == 39 && flag == 39)
			flag = 0;
		if (input[i] == '|' && input[i + 1] != '|' && flag == 0)
		{
			execl->pipe_loc[j] = i;
			j++;
		}
	}
	execl->pipe_loc[j] = '\0';
}

int	pipe_cnt_loop(t_execlist *execl, char *input, int flag, int i, int *c)
{
	while (input[++i] != '\0')
	{
		if (input[i] == 34 && flag == 0)
			flag = 34;
		else if (input[i] == 34 && flag == 34)
			flag = 0;
		else if (input[i] == 39 && flag == 0)
			flag = 39;
		else if (input[i] == 39 && flag == 39)
			flag = 0;
		if (input[i] == '|' && flag == 0)
		{
			if (input[i + 1] == '|' || i == 0 || input[i + 1] == '\0') //pipe errors
				return (-1);
			if (input[i + 1] != '|')
			{
				(execl->valid_cmds)++;
				(*c)++;
			}
			//if (input[i + 1] == '\0') //pipe no ultimo indice
				//return (-1);
		}
	}
	return (1);
}

int	pipe_counter(char *input, t_execlist *execl)
{
	int	c;
	int	i;
	//int *flag; //*flag

	c = 0;
	i = -1;
	//flag = malloc(2 * sizeof(int));
	//flag[0] = 1;
	//flag[1] = 1;
	execl->valid_cmds = 1;
	//ft_printf("Inside pipe counter.\n"); //
	if (pipe_cnt_loop(execl, input, 0, i, &c) == -1)
		return (-1);
	//ft_printf("%d valid cmds counted.\n", execl->valid_cmds); //
	execl->pipe_loc = malloc((execl->valid_cmds + 1) * sizeof(int));
	i = -1;
	//flag[0] = 1;
	//flag[1] = 1;
	pipe_atr_loop(execl, input, 0, i);
	//free (flag);
	return (c);
}

/*
pipe_atr_loop
	guarda o [i] da localizaçao da cada pipe valido
	para ser usado para dividir no divide_pipes
pipe_cnt_loop
	aumenta o contador "valid_pipes" com cada pipe valido

talvez mudar as flags do pipe_cnt_loop para evitar erros
-> mudei as flags e parecem estar a dar direito
*/

/*
flags antigas

if (input[i] == 34)
			flag[0] *= -1;
		else if (input[i] == 39)
			flag[1] *= -1;
		else if (input[i] == '|' && flag[0] == 1 && flag[1] == 1)
*/