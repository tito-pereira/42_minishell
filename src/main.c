/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/11 12:25:23 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig;

void	global_init(int *exit_stt, char ***env, int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_printf("minishell: ./minishell: no arguments required\n");
		exit(1);
	}
	g_sig = 128;
	*exit_stt = 0;
	*env = create_envp();
}

int	mini_init(t_execlist **execl, char **input, char ***env, int *exit_stt)
{
	*execl = NULL;
	sig_handlerr(1);
	if (ft_read(input, env) == 0)
		return (0);
	if (g_sig == 130)
		*exit_stt = 130;
	return (1);
}

void	mini_exit(t_execlist **execl)
{
	int	i;

	i = -1;
	if (g_sig == 130)
		(*(*execl)->exit_stt) = 130;
	if (*execl && (*execl)->cmd_nmb == 1
		&& ft_strncmp((*execl)->chunk[0]->cmd_n_args[0], "cd", 10) == 0)
		(*(*execl)->exit_stt) = ft_cd((*execl)->chunk[0]->cmd_n_args, \
		(*execl)->my_envp);
	while (*execl && (*execl)->chunk[++i])
	{
		if (ft_strncmp((*execl)->chunk[i]->cmd_n_args[0], "exit", 9) == 0)
			ft_exit((*execl)->chunk[0]->cmd_n_args, *execl);
	}
	if (*execl)
		free_exec(*execl, 1);
}

int	parser_success(t_execlist **execl, char ***env)
{
	(*(*execl)->exit_stt) = 0;
	g_sig = 128;
	exec_main(*execl);
	if ((*execl)->exit_stt && (*(*execl)->exit_stt) == 0)
		*env = *((*execl)->my_envp);
	else if ((*(*execl)->exit_stt) && (*(*execl)->exit_stt) != 0)
	{
		*env = *((*execl)->my_envp);
		if (*execl)
			free_exec(*execl, 1);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char			*input;
	t_execlist		*execl;
	int				exit_stt;
	char			**env;

	global_init(&exit_stt, &env, argc, argv);
	while (1)
	{
		if (mini_init(&execl, &input, &env, &exit_stt) == 0)
			continue ;
		if (parse_central(&execl, input, &exit_stt, &env) == 1)
		{
			if (parser_success(&execl, &env) == 0)
				continue ;
		}
		else
		{
			if (execl)
				free_exec(execl, 1);
			continue ;
		}
		mini_exit(&execl);
	}
}
