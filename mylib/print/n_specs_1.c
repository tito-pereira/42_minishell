/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_specs_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:11:07 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 18:21:43 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_c_spec(va_list arg)
{
	int	tmp;

	tmp = va_arg(arg, int);
	ft_putchar((char)tmp);
	return (1);
}

int	ft_s_spec(va_list arg, t_pain bois)
{
	char	*tmp;
	int		c;

	c = 0;
	tmp = va_arg(arg, char *);
	if (tmp == NULL && bois.pex == 1)
	{
		if (bois.psize > 5)
		{
			c = ft_putstr_c("(null)");
			return (c);
		}
		else if (bois.psize < 6)
			return (0);
	}
	else if (tmp == NULL && bois.pex == 0)
	{
		c = ft_putstr_c("(null)");
		return (c);
	}
	if (bois.pex == 1)
		c = ft_putstr_c_p(tmp, bois.psize);
	else
		c = ft_putstr_c(tmp);
	return (c);
}

int	p_flags(char f, int c)
{
	if (f == '+')
	{
		ft_putchar('+');
		c++;
	}
	else if (f == ' ')
	{
		ft_putchar(' ');
		c++;
	}
	return (c);
}

int	ft_p_spec(va_list arg, char f)
{
	void				*tmp;
	long unsigned int	i;
	int					c;

	c = 0;
	tmp = va_arg(arg, void *);
	i = (long unsigned int) tmp;
	if (tmp == NULL)
	{
		c = ft_putstr_c("(nil)");
		return (c);
	}
	c = p_flags(f, c);
	ft_putstr("0x");
	ft_putphex_c(i, &c);
	return (c + 2);
}

int	ft_d_spec(va_list arg, char f, t_pain bois)
{
	int		tmp;
	int		c;
	char	*ito;

	c = 0;
	tmp = va_arg(arg, int);
	if (tmp == 0 && bois.pex == 1)
		ito = NULL;
	else
		ito = f_itoa(tmp);
	if ((f == '+') && (tmp >= 0))
		c = c + ft_putchar_c('+');
	else if ((f == ' ') && (tmp >= 0) && (bois.pex == 0))
		c = c + ft_putchar_c(' ');
	else if (tmp < 0)
		c = c + ft_putchar_c('-');
	bois.psize -= ff_strlen(ito);
	while (bois.psize-- > 0)
		c = c + ft_putchar_c('0');
	c = c + ft_putstr_c(ito);
	if (ito)
		free (ito);
	return (c);
}
