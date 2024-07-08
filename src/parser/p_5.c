	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:55 by marvin            #+#    #+#             */
/*   Updated: 2024/03/18 17:44:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
(5) - commands && arguments separator by whitespaces
	- handles single && double quotes
	- does not handle redirections (handled previously)

(repeating) skip whitespace -> parse;

. erros para '\0' estao contidos nas funcoes e retornam -1
. retorna 0 sem alterações ou retorna 1 c alterações
. correm seguidos porque só um vai retornar 1 c alterações
erros para unclosed quotes aqui ou noutro sitio

. talvez um erro em que cmp_sep e arg_c nao coincidem ?
*/


int	arg_separator(t_execlist *execl)
{
	int		c;
	int		ret;

	//ft_printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n");//
	printf("Inside parsing (5): arg_separator;\n");//
	c = -1;
	while (execl->chunk[++c] != NULL)
	{
		//ft_printf("Loop nª%d;\n", c);//
		ret = cmd_separator(execl->chunk[c]);
		//ft_printf("cmd_separator return == %d;\n", ret);//
		if (ret == 0)
		{
			ft_printf("minishell: syntax error near unexpected token `|'\n");
			*(execl->exit_stt) = 2;
			return(0);
		}
		else if (ret == -1)
		{
			ft_printf("minishell: unclosed quotes\n");
			*(execl->exit_stt) = 1;
			return(0);
		}
	}
	/*ft_printf("Separated atguments:\n");
	if (execl->chunk[0]->cmd_n_args[0])
		ft_printf("str[%d]: %s;\n", 0, execl->chunk[0]->cmd_n_args[0]);
	if (execl->chunk[0]->cmd_n_args[1])
		ft_printf("str[%d]: %s;\n", 1, execl->chunk[0]->cmd_n_args[1]);
	if (execl->chunk[0]->cmd_n_args[2])
		ft_printf("str[%d]: %s;\n", 2, execl->chunk[0]->cmd_n_args[2]);
	if (execl->chunk[0]->cmd_n_args[3])
		ft_printf("str[%d]: %s;\n", 3, execl->chunk[0]->cmd_n_args[3]);*/
	return(1);
}


/*
verificação de vários erros
- vários comandos (mais do que um built in)
- nao contar com as redirections e saber retira-las
*/

/*
-------------------------------

support function for my command separator
instead of creating a command counter and a command parser
in separate, and iterating over the entire input string twice,
i created a dynamic resizer for the char **cmd_n_args
- new malloc +1 size,
- copies old to new,
- adds new substring to last position,
- free old cmd_n_args

adicionar NULL no fim
algo na numeração da atribuição do NULL nao esta a bater bem
pq todos os elementos estao NULL agora
o new[] imprime bem. o problema é com os frees.
algo esta a tranformar os pointer em NULL ou a trocar a ordem deles

atribuo os pointers diretamente new = pointer, em vez de duplicar
burro do crl
eu igualo os pointers mas dou free ao conteudo local na mesma
*/

void	add_arg(t_chunk *chunk, char **str)
{
	int		c;
	char	**new;

	c = 0;
	//ft_printf("Adding new arg to cmd_n_args;\nThis bad boy: '%s'\n", *str);//
	if (chunk->cmd_n_args == NULL)
	{
		//ft_printf("First arg;\n");//
		chunk->cmd_n_args = malloc(2 * sizeof(char *));
		chunk->cmd_n_args[0] = *str;
		chunk->cmd_n_args[1] = NULL;
	}
	else
	{
		//ft_printf("Already existing args;\n");//
		while (chunk->cmd_n_args[c] != NULL)
			c++;
		//ft_printf("How many cmd_n_args then? %d;\n", c);//
		new = malloc((c + 2) * sizeof(char *));
		c = -1;
		while (chunk->cmd_n_args[++c] != NULL)
			new[c] = ft_strdup(chunk->cmd_n_args[c]);
		new[c] = *str;
		new[c + 1] = NULL;
		//ft_printf("Manual print:\n");//
		/*if (new[c])
			ft_printf("new[%d]: %s;\n", c, new[c]);
		if (new[c + 1] == NULL)
			ft_printf("new[%d]: %s;\n", (c + 1), new[c + 1]);
		if (new[c + 2] == NULL)
			ft_printf("new[%d] exists and is NULL\n", (c + 2));*/
		chunk->cmd_n_args = free_db_str(chunk->cmd_n_args);
		chunk->cmd_n_args = new;
	}
}
