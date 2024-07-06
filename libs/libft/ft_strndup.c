/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:39:47 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/05 10:37:48 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Duplicates the string starting from the 'n' value. */
char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*s_dup;

	i = 0;
	s_dup = malloc(sizeof(char) * (ft_strlen(s) - n + 1) + 1);
	if (!s_dup)
		return (NULL);
	while (s[n])
	{
		s_dup[i++] = s[n++];
	}
	s_dup[i] = '\0';
	return (s_dup);
}
