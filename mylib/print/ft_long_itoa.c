/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:46:38 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/11 10:40:52 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_l_set_size(unsigned int n)
{
	unsigned int	counter;
	unsigned int	tmp;

	counter = 1;
	tmp = 1;
	if (n > 0)
	{
		while ((n / tmp) >= 10)
		{
			tmp *= 10;
			counter++;
		}
	}
	return (counter);
}

char	*ft_l_reverse(char *str)
{
	unsigned int	i;
	unsigned int	size;
	unsigned int	tmp;

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

char	*ft_l_support(char *ret, unsigned int tmp, unsigned int i, \
	unsigned int n)
{
	if (n == 0)
		ret[0] = '0';
	while (tmp > 0)
	{
		ret[i] = (tmp % 10) + 48;
		tmp = tmp / 10;
		i++;
	}
	return (ret);
}

char	*ft_long_itoa(unsigned int n)
{
	unsigned int	i;
	unsigned int	tmp;
	char			*ret;

	i = 0;
	tmp = n;
	ret = malloc((ft_l_set_size(n) + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret = ft_l_support(ret, tmp, i, n);
	ret[ft_l_set_size(n)] = '\0';
	ft_l_reverse(ret);
	return (ret);
}
