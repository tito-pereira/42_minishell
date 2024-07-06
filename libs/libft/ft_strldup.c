/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:44:37 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/05 10:37:44 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Duplicates the string up to 'l' characters. */
char	*ft_strldup(const char *s, size_t l)
{
	size_t	i;
	char	*s_dup;

	i = 0;
	s_dup = malloc(sizeof(char) * (l + 1));
	if (!s_dup)
		return (NULL);
	while (i < l)
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}
