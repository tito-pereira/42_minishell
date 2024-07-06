/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:52:03 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 00:52:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr2(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (unsigned char) c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (unsigned char)c)
		return ((char *)&str[i]);
	return (0);
}

char	*ft_strjoin2(char *bufftxt, char *temp)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	if (!bufftxt)
	{
		bufftxt = malloc(sizeof(char) * 1);
		bufftxt[0] = '\0';
	}
	join = malloc(sizeof(char) * (ft_strlen2(bufftxt) + ft_strlen2(temp) + 1));
	if (!join)
		return (NULL);
	while (bufftxt[++i])
		join[i] = bufftxt[i];
	while (temp[++j])
		join[j + i] = temp[j];
	join[i + j] = '\0';
	free(bufftxt);
	return (join);
}

char	*ft_strtrim_l(char *bufftxt)
{
	char	*final_line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!bufftxt[i])
		return (NULL);
	while (bufftxt[i] && bufftxt[i] != '\n')
		i++;
	final_line = malloc(sizeof(char) * (i + 2));
	if (!bufftxt)
		return (NULL);
	j = -1;
	while (++j <= i)
		final_line[j] = bufftxt[j];
	final_line[j] = '\0';
	return (final_line);
}

char	*ft_strtrim_r(char *bufftxt)
{
	char	*next_line;
	size_t	i;
	size_t	j;

	i = 0;
	while (bufftxt[i] && bufftxt[i] != '\n')
		i++;
	if (!bufftxt[i])
	{
		free(bufftxt);
		return (NULL);
	}
	next_line = malloc(sizeof(char) * (ft_strlen2(bufftxt) - i));
	if (!bufftxt)
		return (NULL);
	j = -1;
	while (++i < ft_strlen2(bufftxt))
		next_line[++j] = bufftxt[i];
	next_line[++j] = '\0';
	free(bufftxt);
	return (next_line);
}
