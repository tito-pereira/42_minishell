/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 16:20:00 by marvin           ###   ########.fr       */
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

	flag = 1;
	if (flag == 1)
		flag = pipe_chunks(execl, input, exit_stt, env);
	if (flag == 1)
		flag = redir_checker(*execl);
	if (flag == 1)
		flag = special_char(*execl);
	if (flag == 1)
		flag = scope_redirs(*execl);
	if (flag == 1)
		flag = arg_separator(*execl);
	if (flag == 1)
		flag = arg_id(*execl);
	return (flag);
}

int	parser_success(t_execlist *execl, char *input, int *exit_stt, char **env)
{
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
			return (0);
		}
	}
	return (1);
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