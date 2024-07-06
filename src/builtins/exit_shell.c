/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:18:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_numeric(char **exit_in, int i)
{
	while (exit_in[1][++i])
	{
		if (exit_in[1][i] == '+' && ft_isdigit(exit_in[1][i + 1]))
			i++;
		else if (exit_in[1][i] == '-' && ft_isdigit(exit_in[1][i + 1]))
			i++;
		else if (!ft_isdigit(exit_in[1][i]))
			return (0);
	}
	if (exit_in[2])
		return (1);
	return (0);
}

int	check_exit_args(char **exit_in, int *exit_code, int i, int sign)
{
	if (check_numeric(exit_in, i) == 0)
	{
		while (exit_in[1][++i])
		{
			if (exit_in[1][i] == '+' && ft_isdigit(exit_in[1][i + 1]))
				i++;
			else if (exit_in[1][i] == '-' && ft_isdigit(exit_in[1][i + 1]))
			{
				sign = sign * -1;
				i++;
			}
			else if ((!ft_isdigit(exit_in[1][i]) && exit_in[1][i]) || \
				(!ft_isdigit(exit_in[1][i]) && !exit_in[1][i + 1]) || \
				((sign == 1 && ft_atoll(exit_in[1]) > LLONG_MAX) || \
				(sign == -1 && ft_atoll(exit_in[1]) > \
				(unsigned long long)(LLONG_MAX) + 1)))
			{
				*exit_code = 2;
				return (TRUE_EXIT);
			}
		}
		*exit_code = ((int)(ft_atoll(exit_in[1]) * sign) % 256 + 256) % 256;
		printf("exit\n");
	}
	return (*exit_code);
}

int	exit_arguments(char *input, int exit_code, char **exit_in)
{
	if (input)
	{
		exit_in = ft_split(input, ' ');
		if (exit_in[1] == NULL && !ft_iswhitespace(input[0]))
		{
			printf("exit\n");
			exit_code = exit_code - 500;
		}
		else if (check_exit_args(exit_in, &exit_code, -1, 1) == TRUE_EXIT)
			printf("exit\nminishell: exit: %s: numeric argument required\n", \
				exit_in[1]);
		else if (exit_in[2] != NULL)
		{
			printf("exit\nminishell: exit: too many arguments\n");
			add_history(input);
			if (exit_code == 0)
				exit_code = ARGS_EXIT + 1;
			else
				exit_code = exit_code + ARGS_EXIT ;
		}
		ft_free_smatrix(exit_in);
	}
	else
		printf("exit\n");
	return (exit_code);
}

int	process_exit(char *input, int *exit_code)
{
	if (input == NULL || !ft_strncmp(input, "exit", 4))
	{
		*exit_code = exit_arguments(input, *exit_code, NULL);
		if ((*exit_code != TRUE_EXIT || input == NULL) \
			&& *exit_code < ARGS_EXIT)
		{
			if (input && ft_strlen(input) > 0)
				free(input);
			return (0);
		}
		else if (*exit_code >= ARGS_EXIT)
		{
			if (input && ft_strlen(input) > 0)
				free(input);
			*exit_code = *exit_code - ARGS_EXIT;
		}
		return (1);
	}
	return (2);
}

/*
separa o input em varios argumentos
exit -> simples exit
exit <digit> -> valido?
exit <stuff> <stuff> ... -> too many args
*/