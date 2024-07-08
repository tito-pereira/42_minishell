/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:47 by marvin            #+#    #+#             */
/*   Updated: 2024/07/05 19:10:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
(3) - environment variable expander with '$'
	- handles single && double quotes
	- does not handle redirections (handled previously)
*/

/*
nao esquecer que "" suporta $ mas '' já não

Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.

$PATH, $HOME, $SHELL, $PWD

.ft_substr()
char	*ft_substr(char const *s, unsigned int start, size_t len)

.ft_strcat()
size_t	ft_strlcat(char *dest, const char *src, size_t size)

char *ret = getenv("env_name")

se calhar, por questoes de evitar erros, colocar a = $ && b = last_char
*/

void	get_positions(int *a, int *b, int *i, char *chunk)
{
	//ft_printf("Getting positions a && b:\n");
	*a = *i;
	(*i)++;
	while (chunk[*i] != 9 && chunk[*i] != 32 && chunk[*i] != '$'
		&& chunk[*i] != '\0' && chunk[*i] != 34 && chunk[*i] != '\n')
		(*i)++;
	*b = (*i) - 1;
	//ft_printf("a:%d && b:%d\n", *a, *b);
	/*
	se calhar acrescentar uma condicao de [i] != 34 por causa da
	double quote
	ha alguma env var que possua double quote? nao creio
	9, 32, 34, $, \0, e agr \n?
	*/
}

char	*get_spec(int *a, int *b, char *chunk, t_execlist *execl)
{
	char	*env_name;
	char	*env_value;

	//ft_printf("Getting spec:\n");
	env_name = ft_substr(chunk, ((*a) + 1), ((*b) - (*a)));
	//ft_printf("env_name: '%s'\n", env_name);
	if (!env_name)
		return(NULL);
	if (env_name[0] == '?')
	{
		//printf("will go for exit_stt itoa\n");
		env_value = ft_itoa(*(execl->exit_stt));
	}
	else
	{
		//printf("will go for search_my_envp\n");
		env_value = search_my_envp(execl, env_name); //getenv(env_name);
	}
	if (!env_value)
		return(NULL);
	free(env_name);
	//ft_printf("spec: '%s'\n", env_value);
	return (env_value);
}

int	h_env_var(int *a, int *b, int *i, char **chunk, t_execlist *execl)
{
	char	*spec;

	//ft_printf("Inside the handler\n");
	get_positions(a, b, i, *chunk);
	spec = ft_strdup(get_spec(a, b, *chunk, execl));
	if (spec != NULL) //env valida
		*chunk = new_chnk(spec, *chunk, *a, *b);
	else //env nao existente
	{
		//ft_printf("Spec is NULL\n");
		//perror("Error handling environment variable ($)");
		//return (0);
		spec = (char *)ft_calloc(1, sizeof(char));
		spec[0] = '\0';
		*chunk = new_chnk(spec, *chunk, *a, *b);
		//free(spec); leva free dentro da new, chunk
	}
	if (*chunk == NULL)
	{
		ft_printf("minishell: error parsing ($) expander\n");
		return (0);
	}
	//else
		//printf("new chunk is '%s'\n", *chunk);
	return (1);
}

int	spec_char_chunk(t_execlist *execl, int j, int *a, int *b)
{
	int	i;
	int	flag;
	
	i = -1;
	flag = 1;
	while (execl->chunk[j]->og[++i] != '\0')
	{
		if (execl->chunk[j]->og[i] == 39)
			flag *= -1;
		if (execl->chunk[j]->og[i] == '$' && flag == 1)
		{
			if (execl->chunk[j]->og[i + 1]
				&& execl->chunk[j]->og[i + 1] != 32)
				h_env_var(a, b, &i, &execl->chunk[j]->og, execl);
			/*if (h_env_var(a, b, &i, &execl->chunk[j]->og, execl) == 0)
			{
				*(execl->exit_stt) = 1;
				return (0);
			}*/
		}
	}
	return (1);
}

int	spec_char_heredoc(t_execlist *execl, int j, int *a, int *b)
{
	int	i;
	int	flag;
	int	inf;
	
	inf = -1;
	//printf("inside heredoc spec char\n");
	while (execl->chunk[j]->infiles[++inf] != NULL)
	{
		i = -1;
		flag = 1;
		while (execl->chunk[j]->here_dcs[inf] == 1
			&& execl->chunk[j]->infiles[inf][++i] != '\0')
		{
			if (execl->chunk[j]->infiles[inf][i] == 39)
				flag *= -1;
			if (execl->chunk[j]->infiles[inf][i] == '$' && flag == 1)
			{
				if (execl->chunk[j]->og[i + 1]
					&& execl->chunk[j]->og[i + 1] != 32)
					h_env_var(a, b, &i, &execl->chunk[j]->og, execl);
				/*if (h_env_var(a, b, &i, &execl->chunk[j]->infiles[inf], execl) == 0)
				{
					*(execl->exit_stt) = 1;
					return (0);
				}*/
			}
		}
	}
	return (1);
}

int	special_char(t_execlist *execl)
{
	int		a;
	int		b;
	int		j;
	//int		i;
	//int		flag;

	j = -1;
	//printf("inside parser 3: spec char\n");
	a = 0;
	b = 0;
	while (execl->chunk[++j] != NULL)
	{
		if (spec_char_chunk(execl, j, &a, &b) == 0)
			return (0);
		if (execl->chunk[j]->infiles)
		{
			//printf("will enter heredoc spec char\n");
			if (spec_char_heredoc(execl, j, &a, &b) == 0)
				return (0);
		}
	}
	return(1);
}
//else, retorna normalmente sem fazer nada

/*

- aceitar valido $ sozinho como um char
	acho q ta, se tiver um SPACE depois nem sequer parsa
- aceitar $ errados e colocar como empty string '\0'
	nao sei se é do printf, mas a str vazia ta a dar stress
	ou ver se resulta assim noutro lado
	acho q era so do printf

-- o zé coloca um espaço, o default nao coloca nada e retira...
a minha, para ja, ta igual ao default bash
*/






/*
i = -1;
while (execl->chunk[j]->here_dcs[x] == 1
	&& execl->chunk[j]->infiles[x][i] != '\0')
{
	a = 0;
	b = 0;
	if (execl->chunk[j]->infiles[x][i] == 39)
		flag *= -1;
	if (execl->chunk[j]->infiles[x][i] == '$' && flag == 1)
	{
		if (h_env_var(&a, &b, &i, &execl->chunk[j]->infiles[x], execl) == 0)
		{
			*(execl->exit_stt) = 1;
			return(0);
		}
	}
}
*/

/*
int	special_char(t_execlist *execl)
{
	int		a;
	int		b;
	int		j;
	int		i;
	int		flag;

	j = -1;
	flag = 1;
	while (execl->chunk[++j] != NULL)
	{
		i = -1;
		while (execl->chunk[j]->og[++i] != '\0')
		{
			a = 0;
			b = 0;
			if (execl->chunk[j]->og[i] == 39)
				flag *= -1;
			if (execl->chunk[j]->og[i] == '$' && flag == 1)
			{
				if (h_env_var(&a, &b, &i, &execl->chunk[j]->og, execl) == 0)
				{
					*(execl->exit_stt) = 1;
					return(0);
				}
			}
		}
	}
	return(1);
}
*/