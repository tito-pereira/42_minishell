/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:34 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 02:25:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
(2) - reads and stores redirections and filenames inside each token
inicializa cada chunk
*/

void	get_error_msg(t_execlist *execl, int ret)
{
	if (ret == 130)
	{
		// SIGINT error message
		(*execl->exit_stt) = 130;
		return ;
	}
	if ((*execl->exit_stt) == 10)
		printf("minishell: unclosed quotes\n");
	if ((*execl->exit_stt) == 20)
		printf("minishell: syntax error near unexpected token `newline'\n");
	if ((*execl->exit_stt) == 30)
		printf("minishell: syntax error near unexpected token `|'\n");
	if ((*execl->exit_stt) == 40)
		printf("minishell: syntax error near unexpected token `<'\n");
	if ((*execl->exit_stt) == 45)
		printf("minishell: syntax error near unexpected token `<<'\n");
	if ((*execl->exit_stt) == 50)
		printf("minishell: syntax error near unexpected token `>'\n");
	if ((*execl->exit_stt) == 55)
		printf("minishell: syntax error near unexpected token `>>'\n");
	(*execl->exit_stt) = 1;
}

/*
(V) unclosed quotes - 10 (get_name_errors)
(V) empty string (last chunk) - 20 (get_name)
(V) empty string (pipe) - 30 (get_name)
(V) redirs: (get_name_errors)
<  - 40
<< - 45
>  - 50
>> - 55
*/

int	check_redir(t_execlist *execl, int *i, int c, int flag)
{
	char	*nwe;
	int		ret;

	nwe = NULL;
	ret = 0;
	if (flag == 0 && execl->chunk[c]->og[*i] == '<')
	{
		//printf("will enter with flag %d\n", flag);
		ret = input_redir(execl->chunk[c], *i, nwe, execl, c);
		if (ret == -1 || ret == 130)
		{
			//perror("Input redirection parsing error");
			//(*execl->exit_stt) = 1;
			get_error_msg(execl, ret);
			return (0);
		}
		if (execl->chunk[c]->og[*i + 1] == '<')
			(*i)++;
	}
	else if (flag == 0 && execl->chunk[c]->og[*i] == '>')
	{
		//printf("will enter with flag %d\n", flag);
		if (output_redir(execl->chunk[c], *i, nwe, execl, c) == -1)
		{
			//perror("Output redirection parsing error");
			//(*execl->exit_stt) = 1;
			get_error_msg(execl, -1);
			return (0);
		}
		if (execl->chunk[c]->og[*i + 1] == '>')
			(*i)++;
	}
	return (1);
}

/*
problema da morada do i
*/

int	redir_checker(t_execlist *execl)
{
	int	i;
	int	c;
	int	flag;

	//ft_printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n"); //
	printf("Inside parsing (2): redir_checker;\n"); //
	c = -1;
	flag = 0;
	//if (execl == NULL) //
		//ft_printf("execl is NULL dumbass\n"); //
	while (execl->chunk[++c] != NULL)
	{
		ft_printf("chunk [%d];\n", c);
		execl->chunk[c]->infiles = NULL;
		execl->chunk[c]->nmb_inf = -1;
		execl->chunk[c]->here_dcs = NULL;
		execl->chunk[c]->heredoc = 0; //?
		execl->chunk[c]->here_file = NULL; //?
		execl->chunk[c]->delimiter = NULL;
		execl->chunk[c]->outfiles = NULL;
		execl->chunk[c]->nmb_outf = -1;
		execl->chunk[c]->append = 0;
		execl->chunk[c]->app_dcs = NULL;
		execl->chunk[c]->inpipe = 0;
		execl->chunk[c]->path = NULL;
		execl->chunk[c]->cmd_n_args = NULL;
		i = -1;
		while (execl->chunk[c]->og[++i] != '\0')
		{
			//printf("loop %d with flag %d\n", i, flag);
			if (execl->chunk[c]->og[i] == 34 && flag == 0)
			{
				//printf("double quote found\n");
				flag = 34;
			}
			else if (execl->chunk[c]->og[i] == 34 && flag == 34)
			{
				//printf("double quote ended\n");
				flag = 0;
			}
			else if (execl->chunk[c]->og[i] == 39 && flag == 0)
			{
				//printf("single quote found\n");
				flag = 39;
			}
			else if (execl->chunk[c]->og[i] == 39 && flag == 39)
			{
				//printf("single quote ended\n");
				flag = 0;
			}
			if (check_redir(execl, &i, c, flag) == 0) //flag == 0 && 
				return (0);
		}
		if (flag != 0)
		{
			ft_printf("minishell: unclosed quotes\n");
			*(execl->exit_stt) = 1;
			return (0);
		}
		support_print(execl, c);
	}
	return (1);
}

/*
echo >    abc< | echo stuff
-bash: syntax error near unexpected token `|'
(meu) minishell: syntax error near unexpected token `<' ???

cat -e<ex>f1 | cat -e<ex>f2 | cat -e<ex>f3
minishell: syntax error near unexpected token `>' ???

erro de logica aqui

<,>,<<,>>
"  '<,>,<<,>>"<
abc< (assumia erro mas ja ta resolvido)

echo <<
minishell: syntax error near unexpected token `newline'
echo >>  | echo stuff
minishell: syntax error near unexpected token `|'
echo >>  "| echo stuff
minishell: unclosed quotes
echo <<   </<</>/>>
minishell: syntax error near unexpected token `</<</>/>>'

(V) unclosed quotes - 10 (get_name_errors)
(V) empty string (last chunk) - 20 (get_name)
(V) empty string (pipe) - 30 (get_name)
(V) redirs: (get_name_errors)
<  - 40
<< - 45
>  - 50
>> - 55

(?) (p_2 acho eu) file redirections:
",' quotes -> 0 -> desativa procura por >,<
",' quotes -> 1 -> volta a ativar procura por >,<
--- (dentro da get_name) ---
",' quotes -> 0 -> desativa procura por SPACE, '\0', <>
",' quotes -> 1 -> volta a ativar procura por SPACE, '\0', <>
*/

/*
void	getname_chest(char **chest, char *input)
{
	char	*old;

	if (!(*chest))
		*chest = ft_strdup(*input);
	else
	{
		old = *chest;
		*chest = ft_strjoin(*chest, *input);
		free (old);
	}
	old = *chest;
	*chest = ft_strjoin(*chest, "\n");
	free(old);
}

char	*get_name(char *str, int i)
{
	int		a;
	int		b;
	int		flag;
	char	*chest;

	while (str[i] == 9 || str[i] == 32)
		i++;
	if (str[i] == '\0') //all whitespaces
		return (NULL);
	a = i; //primeiro non-whitespace
	flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && flag == 0)
			flag = 34;
		if (str[i] == 34 && flag == 34)
			flag = 0;
		if (str[i] == 39 && flag == 0)
			flag = 39;
		if (str[i] == 39 && flag == 39)
			flag = 0;
		if (flag == 0 && (str[i] == 9 || str[i] == 32
			|| str[i] == '>' || str[i] == '<'))
			break ;
		if (str[i] != 34 && str[i] != 39)
			getname_chest(&chest, &str[i]);
		i++;
	}
	b = i;
	if (a == b) //o primeiro non-whitespace era uma redir symbol
		return (NULL);
	return (chest);
}

se der break com uma flag ativa? EOF c flag ativa poderá
ser erro de unclosed quotes por exemplo
*/

/*
old

char	*get_name(char *str, int i)
{
	int	a;
	int	b;

	//ft_printf("Getting file name:\n"); //
	while (str[i] == 9 || str[i] == 32)
		i++;
	if (str[i] == '\0')
		return (NULL); //empty redir
	a = i;
	//ft_printf("a:%d;\n", a); //
	while (str[i] != 9 && str[i] != 32 && str[i] != '\0'
		&& str[i] != '>' && str[i] != '<' && str[i] != '|')
		i++;
	b = i;
	//ft_printf("b:%d;\n", b); //
	if (a == b)
		return (NULL);
	return (ft_substr(str, a, (b - a)));
}
*/