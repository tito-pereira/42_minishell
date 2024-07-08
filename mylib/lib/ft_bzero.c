/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:30:12 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:23:05 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *dest, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)dest)[i] = '\0';
		i++;
	}
	return (dest);
}
