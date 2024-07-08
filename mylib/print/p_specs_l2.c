/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_specs_l2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:35:41 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 18:11:00 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_u_spec_right(unsigned int tmp, t_pain bois, char f2)
{
	int		c;
	char	pad;
	char	*ito;

	c = 0;
	ito = ft_long_itoa(tmp);
	ito = p_null_support(tmp, &bois, ito);
	if (f2 == '0' && bois.pex == 0)
		pad = '0';
	else
		pad = ' ';
	while (bois.size-- > 0)
		c = c + ft_putchar_c(pad);
	while (bois.psize-- > 0)
		c = c + ft_putchar_c('0');
	c = c + ft_putstr_c(ito);
	free (ito);
	return (c);
}

int	p_x_spec_zero(unsigned int tmp, t_pain bois, char pad, char f1)
{
	int		c;
	char	*ito;

	c = 0;
	ito = ft_hx_itoa(tmp);
	ito = p_null_support(tmp, &bois, ito);
	if (f1 == '#' && tmp > 0)
		bois.size -= 2;
	if (f1 == '#' && bois.pex == 0 && tmp > 0)
		c = c + ft_putstr_c("0x");
	if (bois.pex == 1)
		pad = ' ';
	while (bois.size-- > 0)
		c = c + ft_putchar_c(pad);
	if (f1 == '#' && bois.pex == 1 && tmp > 0)
		c = c + ft_putstr_c("0x");
	while (bois.psize-- > 0)
		c = c + ft_putchar_c('0');
	c = c + ft_putstr_c(ito);
	free (ito);
	return (c);
}

int	p_bx_spec_zero(unsigned int tmp, t_pain bois, char pad, char f1)
{
	int		c;
	char	*ito;

	c = 0;
	ito = ft_hbx_itoa(tmp);
	ito = p_null_support(tmp, &bois, ito);
	if (f1 == '#' && tmp > 0)
		bois.size -= 2;
	if (f1 == '#' && bois.pex == 0 && tmp > 0)
		c = c + ft_putstr_c("0X");
	if (bois.pex == 1)
		pad = ' ';
	while (bois.size-- > 0)
		c = c + ft_putchar_c(pad);
	if (f1 == '#' && bois.pex == 1 && tmp > 0)
		c = c + ft_putstr_c("0X");
	while (bois.psize-- > 0)
		c = c + ft_putchar_c('0');
	c = c + ft_putstr_c(ito);
	free (ito);
	return (c);
}
