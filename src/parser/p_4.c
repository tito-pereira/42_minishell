/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:12:29 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/08 15:53:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
(4) - remove redirections from the parsing string to simplify parsing process

e se houver >>>>> ou <<<<<
redir interpreta isso ou da erro?
-> get_name retorna NULL
-> rmv_redirs salta todos os '<' a frente, assume bom senso

cat <example.txt >tmp1|cat -e>tmp2|cat -e>tmp3
*/

void	temp_strings(char *og, char **new, int a, int b)
{
	char	*first;
	char	*secnd;
	
	first = NULL;
	if (a != 0)
		first = ft_substr(og, 0, a);
	secnd = NULL;
	if ((b + 1) != (int)ft_strlen(og))
		secnd = ft_substr(og, b, ((int)ft_strlen(og) - b));
	*new = NULL;
	if (!first && secnd)
		*new = secnd; //(malloc ja feito)
	else if (first && secnd)
	{
		*new = ft_strjoin(first, secnd);
		free(first);
		free(secnd);
	}
	else if (first && !secnd)
		*new = first; //(malloc ja feito)
}

/*
if (b + 1)

total 11, [10]
char 6, [5]

provavelmente o erro ta na substr, ver como é feita
[start]
len = numero de malloc
*/

void	find_redirs(char *og, int *a, int *b, int *i)
{
	int	flag;

	flag = 0;
	(*a) = (*i);
	while ((og[*i] == '<' || og[*i] == '>') && og[*i] != '\0') //double signal + errors
		(*i)++;
	while ((og[*i] == 9 || og[*i] == 32) && og[*i] != '\0') //whitespaces
		(*i)++;
	while (og[*i] != '\0') // non white + EOF
	{
		if (og[*i] == 34 && flag == 0)
		{
			//printf("remove_iter: double quote found\n");
			flag = 34;
		}
		else if (og[*i] == 34 && flag == 34)
		{
			//printf("remove_iter: double quote ended\n");
			flag = 0;
		}
		else if (og[*i] == 39 && flag == 0)
		{
			//printf("remove_iter: single quote found\n");
			flag = 39;
		}
		else if (og[*i] == 39 && flag == 39)
		{
			//printf("remove_iter: single quote ended\n");
			flag = 0;
		}
		if (flag == 0 && (og[*i] == 9 || og[*i] == 32))
			break ;
		(*i)++;
	}
	(*b) = (*i);
	//printf("b = %d, position = '%c'\n", *b, og[*b]);
}

/*
se houver <<hbkh>>njne<unoew>kcme vai tudo atrelado ate EOF ou espacos

(*a) = (*i);
while <>
while WHITESPACES
while (!= '\0')
{
	flags
	if (flag == 0 && WHITESPACE)
		break ;
}
(*b) = (*i);

",' quotes -> 0 -> desativa procura por SPACE / '\0'
",' quotes -> 1 -> volta a ativar procura por SPACE / '\0'
e por >,< ? if flag = 0 e >,<, é sinal de voltar atras
tipo >>        ">>< 'this' cwenc "
*/

void	find_red_pos(t_chunk *chunk, int *i)
{
	int		a;
	int		b;
	char	*new;

	a = 0;
	b = 0;
	new = NULL;
	if (chunk->og[*i] == '<' || chunk->og[*i] == '>')
	{
		find_redirs(chunk->og, &a, &b, i);
		temp_strings(chunk->og, &new, a, b);
		if (new)
		{
			free(chunk->og);
			chunk->og = new;
		}
		(*i) = a;
		if (chunk->og[(*i) + 1]
			&& ((chunk->og[*i] == '<' && chunk->og[(*i) + 1] == '<')
			|| (chunk->og[*i] == '>' && chunk->og[(*i) + 1] == '>')))
			(*i)++;
	}
}

/*
if [i + 1] == >,< só aí é que faço o pointer p frente
*/

int	scope_redirs(t_execlist *execl)
{
	int		c;
	int		i;
	int		flag;

	c = -1;
	i = -1;
	flag = 0;
	//ft_printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n");//
	//ft_printf("Inside parsing (4): scope_redirs;\n");//
	while (execl->chunk[++c] != NULL)
	{
		i = -1;
		while (execl->chunk[c]->og[++i] != '\0')
		{
			if (execl->chunk[c]->og[i] == 34 && flag == 0)
			{
				//printf("remove: double quote found\n");
				flag = 34;
			}
			else if (execl->chunk[c]->og[i] == 34 && flag == 34)
			{
				//printf("remove: double quote ended\n");
				flag = 0;
			}
			else if (execl->chunk[c]->og[i] == 39 && flag == 0)
			{
				//printf("remove: single quote found\n");
				flag = 39;
			}
			else if (execl->chunk[c]->og[i] == 39 && flag == 39)
			{
				//printf("remove: single quote ended\n");
				flag = 0;
			}
			if (flag == 0)
				find_red_pos(execl->chunk[c], &i);
		}
		//printf("Final chunk[%d]->og:%s;\n", c, execl->chunk[c]->og);
	}
	return (1);
}

/*
flags 
if flag 0, find_red_pos

(X) (p_4) redir removal:
",' quotes -> 0 -> desativa procura por >,<
",' quotes -> 1 -> volta a ativar procura por >,<
--- (dentro da get_name) ---
",' quotes -> 0 -> desativa procura por SPACE / '\0'
",' quotes -> 1 -> volta a ativar procura por SPACE / '\0'

void	flag_checker(char c, int *flag)
{
	if (c == 34 && *flag == 0)
		*flag = 34;
	else if (c == 34 && *flag == 34)
		*flag = 0;
	else if (c == 39 && *flag == 0)
		*flag = 39;
	else if (c == 39 && *flag == 39)
		*flag = 0;
}
*/

/*
old

void	find_redirs(char *og, int *a, int *b, int *i)
{
	if (og[*i] == '<' || og[*i] == '>')
	{
		(*a) = (*i);
		while ((og[*i] == '<' || og[*i] == '>') && og[*i] != '\0')
			(*i)++;
		while ((og[*i] == 9 || og[*i] == 32) && og[*i] != '\0') //whitespaces + EOF
			(*i)++;
		while (og[*i] != 9 && og[*i] != 32 && og[*i] != '\0') // non white + EOF
			(*i)++;
		(*b) = (*i);
		//printf("b = %d, position = '%c'\n", *b, og[*b]);
	}
}
*/