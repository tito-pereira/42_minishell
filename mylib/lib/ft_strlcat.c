/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:26:19 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:29:53 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ret;
	size_t	restsize;

	ret = ft_strlen(dest) + ft_strlen(((char *)src));
	if (size == 0 || size <= ft_strlen(dest))
		return (ft_strlen((char *)src) + size);
	j = 0;
	i = ft_strlen(dest);
	restsize = size - i;
	while (((char *)src)[j] != '\0' && j < restsize - 1)
	{
		dest[i] = ((char *)src)[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (ret);
}
