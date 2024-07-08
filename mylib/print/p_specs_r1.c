/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_specs_r1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:22:53 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 18:17:04 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_c_spec_r(int tmp, int size, char pad)
{
	int	c;

	c = 0;
	while (size > 0)
	{
		c = c + ft_putchar_c(pad);
		size--;
	}
	ft_putchar(((char)tmp));
	c++;
	return (c);
}

int	p_s_spec_r(char *tmp, t_pain bois, char pad)
{
	int	c;

	c = 0;
	while (bois.size > 0)
	{
		c = c + ft_putchar_c(pad);
		bois.size--;
	}
	if (bois.pex == 0)
		c = c + ft_putstr_c(tmp);
	else if (bois.pex == 1)
		c = c + ft_putstr_c_p(tmp, bois.psize);
	return (c);
}

int	p_p_spec_zeros(long unsigned int i, int size, char pad, char f1)
{
	int	c;

	c = 0;
	if (f1 == '+')
	{
		c = c + ft_putchar_c('+');
		size--;
	}
	c = c + ft_putstr_c("0x");
	size = size - 2;
	while (size > 0)
	{
		c = c + ft_putchar_c(pad);
		size--;
	}
	ft_putphex_c(i, &c);
	return (c);
}

int	p_d_spec_space_m(int tmp, t_pain bois, char pad, char f1)
{
	int		c;
	char	*ito;

	c = 0;
	ito = f_itoa(tmp);
	ito = p_null_support(tmp, &bois, ito);
	if (f1 == '+' && tmp >= 0)
	{
		c = c + ft_putchar_c('+');
		bois.size--;
	}
	if (tmp < 0)
	{
		c = c + ft_putchar_c('-');
		bois.size--;
	}
	while (bois.psize-- > 0)
		c = c + ft_putchar_c('0');
	c = c + ft_putstr_c(ito);
	while (bois.size-- > 0)
		c = c + ft_putchar_c(pad);
	free (ito);
	return (c);
}

int	p_d_spec_space_f(int tmp, t_pain bois, char pad, char f1)
{
	int		c;
	char	*ito;

	c = 0;
	ito = f_itoa(tmp);
	ito = p_null_support(tmp, &bois, ito);
	if (tmp < 0 || f1 == '+')
		bois.size--;
	while (bois.size-- > 0)
		c = c + ft_putchar_c(pad);
	if (f1 == '+' && tmp >= 0)
		c = c + ft_putchar_c('+');
	else if (tmp < 0)
		c = c + ft_putchar_c('-');
	while (bois.psize-- > 0)
		c = c + ft_putchar_c('0');
	c = c + ft_putstr_c(ito);
	free (ito);
	return (c);
}
