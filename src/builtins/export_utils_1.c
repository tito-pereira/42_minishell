/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 03:18:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*assign_val(t_env **count, int *flag, t_mshell *init)
{
	t_env	*env_node;

	env_node = init->env_table;
	*count = init->env_table;
	*flag = 0;
	return (env_node);
}

void	save_in_stash(t_env *node, t_env *stash)
{
	t_env	*stash_node;

	stash_node = stash;
	if (!stash_node->var)
		stash_node->var = ft_strdup(node->var);
	else
	{
		while (stash_node->next)
			stash_node = stash_node->next;
		stash_node->next = (t_env *)malloc(sizeof(t_env));
		stash_node = stash_node->next;
		stash_node->var = NULL;
		stash_node->content = NULL;
		stash_node->next = NULL;
		stash_node->var = ft_strdup(node->var);
	}
}

int	check_stash(t_env *node, t_env *stash)
{
	t_env	*stash_node;

	stash_node = stash;
	while (stash_node)
	{
		if (ft_strcmp(node->var, stash_node->var) == 0)
			return (0);
		stash_node = stash_node->next;
	}
	return (1);
}

void	sort_list(t_env **prnt, t_env *env_node, \
					t_mshell *init, t_env *stash)
{
	*prnt = env_node;
	while (env_node)
	{
		if (ft_strcmp((*prnt)->var, env_node->var) < 0)
			*prnt = env_node;
		env_node = env_node->next;
	}
	env_node = init->env_table;
	while (env_node)
	{
		while (env_node && stash->var && check_stash(env_node, stash) == 0)
			env_node = env_node->next;
		if (!env_node)
			break ;
		if (ft_strcmp((*prnt)->var, env_node->var) > 0)
			*prnt = env_node;
		env_node = env_node->next;
	}
}

void	check_oldpwd(t_env *prnt, int *flag)
{
	if (ft_strcmp("OLDPWD", prnt->var) == 0)
		*flag = 1;
	if (ft_strcmp("OLDPWD", prnt->var) < 0 && *flag == 0)
	{
		*flag = 1;
		printf("declare -x OLDPWD\n");
	}
}
