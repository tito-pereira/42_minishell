/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:39:11 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:31:15 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (len == 0 && s1[0] == '\0' && s2[0] == '\0')
		return (((char *)s1));
	if (s2[0] == '\0')
		return (((char *)s1));
	while (((char *)s1)[i] != '\0' && i < len)
	{
		while (((char *)s1)[i + j] == s2[j] && s1[i + j] != '\0'
				&& (i + j) < len)
			j++;
		if (len == 0)
			break ;
		if (s2[j] == '\0')
			return (((char *)s1) + i);
		j = 0;
		i++;
	}
	return (NULL);
}
