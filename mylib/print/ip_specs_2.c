/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_specs_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:28:33 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 15:09:11 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ip_u_spec(va_list arg, t_pain bois)
{
	unsigned int		tmp;
	int					c;
	char				f2;
	char				*ito;

	c = 0;
	tmp = va_arg(arg, unsigned int);
	f2 = ft_check_z_m(bois.str, bois.i);
	p_control_flag(bois.str, bois.i);
	ito = ft_long_itoa(tmp);
	bois.size = bois.size - ff_strlen(ito);
	if (f2 == '-')
		c = c + p_u_spec_left(tmp, bois, ' ');
	else if (f2 == '0' || f2 == 'f')
		c = c + p_u_spec_right(tmp, bois, f2);
	free (ito);
	return (c);
}

int	ip_x_spec(va_list arg, t_pain bois)
{
	unsigned int		tmp;
	int					c;
	char				f1;
	char				f2;
	char				*ito;

	c = 0;
	tmp = va_arg(arg, unsigned int);
	f2 = ft_check_z_m(bois.str, bois.i);
	f1 = p_control_flag(bois.str, bois.i);
	ito = ft_hx_itoa(tmp);
	bois.size = bois.size - ff_strlen(ito);
	if (f2 == '-')
		c = c + p_x_spec_space_m(tmp, bois, ' ', f1);
	else if (f2 == 'f')
		c = c + p_x_spec_space_f(tmp, bois, ' ', f1);
	else if (f2 == '0')
		c = c + p_x_spec_zero(tmp, bois, '0', f1);
	free (ito);
	return (c);
}

int	ip_bx_spec(va_list arg, t_pain bois)
{
	unsigned int		tmp;
	int					c;
	char				f1;
	char				f2;
	char				*ito;

	c = 0;
	tmp = va_arg(arg, unsigned int);
	f2 = ft_check_z_m(bois.str, bois.i);
	f1 = p_control_flag(bois.str, bois.i);
	ito = ft_hbx_itoa(tmp);
	bois.size = bois.size - ff_strlen(ito);
	if (f2 == '-')
		c = c + p_bx_spec_space_m(tmp, bois, ' ', f1);
	else if (f2 == 'f')
		c = c + p_bx_spec_space_f(tmp, bois, ' ', f1);
	else if (f2 == '0')
		c = c + p_bx_spec_zero(tmp, bois, '0', f1);
	free (ito);
	return (c);
}
