/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:05:48 by tibarbos          #+#    #+#             */
/*   Updated: 2023/12/26 18:05:16 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	death_star(va_list args, char *str, int *j, int *c)
{
	int		cc;
	t_pain	bois;

	bois.psize = 0;
	bois.str = str;
	bois.i = j;
	cc = *c;
	(*bois.i)++;
	bois.pex = c_valid_point(bois.str, bois.i);
	if (bois.pex == 1)
		bois.psize = check_point_size(bois.str, bois.i);
	if (ft_check_if_one(bois.str, bois.i) == 1)
		cc = normie(args, &cc, bois);
	else
	{
		if (ft_check_mw(bois.str, bois.i) == 1)
			cc = pain(args, &cc, bois);
		else
			cc = normie(args, &cc, bois);
	}
	*c = cc;
	*j = *bois.i;
}

int	pain(va_list args, int *c, t_pain bois)
{
	char	pad;
	int		cc;

	cc = *c;
	pad = ft_check_z_m(bois.str, bois.i);
	if (pad == '0')
		cc = cc + write_right(args, bois);
	else if (pad == '-')
		cc = cc + write_left(args, bois);
	else if (pad == 'f')
		cc = cc + write_right(args, bois);
	return (cc);
}

int	write_right(va_list args, t_pain bois)
{
	int		c;

	c = 0;
	bois.size = check_mw_size(bois.str, bois.i);
	c = c + ft_inic(args, bois);
	return (c);
}

int	write_left(va_list args, t_pain bois)
{
	int		c;

	c = 0;
	bois.size = check_mw_size(bois.str, bois.i);
	c = c + ft_inic(args, bois);
	return (c);
}

int	ft_inic(va_list args, t_pain bois)
{
	int		c;
	char	sp;

	c = 0;
	sp = p_check_spec_2(bois.str, bois.i);
	if (sp == 'c')
		c = ip_c_spec(args, bois);
	else if (sp == 's')
		c = ip_s_spec(args, bois);
	else if (sp == 'p')
		c = ip_p_spec(args, bois);
	else if (sp == 'd' || sp == 'i')
		c = ip_d_spec(args, bois);
	else if (sp == 'u')
		c = ip_u_spec(args, bois);
	else if (sp == 'x')
		c = ip_x_spec(args, bois);
	else if (sp == 'X')
		c = ip_bx_spec(args, bois);
	return (c);
}
