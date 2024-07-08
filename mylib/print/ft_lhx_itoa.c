/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lhx_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:18:44 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:39:27 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long unsigned int	ft_lhx_set_size(long unsigned int n)
{
	long unsigned int	counter;
	long unsigned int	tmp;

	counter = 1;
	tmp = 1;
	if (n > 0)
	{
		while ((n / tmp) >= 16)
		{
			tmp *= 16;
			counter++;
		}
	}
	return (counter);
}

char	*ft_lhx_reverse(char *str)
{
	long unsigned int	i;
	long unsigned int	size;
	long unsigned int	tmp;

	i = 0;
	size = 0;
	tmp = 0;
	while (str[size] != '\0')
		size++;
	while (i < (size / 2))
	{
		tmp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = tmp;
		i++;
	}
	return (str);
}

char	*ft_lhx_support(char *ret, long unsigned int tmp, \
	long unsigned int i, long unsigned int n)
{
	long unsigned int	k;
	char				b;

	if (n == 0)
		ret[0] = '0';
	while (tmp > 0)
	{
		k = tmp % 16;
		b = check_letter_x(k);
		ret[i] = b;
		tmp = tmp / 16;
		i++;
	}
	return (ret);
}

char	*ft_lhx_itoa(long unsigned int n)
{
	long unsigned int	i;
	long unsigned int	tmp;
	char				*ret;

	i = 0;
	tmp = n;
	ret = malloc((ft_lhx_set_size(n) + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret = ft_lhx_support(ret, tmp, i, n);
	ret[ft_lhx_set_size(n)] = '\0';
	ft_lhx_reverse(ret);
	return (ret);
}
