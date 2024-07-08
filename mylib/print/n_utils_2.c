/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:26:12 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 17:38:49 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

int	ft_putchar_c(char c)
{
	write (1, &c, 1);
	return (1);
}

char	check_letter_p(long unsigned int i)
{
	char	c;

	if (i == 10)
		c = 'a';
	else if (i == 11)
		c = 'b';
	else if (i == 12)
		c = 'c';
	else if (i == 13)
		c = 'd';
	else if (i == 14)
		c = 'e';
	else if (i == 15)
		c = 'f';
	else
		c = i + 48;
	return (c);
}

void	ft_putphex_c(long unsigned int n, int *c)
{
	char	h;

	if (n > 15)
	{
		ft_putphex_c((n / 16), c);
		ft_putphex_c((n % 16), c);
	}
	else
	{
		h = check_letter_p(n);
		ft_putchar(h);
		(*c)++;
	}
}

void	ft_put_uns_nbr(unsigned int n, int *c)
{
	if (n > 9)
	{
		ft_put_uns_nbr((n / 10), c);
		ft_put_uns_nbr((n % 10), c);
	}
	else
	{
		ft_putchar(n + 48);
		(*c)++;
	}
}
