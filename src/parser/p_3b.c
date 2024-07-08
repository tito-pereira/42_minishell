/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_4b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:14:26 by tibarbos          #+#    #+#             */
/*   Updated: 2024/06/23 15:28:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		match_var(t_execlist *execl, int i, char *env_name)
{
	int	j;

	j = 0;
	//printf("-> checking if [%d] matches\n", i);
	//printf("env_name:%s;\n", env_name);
	//printf("my_envp:%s;\n", execl->my_envp[0][i]);
	while ((env_name[j] != '\0') && (env_name[j] == execl->my_envp[0][i][j]))
	{
		//printf("env:%c = my_envp:%c;\n", env_name[j], execl->my_envp[0][i][j]);
		j++;
	}
	if (env_name[j] == '\0' && execl->my_envp[0][i][j] == '=')
		return (1);
	return (0);
}

char	*search_my_envp(t_execlist *execl, char *env_name)
{
	int	i;
	
	i = -1;
	//printf("searching my_envp for env variables\n");
	while (execl->my_envp[0][++i] != NULL)
	{
		//printf("----- searching var [%d] -----\n", i);
		if (match_var(execl, i, env_name) == 1)
		{
			//printf("[%d] it's a match.\n", i);
			return (ft_substr(execl->my_envp[0][i], (ft_strlen(env_name) + 1), \
				ft_strlen(execl->my_envp[0][i])));
		}
		//printf("[%d] is not a match.\n", i);
	}
	return (NULL);
}

/*
-> ajustar os valores de strlen aqui
parece ja estar a funcionar direito mas poderao haver é erros de leaks

syntax correta: <name>=<value>\0
se houver <name> = <value>\0, o espaco vai ser interpretado como dois args diferentes
e retornar erro

retorno:
char * que simula o funcionamento da get_env mas para as minhas proprias env_var
*/