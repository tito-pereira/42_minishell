/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_3a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:11:55 by tibarbos          #+#    #+#             */
/*   Updated: 2024/07/08 16:38:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*chnk_conditions(char *spec, char *first, char *secnd)
{
	char	*new;
	char	*tmp;
	
	new = NULL;
	if (first && secnd)
	{
		tmp = ft_strjoin(first, spec);
		new = ft_strjoin(tmp, secnd);
	}
	else if (!first && secnd)
		new = ft_strjoin(spec, secnd);
	else if (first && !secnd)
		new = ft_strjoin(first, spec);
	else if (!first && !secnd)
		new = ft_strdup(spec);
	return(new);
}

void	check_empty_strs(char **first, char **secnd)
{
	if (*first[0] == '\0')
	{
		free(*first);
		*first = NULL;
	}
	if (*secnd[0] == '\0')
	{
		free(*secnd);
		*secnd = NULL;
	}
}

char	*new_chnk(char *spec, char *old, int a, int b)
{
	char	*first;
	char	*secnd;
	char	*new;

	first = ft_substr(old, 0, a);
	secnd = ft_substr(old, (b + 1), (ft_strlen(old) - b));
	check_empty_strs(&first, &secnd);
	new = chnk_conditions(spec, first, secnd);
	if (first)
		free(first);
	if (secnd)
		free(secnd);
	free(spec);
	if (new == NULL)
		return(NULL);
	free(old);
	return(new);
}
