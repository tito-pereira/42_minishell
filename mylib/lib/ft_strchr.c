/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:48:47 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:29:17 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (s[i] == '\0' && c == '\0')
		return (s + i);
	while (s[i] != '\0')
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (s + i);
	return (NULL);
}
