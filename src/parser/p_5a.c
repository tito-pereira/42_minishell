/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_5a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:45:01 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 15:25:36 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
arg separator
- entre whitespaces
- entre quotes duplas
- entre quotes singulares

separar em args e comandos

nao posso usar split porque whitespaces nao sao so espacos tmb contam com os
tabs
tenho que fazer substrs manuais para esta coisa
mas nao consigo dividir 9 e 32

- spaces / ! spaces
- "" (onde '' contam como literals)
- '' (onde "" contam como literals)

a && b positioning:
- scroll whitespaces
- find chars

non_white_cnt
non_white_prs
text\0 (Y)
text""text (Y)
text"" (Y)
text"text\0 (X)

""text
text""
conta tudo como um só arg

- non whitespaces -> whitespaces
	unclosed tabs error
- quotes -> quotes + whitespaces

acho que nem sequer preciso do int beg. vai retornar -1 e vai,
vai fechar o programa, é um bocado inutil
*/

int	quote_handler(int option, char c, int *qt, int *qts)
{
	if (option == 1)
	{
		if (c == 39)
			*qt *= -1;
		else if (c == 34)
			*qts *= -1;
	}
	if (option == 2) //&& (*qt == -1 || *qts == -1))
	{
		printf("inside option 2\n");
		if (*qt == -1)
			return (-1);
		if (*qts == -1)
			return (-1);
		//if (*qt == -1 || *qts == -1)
			//return (-1);
	}
	return (1);
}

/*
decline (return 0):
. non whitespace + non endstring from previous parsing;
. single + double quotes;

while:
. non whitespace (9 && 32);
. non endstring;

error_check:
. unclosed quotes

if:
. whitespace + endstring - good return
*/

int	non_white(int *a, int *b, t_chunk *chunk, int *i)
{
	//int	beg;
	int	quote;
	int	quotes;

	//beg = *a;
	quote = 1;
	quotes = 1;
	//if (chunk->og[*i] == 34 || chunk->og[*i] == 39)
		//return(0);
	*a = *i;
	while((chunk->og[*i] != '\0')
		&& ((chunk->og[*i] != 9 && chunk->og[*i] != 32)
		|| ((chunk->og[*i] == 9 || chunk->og[*i] == 32)
		&& quote_handler(2, chunk->og[*i], &quote, &quotes) == -1)))
	{
		//printf("%c\n", chunk->og[*i]);
		quote_handler(1, chunk->og[*i], &quote, &quotes);
		(*i)++;
		//if (chunk->og[*i] == 9 && chunk->og[*i] == 32 && chunk->og[*i] != '\0')
		//if (quote_handler(2, chunk->og[*i], &quote, &quotes) == -1)
			//return (-1);
	}
	//if (quote_handler(2, chunk->og[*i], &quote, &quotes) == -1)
		//return (-1);
	//if(chunk.og[*i] == 34 || chunk.og[*i] == 39 || chunk.og[*i] == 9
		//|| chunk.og[*i] == 32 || chunk.og[*i] == '\0')
	if (chunk->og[*i] == 9 || chunk->og[*i] == 32 || chunk->og[*i] == '\0' || (!quote && !quotes))
		*b = *i - 1;
	printf("exit parser\n");
	return(1);
}

/*
decline (return 0):
. non whitespace + non endstring from previous parsing;
. non single quote;

while:
. non single quote;
. non endstring;

if:
. endstring - return error;
. single quote - good return;
*/

int	single_quote(int *a, int *b, t_chunk *chunk, int *i)
{
	//ft_printf("Parsing single quotes\n");//
	//int beg = *a;
	if (chunk->og[*i] != 39)
		return(0);
	(*i)++;
	*a = *i;
	while(chunk->og[*i] != 39 && chunk->og[*i] != '\0')
		(*i)++;
	if(chunk->og[*i] == '\0')
	{
		//*a = beg;
		perror("Unclosed single quotes error");
		return(-1);
	}
	*b = *i;
	if (*b == *a)
	{
		perror("Empty single quotes error");
		return(-1);
	}
	if (chunk->og[*i] == 39)
		*b = (*i - 1);
	return(1);
}

/*
decline (return 0):
. non whitespace + non endstring from previous parsing;
. non double quote;

while:
. non double quote;
. non endstring;

if:
. endstring - return error;
. double quote - good return;
*/

int	double_quote(int *a, int *b, t_chunk *chunk, int *i)
{
	//ft_printf("Parsing double quotes\n");//
	//int beg = *a;
	if (chunk->og[*i] != 34)
		return(0);
	(*i)++;
	*a = *i;
	while(chunk->og[*i] != 34 && chunk->og[*i] != '\0')
		(*i)++;
	if(chunk->og[*i] == '\0')
	{
		//*a = beg;
		perror("Unclosed double quotes error");
		return(-1);
	}
	*b = *i;
	if (*b == *a)
	{
		perror("Empty double quotes error");
		//ft_printf("minishell: unclosed  double quotes\n");
		return(-1);
	}
	if (chunk->og[*i] == 34)
		*b = (*i - 1);
	return(1);
}

/*
double quotes ficam inseridas no arg

a >> 1 -> \0 ou "

if \0, error
if " && b == a, error
if " && b > a, success

(b nunca fica atras de a
no maximo, b == a)

perror

. o a nao precisa de retornar ao inicio pq eu vou matar o processo
anyway
. nem sei se preciso daquela verificacao de inicio, ja esta assegurada
pelo cmd_separator
PRECISAS SIM, o loop inteiro entra em todas as verificacoes entao é
importante ter essa condicao de saida

""<stuff>\0
<stuff>""\0
<stuff>""<stuff>\0
"uwencewncjw\0

if a == b, error porque empty quotes?

32 - space
34 - double quotes
39 - single quotes
*/

int	cmd_separator(t_chunk *chunk)
{
	int		i;
	int		a;
	int		b;
	char	*sub;

	i = -1;
	a = 0;
	b = 0;
	//ft_printf("Inside cmd_separator;\n");//
	//ft_printf("cmd_n_args: %s;\n", chunk->cmd_n_args);//
	/*int	w = 0;
	while (chunk->cmd_n_args[w] != NULL)
		w++;
	ft_printf("cmd_n_args has %d elements;\n", w);*/
	while (chunk->og[++i]) //non endstring
	{
		//ft_printf("parsing char[%c] on position[%d];\n", chunk->og[i], i);//
		if (chunk->og[i] != 9 && chunk->og[i] != 32) //non whtspcs
		{
			if (non_white(&a, &b, chunk, &i) == -1)
				return (-1); //unclosed quotes ?
			//if (single_quote(&a, &b, chunk, &i) == -1)
				//return (-1); //unclosed quotes
			//if (double_quote(&a, &b, chunk, &i) == -1)
				//return (-1); //unclosed quotes
			//ft_printf("a == [%d] && b == [%d]\n", a, b);//
			sub = ft_substr(chunk->og, a, (b - a + 1));
			add_arg(chunk, &sub);
		}
		if (chunk->og[i] == '\0')
			return (1);
	}
	if (a == b && chunk->cmd_n_args == NULL) //significa que todos retornaram zero, os -1 ja sairam fora
		return (0); //endstring , empty
	return (1);
}

/*
simplesmente tirei/comentei as single e double quotes e os
non-white aceitam tudo quotes no inicio
*/