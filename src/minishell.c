/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 04:26:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signo;

char	*prompt_line(char **envp_copy)
{
	char	*line;
	char	*dir;
	char	*cwd;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (envp_copy[i] && ft_strncmp(envp_copy[i], "HOME", 4) != 0)
		i++;
	if (envp_copy[i])
		len = ft_strlen(envp_copy[i] + 4);
	cwd = getcwd(NULL, 0);
	if (envp_copy[i] && ft_strncmp(cwd, envp_copy[i] + 5, len - 1) == 0)
		dir = ft_strdup(cwd + len - 1);
	else
		dir = ft_strdup(cwd);
	free(cwd);
	line = ft_strdup("\033[1;32mminishell:~");
	line = ft_strupdate(line, dir);
	free(dir);
	line = ft_strupdate(line, "\033[0m$ ");
	return (line);
}

int	minishell(int exit_code, char **envp, char *input, char *line)
{
	t_mshell	*init;
	int			proc_exit_val;

	while (1)
	{
		set_signals();
		set_prompt_and_get_input(envp, &input, &line);
		if (check_whitespace(input) == 1)
			continue ;
		proc_exit_val = process_exit(input, &exit_code);
		if (proc_exit_val == 0)
			break ;
		else if (proc_exit_val == 1)
			continue ;
		if (quotes_checker(input) != 0)
			continue ;
		init = mshell_init(init, input, envp);
		init->envp_copy = &envp;
		free(input);
		if (lexer_main(init, &envp, &exit_code) == 1)
			init->set_var = true;
		parse_and_execute(init, &envp, &exit_code);
	}
	free_and_clear(envp);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	int			exit_code;
	char		**envp_copy;

	exit_code = 0;
	if (argc != 1)
		args_error();
	envp_copy = envp_dup(envp, -1);
	exit_code = minishell(exit_code, envp_copy, NULL, NULL);
	(void)argv;
	if (exit_code < 0)
		exit_code = exit_code + 500;
	return (exit_code);
}