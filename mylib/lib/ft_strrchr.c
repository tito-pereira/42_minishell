/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:49:11 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:31:05 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (((char *)s)[i] != '\0')
		i++;
	if (((char *)s)[i] == (unsigned char)c)
		return (((char *)s) + i);
	while (i)
	{
		i--;
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (((char *)s) + i);
	}
	return (NULL);
}
