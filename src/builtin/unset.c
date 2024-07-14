/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:19 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/07/14 18:42:55 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	remove_var(char *var, char ***envp)
{
	size_t	i;
	char	*temp_var;

	i = 0;
	//printf("removing var '%s'\n", var);
	if (!var || !envp)
		return ;
	temp_var = ft_strdup(var);
	while (envp[0][i] && ft_strncmp(envp[0][i], temp_var, ft_strlen(temp_var)))
		i++;
	if (*envp && envp[0][i])
	{
		envp[0][i] = free_str (envp[0][i]);
		envp[0][i] = envp[0][i + 1];
		i++;
		while (envp[0][i])
		{
			envp[0][i] = envp[0][i + 1];
			i++;
		}
		envp[0][i] = NULL;
	}
	temp_var = free_str (temp_var);
}

void	ft_unset(char **cmd, char ***envp)
{
	int	i;

	i = 0;
	//printf("lets unset\n");
	while (cmd[++i])
		remove_var (cmd[i], envp);
}

/*
unset <vazio> (nem sequer entra no loop e nao crasha, otimo)

vamos la ver o que se passa aqui
testar com variaveis de = entao

tmb acho que vou ter problemas com o = aqui

faz strjoin da var com =
comeca a percorrer as envs procurando o strcmp 0 (portanto, aqui, qualquer env sem = nao resulta)
guarda esse i
e depois faz as operacoes que eu ainda tenho que testar a ver se funcionam, sao validas, etc etc

vai ao indice i, da free, e depois faz um loop de i = i+1, i++

temp_var = ft_strjoin (var, "=");
*/