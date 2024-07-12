/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/13 00:11:31 by marvin           ###   ########.fr       */
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
	if (*execl && (*execl)->cmd_nmb == 1 && (*execl)->chunk[0]->cmd_n_args
		&& ft_strncmp((*execl)->chunk[0]->cmd_n_args[0], "cd", 10) == 0)
		(*(*execl)->exit_stt) = ft_cd((*execl)->chunk[0]->cmd_n_args, \
		(*execl)->my_envp);
	while (*execl && (*execl)->chunk[++i])
	{
		if ((*execl)->chunk[i]->cmd_n_args
			&& ft_strncmp((*execl)->chunk[i]->cmd_n_args[0], "exit", 9) == 0)
			ft_exit((*execl)->chunk[0]->cmd_n_args, execl);
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

/*void	parser_fail(t_execlist **execl)
{
	int	c;

	c = 0;
	//printf("in parser fails\n");
	if (*execl)
		printf("execl exists mf\n");
	if ((*execl)->chunk[c])
		printf("first chunk exists mf\n");
	while (*execl && (*execl)->chunk && (*execl)->chunk[c] 
		&& ((*execl)->chunk[c]->infiles || (*execl)->chunk[c]->outfiles ))
	{
		//printf("will try to open\n");
		open_all_redirs(*execl);
		c++;
	}
	if (*execl)
		free_exec(*execl, 1);
}*/

/*

>f1 >f2 >f3
reprova no p6, vem ter ao parser fail
mas nao devia né
ya acho que posso tirar o parser fail
vai como um solo chunk NULL ao executor
assim este mecanismo permite que esta condicao especial de
empty pipe com redirs nao interfira na execucao de outros pipes

non_exist
non_exist: command not found
echo $?
127

non_exist >f1
non_exist: command not found
echo $?
0 (e o file f1 foi criado)

sera que continua a parser outros chunks ou sai logo desse?
ya, continua nao só a parsar como a executar
portanto, talvez um free + cmd_n_args = NULL
retorna(1) para continuar a parsar os outros
e mandar para o executor na mesma

(leaks / erros
fechar exec_strs que sejam nulos
fechar todos os pipes quando o exec_action for nulo)
fd && exec_str sao alocados em nº de valid_cmds que é decidido no p1, ou seja,
qualquer que seja o pipe, vazio ou nao, vai ter um fd e exec_str alocado

p5, p6, e_main(exec_str), e_loop(exec_action), chk_emp_exec
*/

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
			//parser_fail(&execl);
			if (execl)
				free_exec(execl, 1);
			continue ;
		}
		mini_exit(&execl);
	}
}
