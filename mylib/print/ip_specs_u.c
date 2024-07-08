/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_specs_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:40:30 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 18:36:52 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_p_null_space_m(char *tmp, int size, char pad)
{
	int	c;

	c = 0;
	c = c + ft_putstr_c(tmp);
	while (size > 0)
	{
		c = c + ft_putchar_c(pad);
		size--;
	}
	return (c);
}

int	p_p_null_space_f(char *tmp, int size, char pad)
{
	int	c;

	c = 0;
	while (size > 0)
	{
		c = c + ft_putchar_c(pad);
		size--;
	}
	c = c + ft_putstr_c(tmp);
	return (c);
}

int	ip_p_spec_null(void *tmp, t_pain bois)
{
	int		c;
	char	f2;
	char	*n;

	c = 0;
	f2 = ft_check_z_m(bois.str, bois.i);
	p_control_flag(bois.str, bois.i);
	n = "(nil)";
	tmp = n;
	bois.size = bois.size - ff_strlen(((char *)tmp));
	if (f2 == '-')
		c = c + p_p_null_space_m(((char *)tmp), bois.size, ' ');
	else if (f2 == 'f' || f2 == '0')
		c = c + p_p_null_space_f(((char *)tmp), bois.size, ' ');
	return (c);
}

char	*p_null_support(long unsigned int tmp, t_pain *bois, char *ito)
{
	if (tmp == 0 && bois->pex == 1 && bois->psize == 0)
	{
		ito = NULL;
		bois->size++;
	}
	if (bois->pex == 1)
		bois->psize -= ff_strlen(ito);
	if (bois->psize >= 0)
		bois->size -= bois->psize;
	return (ito);
}

void	d_support(t_pain *bois, char f1, int tmp, int *c)
{
	if ((f1 == '+' && tmp >= 0) || tmp < 0)
	{
		if ((tmp >= 0 && f1 == '+') && bois->pex == 0)
			*c = *c + ft_putchar_c('+');
		else if ((tmp < 0) && bois->pex == 0)
			*c = *c + ft_putchar_c('-');
		bois->size--;
	}
}
