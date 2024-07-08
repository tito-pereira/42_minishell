/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_hex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:06:37 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 16:41:24 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	check_letter_x(unsigned int i)
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

void	ft_puthex_c(unsigned int n, int *c)
{
	char	h;

	if (n > 15)
	{
		ft_puthex_c((n / 16), c);
		ft_puthex_c((n % 16), c);
	}
	else
	{
		h = check_letter_x(n);
		ft_putchar(h);
		(*c)++;
	}
}

char	check_letter_bx(unsigned int i)
{
	char	c;

	if (i == 10)
		c = 'A';
	else if (i == 11)
		c = 'B';
	else if (i == 12)
		c = 'C';
	else if (i == 13)
		c = 'D';
	else if (i == 14)
		c = 'E';
	else if (i == 15)
		c = 'F';
	else
		c = i + 48;
	return (c);
}

void	ft_putbhex_c(unsigned int n, int *c)
{
	char	h;

	if (n > 15)
	{
		ft_putbhex_c((n / 16), c);
		ft_putbhex_c((n % 16), c);
	}
	else
	{
		h = check_letter_bx(n);
		ft_putchar(h);
		(*c)++;
	}
}
