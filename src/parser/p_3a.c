/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_4a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:11:55 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/22 18:09:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*chnk_conditions(char *spec, char *first, char *secnd)
{
	char	*new;
	char	*tmp;
	
	//ft_printf("Choosing new chunk conditions\n");//
	new = NULL;
	/*if (first != NULL)
		ft_printf("first: '%s'\n", first);
	if (secnd != NULL)
		ft_printf("secnd: '%s'\n", secnd);*/
	if (first && secnd)
	{
		//ft_printf("first && secnd\n");//
		tmp = ft_strjoin(first, spec);
		new = ft_strjoin(tmp, secnd);
	}
	else if (!first && secnd)
	{
		//ft_printf("!first && secnd\n");//
		new = ft_strjoin(spec, secnd);
	}
	else if (first && !secnd)
	{
		//ft_printf("first && !secnd\n");//
		new = ft_strjoin(first, spec);
	}
	else if (!first && !secnd)
	{
		//ft_printf("!first && !secnd\n");//
		new = ft_strdup(spec);
	}
	return(new);
}
/*
//tmp = ft_strlcat(first, spec, 1024);
//new = ft_strlcat(tmp, secnd, 1024);

//new = ft_strlcat(spec, secnd, 1024);

//new = ft_strlcat(first, spec, 1024);

// new = spec;
size_t	ft_strlcat(char *dest, const char *src, size_t size)

if (first && secnd)
{
	tmp = ft_strcat(first, spec);
	new = ft_strcat(tmp, secnd);
}
else if (!first && secnd)
	new = ft_strcat(spec, secnd);
else if (first && !secnd)
	new = ft_strcat(first, spec);
else if (!first && !secnd)
	new = spec;
*/

void	check_empty_strs(char **first, char **secnd)
{
	if (*first[0] == '\0')
	{
		//ft_printf("first will be NULL\n");//
		free(*first);
		*first = NULL;
	}
	if (*secnd[0] == '\0')
	{
		//ft_printf("secnd will be NULL\n");//
		free(*secnd);
		*secnd = NULL;
	}
}

char	*new_chnk(char *spec, char *old, int a, int b)
{
	char	*first;
	char	*secnd;
	char	*new;

	//ft_printf("Creating new chunk:\n");//
	first = ft_substr(old, 0, a);
	secnd = ft_substr(old, (b + 1), (ft_strlen(old) - b));
	check_empty_strs(&first, &secnd);
	new = chnk_conditions(spec, first, secnd);
	//ft_printf("just to check, new is '%s'\n", new);//
	if (first)
	{
		//ft_printf("freeing first\n");//
		free(first);
	}
	if (secnd)
	{
		//ft_printf("freeing secnd\n");//
		free(secnd);
	}
	//ft_printf("freeing spec\n");//
	free(spec);
	if (new == NULL)
		return(NULL);
	//ft_printf("old: '%s'\n", old);//
	//ft_printf("freeing old\n");//
	free(old);
	//ft_printf("new: '%s'\n", new);//
	return(new);
}

/*
check if ft_substr retorna NULL ou str vazia
ya o substr vem vazio

eu nao aloco nova memoria no strlcat do new
se der free a first, secnd ou spec dou free ao new

first = ft_substr(0, a, execl.chunk[j].og);
secnd = ft_substr(b, ft_strlen(execl.chunk[j].og), execl.chunk[j].og);
tmp = ft_strcat(first, spec);
new = ft_strcat(tmp, secnd);
if (*a > 0)
	first = (0, a, chunk);
if (*b < ft_strlen(chunk))
	secnd = ft_substr(b, ft_strlen(chunk), chunk);
ft_strcat(first, spec, secnd);
*/