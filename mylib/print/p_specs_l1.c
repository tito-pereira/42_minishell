/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_specs_l1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:25:43 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 18:33:34 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_c_spec_l(int tmp, int size, char pad)
{
	int	c;

	c = 0;
	ft_putchar(((char)tmp));
	c++;
	while (size > 0)
	{
		c = c + ft_putchar_c(pad);
		size--;
	}
	return (c);
}

int	p_s_spec_l(char *tmp, t_pain bois, char pad)
{
	int	c;

	c = 0;
	if (bois.pex == 0)
		c = c + ft_putstr_c(tmp);
	else if (bois.pex == 1)
		c = c + ft_putstr_c_p(tmp, bois.psize);
	while (bois.size > 0)
	{
		c = c + ft_putchar_c(pad);
		bois.size--;
	}
	return (c);
}

int	p_p_spec_space_m(long unsigned int i, int size, char pad, char f1)
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
	ft_putphex_c(i, &c);
	while (size > 0)
	{
		c = c + ft_putchar_c(pad);
		size--;
	}
	return (c);
}

int	p_p_spec_space_f(long unsigned int i, int size, char pad, char f1)
{
	int	c;

	c = 0;
	size = size - 2;
	if (f1 == '+')
		size--;
	while (size > 0)
	{
		c = c + ft_putchar_c(pad);
		size--;
	}
	if (f1 == '+')
		c = c + ft_putchar_c('+');
	c = c + ft_putstr_c("0x");
	ft_putphex_c(i, &c);
	return (c);
}

int	p_d_spec_zero(int tmp, t_pain bois, char pad, char f1)
{
	int		c;
	char	*ito;

	c = 0;
	ito = f_itoa(tmp);
	ito = p_null_support(tmp, &bois, ito);
	d_support(&bois, f1, tmp, &c);
	if (bois.pex == 1)
		pad = ' ';
	while (bois.size-- > 0)
		c = c + ft_putchar_c(pad);
	if ((tmp >= 0 && f1 == '+') && bois.pex == 1)
		c = c + ft_putchar_c('+');
	else if ((tmp < 0) && bois.pex == 1)
		c = c + ft_putchar_c('-');
	while (bois.psize-- > 0)
		c = c + ft_putchar_c('0');
	c = c + ft_putstr_c(ito);
	free (ito);
	return (c);
}
