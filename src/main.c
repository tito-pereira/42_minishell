/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/10 20:43:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig;

void	global_init(t_execlist **execl, int *exit_stt, char ***env)
{
	g_sig = 0;
	*execl = NULL;
	*exit_stt = 0;
	*env = create_envp();
}

int	mini_init(char **input, char ***env)
{
	g_sig = 128;
	sig_handlerr(1);
	if (ft_read(input, env) == 0)
		return (0);
	return (1);
}

void	mini_exit(t_execlist **execl)
{
	if (*execl && (*execl)->cmd_nmb == 1
		&& ft_strncmp((*execl)->chunk[0]->cmd_n_args[0], "cd", 10) == 0)
		(*(*execl)->exit_stt) = ft_cd((*execl)->chunk[0]->cmd_n_args, (*execl)->my_envp);
	if (*execl && (*execl)->cmd_nmb == 1
		&& ft_strncmp((*execl)->chunk[0]->cmd_n_args[0], "exit", 10) == 0)
		ft_exit((*execl)->chunk[0]->cmd_n_args, *execl);
	if (*execl)
		free_exec(*execl, 1);
}

/*
- retirar o cd daqueles valid cmds do pipe intermedio
- o cd so funciona sozinho num pipe ou pode haver mais cmds? (sozinho)
*/

int	parser_success(t_execlist **execl, char ***env)
{
	(*(*execl)->exit_stt) = 0;
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

int	main(void)
{
	char			*input;
	t_execlist		*execl;
	int				exit_stt;
	char			**env;

	global_init(&execl, &exit_stt, &env);
	while (1)
	{
		if (mini_init(&input, &env) == 0)
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

/*
colocar o cd dentro do mini_exit()


envs
sera que preciso de igualar as envs caso o parser falhe?
so preciso de igualar as envs caso elas mudem no executor acho eu, caso
contrario env continua a apontar para o local correto

exit stt, erros non breakable, quando dar reset?
estar disponivel (non zero) para o parsing (p_3, $?)
depois disso, pode voltar a zero para receber novos sinais e
evitar dar falsas error flags no executor
mas nunca ficar a zeros depois do executor senao perco o $?
logo, dar reset a seguir ao p_3 parsing ter sido feito
(acho q n faço nenhum exit_stt check no p4, p5 e p6)
*/

/*
int	main(void)
{
	char			*input;
	t_execlist		*execl;
	int				exit_stt;
	char			**env;

	exit_stt = 0;
	g_sig = 0;
	execl = NULL;
	env = create_envp();
	while (1)
	{
		g_sig = 128;
		sig_handlerr(1);
		if (ft_read(&input, &env) == 0)
			continue ;
		if (parse_central(&execl, input, &exit_stt, &env) == 1)
		{
			(*execl->exit_stt) = 0;
			exec_main(execl);
			if (execl->exit_stt && (*execl->exit_stt) == 0)
				env = *(execl->my_envp);
			else if ((*execl->exit_stt) && (*execl->exit_stt) != 0)
			{
				env = *(execl->my_envp);
				if (execl)
					free_exec(execl, 1);
				continue ;
			}
		}
		else
		{
			if (execl)
			{
				env = *(execl->my_envp);
				free_exec(execl, 1);
			}
			continue ;
		}
		if (execl && execl->cmd_nmb == 1
			&& ft_strncmp(execl->chunk[0]->cmd_n_args[0], "exit", 10) == 0)
			ft_exit(execl->chunk[0]->cmd_n_args, execl);
		if (execl)
			free_exec(execl, 1);
	}
}
*/