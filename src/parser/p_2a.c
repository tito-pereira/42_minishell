/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:40 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 15:51:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	getname_chest(char **chest, char c)
{
	char	*old;
	char	*input;

	//printf("getname chest\n");
	input = (char *)ft_calloc(2, sizeof(char));
	input[0] = c;
	input[1] = '\0';
	if (!(*chest))
		*chest = ft_strdup(input);
	else
	{
		old = *chest;
		*chest = ft_strjoin(*chest, input);
		free (old);
	}
	free(input);
	//old = *chest;
	//*chest = ft_strjoin(*chest, "\n");
	//free(old);
}

int		get_name_errors(t_execlist *execl, char *str, int i)
{
	if (str[i] == '<')
	{
		if (str[i + 1] && str[i + 1] == '<') //<<
			(*execl->exit_stt) = 45;
		else if (str[i + 1] && str[i + 1] != '<') //<
			(*execl->exit_stt) = 40;
		return (0);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] && str[i + 1] == '>') //>>
			(*execl->exit_stt) = 55;
		else if (str[i + 1] && str[i + 1] != '>') //>
			(*execl->exit_stt) = 50;
		return (0);
	}
	return (1);
}

/*
<  - 40
<< - 45
>  - 50
>> - 55
*/

char	*get_name(char *str, int i, t_execlist *execl, int c)
{
	//int		a;
	//int		b;
	int		flag;
	char	*chest;

	printf("getting redir name with i %d and c '%c'\n", i, str[i]);
	while (str[i] == 9 || str[i] == 32)
	{
		//printf("whitespace\n");
		i++;
	}
	if (str[i] == '\0') //all whitespaces
	{
		if (execl->chunk[c + 1]) //dentro de pipes
			(*execl->exit_stt) = 30;
		else if (!execl->chunk[c + 1]) //last command
			(*execl->exit_stt) = 20;
		return (NULL);
	}
	//a = i; //primeiro non-whitespace, por aqui o check redir?
	if (get_name_errors(execl, str, i) == 0)
		return (NULL);
	flag = 0;
	chest = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && flag == 0)
		{
			//printf("getname: double found\n");
			flag = 34;
		}
		else if (str[i] == 34 && flag == 34)
		{
			//printf("getname: double ended\n");
			flag = 0;
		}
		else if (str[i] == 39 && flag == 0)
		{
			//printf("getname: single found\n");
			flag = 39;
		}
		else if (str[i] == 39 && flag == 39)
		{
			//printf("getname: single ended\n");
			flag = 0;
		}
		if (flag == 0 && (str[i] == 9 || str[i] == 32
			|| str[i] == '>' || str[i] == '<'))
		{
			//printf("getname break: flag is %d and c is '%c'\n", flag, str[i]);
			//if (get_name_errors(execl, str, i) == 0)
				//return (NULL);
			break ;
		}
		if ((str[i] != 34 && str[i] != 39)
			|| (str[i] == 34 && flag == 39)
			|| (str[i] == 39 && flag == 34))
			getname_chest(&chest, str[i]);
		i++;
	}
	if (flag != 0) // unclosed quotes
	{
		(*execl->exit_stt) = 10;
		return (NULL);
	}
	//printf("exit getname with flag %d and i %d\n", flag, i);
	return (chest);
}

/*
echo <<
minishell: syntax error near unexpected token `newline'
echo >>
minishell: syntax error near unexpected token `newline'
echo >>  | echo stuff
minishell: syntax error near unexpected token `|'
echo >>  "| echo stuff
minishell: unclosed quotes
dupla redir
distingue entre as 4 redirs fdsss

(V) unclosed quotes - 10 (get_name_errors)
(V) empty string (last chunk) - 20 (get_name)
(V) empty string (pipe) - 30 (get_name)
(V) redirs: (get_name_errors)
<  - 40
<< - 45
>  - 50
>> - 55
*/

int	check_delim_error(t_execlist *execl, char *delim)
{
	if (ft_strncmp(delim, "<", 5) == 0)
		(*execl->exit_stt) = 40;
	else if (ft_strncmp(delim, "<<", 5) == 0)
		(*execl->exit_stt) = 45;
	else if (ft_strncmp(delim, ">", 5) == 0)
		(*execl->exit_stt) = 50;
	else if (ft_strncmp(delim, ">>", 5) == 0)
		(*execl->exit_stt) = 55;
	else if ((ft_strncmp(delim, "\"", 5) == 0)
		|| (ft_strncmp(delim, "'", 5) == 0))
		(*execl->exit_stt) = 10;
	if (ft_strncmp(delim, "<", 5) == 0 || ft_strncmp(delim, "<<", 5) == 0
		|| ft_strncmp(delim, ">", 5) == 0 || ft_strncmp(delim, ">>", 5) == 0
		|| ft_strncmp(delim, "\"", 5) == 0 || ft_strncmp(delim, "'", 5) == 0)
		return (0);
	return (1);
}

int	input_redir(t_chunk *chunk, int i, char *nwe, t_execlist *execl, int c)
{
	i++;
	//ft_printf("Input redirection checker.\n"); //
	if (chunk->og[i] == '<') // <<
	{
		//ft_printf("heredoc input redirection checking.\n"); //
		chunk->heredoc = 1;
		while ((chunk->og[++i] == 9 || chunk->og[i] == 32)
			&& chunk->og[i] != '\0')
			continue ; // whitespaces + endstring
		if (chunk->og[i] == '\0')
		{
			//perror("Empty heredoc input redirection");
			//(*execl->exit_stt) = 45;
			if (execl->chunk[c + 1]) //dentro de pipes
				(*execl->exit_stt) = 30;
			else if (!execl->chunk[c + 1]) //last command
				(*execl->exit_stt) = 20;
			return (-1);
		}
		if (chunk->delimiter != NULL)
			free(chunk->delimiter);
		chunk->delimiter = get_name(chunk->og, i, execl, c);
		if (chunk->delimiter == NULL
			|| check_delim_error(execl, chunk->delimiter) == 0)
			return (-1);
		nwe = heredoc_read(chunk->delimiter);
		if (nwe == NULL)
		{
			//printf("heredoc_read return was NULL, will give 130\n");
			return (130);
		}
		updt_rdr_lst(chunk, 0, 1, nwe);
	}
	else if (chunk->og[i] != '<') // <
	{
		//if (chunk->infile != NULL) -----------
			//free(chunk->infile); ----------
		//chunk->infile = get_name(chunk->og, *i);
		//ft_printf("simple input redirection checking.\n");
		chunk->heredoc = 0;
		nwe = get_name(chunk->og, i, execl, c);
		if (nwe == NULL)
			return (-1);
		updt_rdr_lst(chunk, 0, 0, nwe);
	}
	//if (chunk->infile == NULL) //----------
		//return (-1); //----------
	//ft_printf("heredoc: '%d'\n", chunk->heredoc);
	//ft_printf("infile: '%s'\n", chunk->infile);
	return (1);
}

int	output_redir(t_chunk *chunk, int i, char *nwe, t_execlist *execl, int c)
{
	i++;
	//ft_printf("Output redirection checker.\n"); //
	if(chunk->og[i] == '>') // >>
	{
		i++;
		//ft_printf("append output redirection.\n");//
		chunk->append = 1;
		//if (chunk->outfile != NULL) //----------
			//free(chunk->outfile); //----------
		//chunk->outfile = get_name(chunk->og, *i);
		nwe = get_name(chunk->og, i, execl, c);
		if (nwe == NULL)
			return (-1);
		updt_rdr_lst(chunk, 1, 1, nwe);
		i--;
	}
	if (chunk->og[i] != '>') // >
	{
		//ft_printf("truncate output redirection.\n");//
		chunk->append = 0;
		//if (chunk->outfile != NULL) -----------
			//free(chunk->outfile); ----------
		//chunk->outfile = get_name(chunk->og, *i);
		nwe = get_name(chunk->og, i, execl, c);
		if (nwe == NULL)
			return (-1);
		updt_rdr_lst(chunk, 1, 0, nwe);
	}
	return(1);
}
