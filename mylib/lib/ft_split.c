/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:13:56 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:29:08 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_last_o(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] != c && s1[i] != '\0')
		i++;
	if (i < 0)
		i = 0;
	return (i);
}

int	ft_num_o(char *s1, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i] != '\0')
	{
		while (s1[i] == c)
			i++;
		if (s1[i] != c && s1[i] != '\0')
			count++;
		while (s1[i] && s1[i] != c)
			i++;
	}
	return (count);
}

int	ft_fst_o(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == c)
	{
		i++;
	}
	if (i < 0)
		i = 0;
	return (i);
}

char	**ft_supportt(char **ret, const char *s1, char c, int i)
{
	int		j;
	int		a;
	char	*s2;

	a = 0;
	j = 0;
	s2 = ((char *)s1);
	while (i > 0)
	{
		a = ft_fst_o(((char *)s1), c);
		s2 = ((char *)s1) + (a);
		s1 = s2;
		a = ft_fst_o(((char *)s1), c);
		ret[j] = ft_substr(((char *)s1), 0, ft_last_o(((char *)s1), c));
		s2 = ((char *)s1) + ft_last_o(((char *)s1), c);
		s1 = s2;
		j++;
		i--;
	}
	return (ret);
}

char	**ft_split(char const *s1, char c)
{
	int		i;
	int		n;
	char	**ret;

	n = ft_num_o(((char *)s1), c);
	ret = (char **)malloc((n + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = n;
	ret = ft_supportt(ret, s1, c, i);
	ret[n] = NULL;
	return (ret);
}
