/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_6a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:40:54 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/22 18:10:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rmv_newline(char *old)
{
	char				*new;
	unsigned int		len;

	len = ft_strlen(old);
	//ft_printf("Checking for newline.\nOld path size: %d;\n", len);//
	if (old[len - 1] == '\n')
	{
		//ft_printf("Newline detected, preparing to remove.\n");//
		new = malloc(len * sizeof(char));
		ft_strlcpy(new, old, len);
		//ft_printf("New non-newline path: '%s'\n", new);//
		free(old);
		return(new);
	}
	return(old);
}
// size_t	ft_strlcpy(char *s1, const char *s2, size_t size)
// size ja inclui o '\0'
// strlen[size] == '\0', [size - 1] == '\0'

/*
prototipo da get_next_line
get_next acrescenta um \n ao fim de cada linha?
porque raio o output tem um \n no fim

esta funcao aqui remove o \n no fim de cada get_next_line
return
*/

char	**find_execve(char *name, int option)
{
	char	**env;

	//ft_printf("Creating char **env.\n");//
	env = NULL;
	if (option == 1) //builtin
	{
		env = malloc(5 * sizeof(char *));
		env[0] = ft_strdup("/usr/bin/find");
		env[1] = ft_strdup(".");
		env[2] = ft_strdup("-name");
		env[3] = ft_strdup(name);
		env[4] = NULL;
	}
	else if (option == 2) //terminal
	{
		env = malloc(3 * sizeof(char *));
		env[0] = ft_strdup("/usr/bin/which");
		env[1] = ft_strdup(name);
		env[2] = NULL;
	}
	return (env);
}

char	*get_path(char *name, int option)
{
	char	*path;
	char	**env;
	int		*fd;
	int		pid;

	fd = malloc(2 * sizeof(int));
	//ft_printf("Forking another process to find our PATH.\n");//
	if (pipe(fd) == -1)
		return (NULL);
	env = find_execve(name, option);
	//ft_printf("char **'env' created successfully:\n");//
	/*if (option == 1)
		ft_printf("[0]:%s; [1]:%s; [2]:%s; [3]:%s; [4]:%s;\n", env[0], env[1], env[2], env[3], env[4]);
	else
		ft_printf("[0]:%s; [1]:%s; [2]:%s;\n", env[0], env[1], env[2]);*/
	pid = fork();
	if (pid == 0)
	{
		close (fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		execve(env[0], env, ENV_VAR);
		//ft_printf("execve error ocurred.\n");//
	}
	wait(0);
	//ft_printf("execve finished\n");//
	env = free_db_str(env);
	close(fd[1]);
	path = get_next_line(fd[0]);
	//ft_printf("get_next_line return: '%s'\n", path);//
	close(fd[0]);
	return (path);
}

char	*find_path(char	*arg, int option)
{
	char	*path;

	//ft_printf("Finding our command PATH:\n");//
	path = get_path(arg, option);
	//ft_printf("PATH discovered.\n");//
	if (path == NULL)
		return (NULL);
	path = rmv_newline(path);
	//ft_printf("PATH found: '%s'\n", path);//
	return (path);
}

int	chunk_id(t_chunk *chunk, int opt) //char *prog, 
{
	char	*path;
	char	*old;

	path = NULL;
	if (opt == 1)
	{
		//ft_printf("(yes builtin) Finding path for '%s'\n", prog);//
		//path = find_path(prog, 1); //builtin
		path = NULL;
		chunk->path = NULL;
	}
	else if (opt == 2)
	{
		//ft_printf("(not builtin) Finding path for '%s'\n", chunk->cmd_n_args[0]);//
		path = find_path(chunk->cmd_n_args[0], 2); //terminal
	}
	if (opt == 2 && path == NULL)
		return (0); //error check
	//if (opt == 1)
		//chunk->path = path; //builtin
	else if (opt == 2)
	{
		//ft_printf("Swapping old cmd_n_arg[0] with PATH.\n");//
		old = chunk->cmd_n_args[0]; //terminal
		chunk->cmd_n_args[0] = path;
		free (old);
		//ft_printf("Swap successfull.\n");//
	}
	return (1);
}