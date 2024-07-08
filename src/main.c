/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 15:47:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig;

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
	return(my_envp);
}

int	parse_central(t_execlist **execl, char *input, int *exit_stt, char ***env)
{
	int			flag;

	//ft_printf("Inside parsing.\n");//
	// initialize
	flag = 1; //null_input(input);
	if (flag == 1)
		flag = pipe_chunks(execl, input, exit_stt, env);
	//printf("p1. exit stt is %d\n", (*(*execl)->exit_stt));
	printf("p1. exit stt is %d\n", *exit_stt);
	if (flag == 1)
		flag = redir_checker(*execl);
	//printf("p2. exit stt is %d\n", (*(*execl)->exit_stt));
	if (flag == 1)
		flag = special_char(*execl);
	//printf("p3. exit stt is %d\n", (*(*execl)->exit_stt));
	if (flag == 1)
		flag = scope_redirs(*execl);
	//printf("p4. exit stt is %d\n", (*(*execl)->exit_stt));
	if (flag == 1)
		flag = arg_separator(*execl);
	//printf("p5. exit stt is %d\n", (*(*execl)->exit_stt));
	if (flag == 1)
		flag = arg_id(*execl);
	//printf("p6. exit stt is %d\n", (*(*execl)->exit_stt));
	//ft_printf("Finished parsing with flag %d\n", flag);//
	return (flag);
}

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
			//printf("main/pre-exec. exit stt is %d\n", (*execl->exit_stt));
			(*execl->exit_stt) = 0; //
			exec_main(execl); // == 1)
			printf("main/post-exec. exit stt is %d\n", (*execl->exit_stt));
			if (execl->exit_stt && (*execl->exit_stt) == 0)
			{
				printf("main/post-exec. exit stt is %d\n", (*execl->exit_stt));
				env = *(execl->my_envp);
				//(*execl->exit_stt) = 0; //success
			}
			else if ((*execl->exit_stt) && (*execl->exit_stt) != 0)
			{
				env = *(execl->my_envp);
				printf("handle executor errors with ext_stt %d\n", (*execl->exit_stt));
				if (execl)
					free_exec(execl, 1);
				continue ;
			}
		}
		else
		{
			printf("need to handle parser fails\n");
			if (execl)
			{
				env = *(execl->my_envp);
				free_exec(execl, 1);
			}
			continue ;
		}
		printf("returned to main\n");
		if (execl && execl->cmd_nmb == 1
			&& ft_strncmp(execl->chunk[0]->cmd_n_args[0], "exit", 10) == 0)
			ft_exit(execl->chunk[0]->cmd_n_args, execl);
		if (execl)
			free_exec(execl, 1);
	}
}

/*
construir aqui o mecanismo para colocar o exit_stt de executor

a unica vez que uso um free_execl(2) é no exit
todo o resto, mesmo com erros de parse ou exec, leva free(1)
e um reset + new prompt
*/

/*
char	*ft_read(char **env)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline(PROMPT);
		if (input != NULL) //normal + ctrl-\ && ctrl-D ignores
		{
			add_history(input);
			return (input);
		}
		else if (input == NULL) //ctrl-D stoppage, SIGINT (ctrl-\ ignores)
		{
			free_db(env);
			ft_printf("exit\n");
			exit(0);
		}
	}
}

input = ft_read(env);
if (null_input(input) == 0)
{
	free(input);
	continue ;
}
*/