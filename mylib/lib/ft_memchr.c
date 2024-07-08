/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:28:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:27:53 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (((void *)s) + i);
		i++;
	}
	return (NULL);
}
