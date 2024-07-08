/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_6.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:35:51 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/07 22:54:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
(6) - builtin vs shell command identifier + absolute/relative paths handler
*/

int	check_absolute(t_chunk *chunk)
{
	int	i;

	i = 0;
	while (chunk->cmd_n_args[0][i] != '\0')
		i++;
	if ((i >= 1 && chunk->cmd_n_args[0][0] == '/')
		|| (i >= 1 && chunk->cmd_n_args[0][0] == '~')
		|| (i >= 2 && chunk->cmd_n_args[0][0] == '.'
		&& chunk->cmd_n_args[0][1] == '/')
		|| (i >= 3 && chunk->cmd_n_args[0][0] == '.'
		&& chunk->cmd_n_args[0][1] == '.'
		&& chunk->cmd_n_args[0][2] == '/'))
		return (1);
	return (0);
}

int	check_builtin(char *arg)
{
	//ft_printf("Checking if builtin or not:\n");//
	if (ft_strncmp("echo", arg, 256) == 0
		|| ft_strncmp("cd", arg, 256) == 0
		|| ft_strncmp("pwd", arg, 256) == 0
		|| ft_strncmp("export", arg, 256) == 0
		|| ft_strncmp("unset", arg, 256) == 0
		|| ft_strncmp("env", arg, 256) == 0
		|| ft_strncmp("exit", arg, 256) == 0)
	{
		//ft_printf("Builtin confirmed.\n");//
		return (1);
	}
	//ft_printf("Not builtin.\n");//
	return (0);
}

int	arg_id(t_execlist *execl)
{
	int	i;
	int	r;

	i = -1;
	//ft_printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n");//
	//ft_printf("Inside parsing (6): arg_id;\n");//
	while (execl->chunk[++i] != NULL)
	{
		//ft_printf("Getting command id from chunk n°%d:\n", i);//
		if (i == 0)
			execl->chunk[i]->inpipe = 1;
		if (check_absolute(execl->chunk[i]) == 0)
		{
			execl->chunk[i]->blt = check_builtin(execl->chunk[i]->cmd_n_args[0]);
			if (execl->chunk[i]->blt == 1)
				r = chunk_id(execl->chunk[i], 1);
			else if (execl->chunk[i]->blt == 0)
				r = chunk_id(execl->chunk[i], 2);
			if (r == 0)
			{
				ft_printf("%s: invalid command\n", \
				execl->chunk[i]->cmd_n_args[0]);
				*(execl->exit_stt) = 127;
				return(0);
			}
		}
	}
	//ft_printf("Finished the arg id parsing.\n");//
	return(1);
}

/*
minishell:~/sgoinfre/tibarbos/Documents/jose_mini$ noncom 123
noncom: command not found
minishell:~/sgoinfre/tibarbos/Documents/jose_mini$ echo $?
127
minishell:~/sgoinfre/tibarbos/Documents/jose_mini$ /path/to/noncom 123
minishell: /path/to/noncom: No such file or directory
minishell:~/sgoinfre/tibarbos/Documents/jose_mini$ echo $?
127

apenas aceito a directory dentro daqueles parametros, nao verifico se existe ou nao
talvez no execve?


if (BUILTIN) , flag == 1
arg[0] = path/builtft
arg[1] = (char *)cmd_n_args;

else (terminal) , flag == 0
path_n_args || modify cmd_n_args
arg[0] = path/terminal
arg[1] = arg normal

ADD CHUNK_PATH
por default,
execl->chunk[i]->path = NULL;
senao, mudar apenas nos builtins;

vou ter que retirar aquela condicao de erro porque vou aceitar todos os
comandos e so verifico os erros no executor
OU MANTENHO?
*/