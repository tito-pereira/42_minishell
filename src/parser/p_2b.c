/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:44:10 by marvin            #+#    #+#             */
/*   Updated: 2024/05/22 22:44:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
neste file aqui tenho as tais funçoes de update
os nomes das file redirections, que recebem os parametros
funcoes sao chamadas no file 2a quando de facto se confirma
uma presenca de redirection e se recolhe o nome dessa tal redirection
*/

char	**add_char_p(char **old, char *n_str)
{
	char	**new;
	int		i;

	//printf("adding a new string %s to a char **\n", n_str);
	i = 0;
	while (old[i] != NULL)
		i++;
	new = (char **)ft_calloc((i + 2), sizeof(char *));
	i = -1;
	while (old[++i] != NULL)
		new[i] = ft_strdup(old[i]);
	new[i] = n_str; //ou strdup ainda n sei
	new[++i] = NULL;
	free_db_str(old);
	old = NULL;
	return (new);
}

int	*add_int_p(int *old, int flag)
{
	int		*new;
	int		i;

	//printf("adding a new flag %d to an int *\n", flag);
	i = 0;
	while (old[i] != -1)
		i++;
	new = (int *)ft_calloc((i + 2), sizeof(int));
	i = -1;
	while (old[++i] != -1)
		new[i] = old[i];
	new[i] = flag;
	new[++i] = -1;
	free(old);
	old = NULL;
	return (new);
}

// chunk, in_out, flag, new
void	update_char_p(char ***in_or_out, char *n_str, int *c)
{
	//printf("updating a char ** with '%s' member\n", n_str);
	if (*c == -1)
	{
		//printf("new char * list created\n");
		*in_or_out = (char **)ft_calloc(2, sizeof(char *));
		(*in_or_out)[0] = n_str;
		(*in_or_out)[1] = NULL;
		(*c)++;
	}
	else
	{
		*in_or_out = add_char_p(*in_or_out, n_str);
		(*c)++;
	}
	//for (int i = 0; (*in_or_out)[i] != NULL; i++)
		//printf("chr_str[%d] == %s\n", i, (*in_or_out)[i]);
}

void	update_int_p(int **in_or_out, int flag, int c)
{
	//printf("updating a int * with %d flag\n", flag);
	if (c == 0)
	{
		//printf("new int * list created\n");
		*in_or_out = (int *)ft_calloc(2, sizeof(int));
		(*in_or_out)[0] = flag;
		(*in_or_out)[1] = -1;
	}
	else
		*in_or_out = add_int_p(*in_or_out, flag);
	//for (int i = 0; (*in_or_out)[i] != -1; i++)
		//printf("int_str[%d] == %d\n", i, (*in_or_out)[i]);
}

/*
infile=0, outfile=1, heredoc && append == 1, nao heredoc && trunc == 0
*/

void	updt_rdr_lst(t_chunk *chunk, int in_out, int flag, char *n_str)
{
	//printf("--- updating rdr list, code %d flag %d new member %s ---\n", in_out, flag, n_str);
	if (in_out == 0)// && flag == 0)
	{
		update_char_p(&(chunk->infiles), n_str, &(chunk->nmb_inf));
		update_int_p(&(chunk->here_dcs), flag, chunk->nmb_inf);
	}
	else if (in_out == 1)// && flag == 0)
	{
		update_char_p(&(chunk->outfiles), n_str, &(chunk->nmb_outf));
		update_int_p(&(chunk->app_dcs), flag, chunk->nmb_outf);
	}
}

/*
- bro se a flag for 1 nao escreve nada
- char str tem sempre tamanho 1

a contagem dos elementos c é feita na char p por isso que essa funcao vem primeiro
e tem la o c

here_file nao preciso de guardar entao posso apenas
estar sempre a atualizar
vou atualizando é a flag heredoc.
quando há normal input, mete a flag heredoc a 0.
quando há heredoc, mete a flag a 1.
o ultimo a mexer na flag é o válido e é o valor
que fica

. infiles, keep adding
. heredoc = flag do here_dcs[nmb_inf]

. outfiles, keeps adding
. append, last one changes

ate aqui, acho que é assim
mas e quando eu tiver que realmente abrir os ficheiros, seja
trunc ou append, é so abrir e deixar em branco? ou realmente faco algo?
*/

/*
update redir list gloabl
-> update char pointer (o char ** que contem e vai acumulando os nomes dos files)
	-> infiles
	-> outfiles
-> update int pointer (int * contendo o valor 0/1 da flag, seja para inf ou outf)
	-> infiles
	-> outfiles
(usando as funcoes generica add int p e add char p que dao free e novo malloc)

new, leva malloc no get_name e aqui é atribuido diretamente
é o nome new_string a ser acrescentado à lista
portanto so deve levar free no fim de cada comando
*/