/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:23:11 by marvin            #+#    #+#             */
/*   Updated: 2024/07/09 18:23:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	null_input(char *input)
{
	int	i;

	i = -1;
	if (input[0] == '\0')
		return (0);
	while (input[++i])
	{
		if (input[i] != ' ' && input[i] != '	')
			return (1);
	}
	return (0);
}

int	ft_read(char **input, char ***env)
{
	*input = NULL;
	while (1)
	{
		*input = readline(PROMPT);
		if (*input == NULL)
		{
			free_db_str(*env);
			ft_printf("exit\n");
			exit(0);
		}
		if (*input != NULL && null_input(*input) == 0)
			free(*input);
		else if (*input != NULL && null_input(*input) == 1)
		{
			add_history(*input);
			return (1);
		}
	}
}

char	**create_envp(void)
{
	char	**my_envp;
	int		i;

	i = 0;
	while (__environ[i] != NULL)
		i++;
	my_envp = (char **)malloc((i + 1) * sizeof(char *));
	i = -1;
	while (__environ[++i] != NULL)
		my_envp[i] = ft_strdup(__environ[i]);
	my_envp[i] = NULL;
	return (my_envp);
}

int	parse_central(t_execlist **execl, char *input, int *exit_stt, char ***env)
{
	int			flag;

	flag = 1;
	if (flag == 1)
		flag = pipe_chunks(execl, input, exit_stt, env);
	//printf("p1 done with %d\n", flag);
	if (flag == 1)
		flag = redir_checker(*execl);
	//printf("p2 done with %d\n", flag);
	if (flag == 1)
		flag = special_char(*execl);
	//printf("p3 done with %d\n", flag);
	if (flag == 1)
		flag = scope_redirs(*execl);
	//printf("p4 done with %d\n", flag);
	if (flag == 1)
		flag = arg_separator(*execl);
	//printf("p5 done with %d\n", flag);
	if (flag == 1)
		flag = arg_id(*execl);
	//printf("p6 done with %d\n", flag);
	return (flag);
}
