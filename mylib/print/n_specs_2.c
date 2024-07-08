/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_specs_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:43:30 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 16:42:28 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_u_spec(va_list arg, t_pain bois)
{
	unsigned int	tmp;
	int				c;
	char			*ito;

	c = 0;
	tmp = va_arg(arg, unsigned int);
	if (tmp == 0 && bois.pex == 1)
		ito = NULL;
	else
		ito = ft_long_itoa(tmp);
	bois.psize -= ff_strlen(ito);
	while (bois.psize > 0)
	{
		ft_putchar('0');
		c++;
		bois.psize--;
	}
	c = c + ft_putstr_c(ito);
	if (ito)
		free (ito);
	return (c);
}

int	ft_x_spec(va_list arg, char f, t_pain bois)
{
	unsigned int	tmp;
	int				c;
	char			*ito;

	c = 0;
	tmp = va_arg(arg, unsigned int);
	if (tmp == 0 && bois.pex == 1)
		ito = NULL;
	else
		ito = ft_hx_itoa(tmp);
	if ((f == '#') && (tmp > 0))
		c = c + ft_putstr_c("0x");
	bois.psize -= ff_strlen(ito);
	while (bois.psize > 0)
	{
		ft_putchar('0');
		c++;
		bois.psize--;
	}
	c = c + ft_putstr_c(ito);
	if (ito)
		free (ito);
	return (c);
}

int	ft_bx_spec(va_list arg, char f, t_pain bois)
{
	unsigned int	tmp;
	int				c;
	char			*ito;

	c = 0;
	tmp = va_arg(arg, unsigned int);
	if (tmp == 0 && bois.pex == 1)
		ito = NULL;
	else
		ito = ft_hbx_itoa(tmp);
	if ((f == '#') && (tmp > 0))
		c = c + ft_putstr_c("0X");
	bois.psize -= ff_strlen(ito);
	while (bois.psize > 0)
	{
		ft_putchar('0');
		c++;
		bois.psize--;
	}
	c = c + ft_putstr_c(ito);
	if (ito)
		free (ito);
	return (c);
}
