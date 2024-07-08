/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_specs_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:20:14 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 17:33:07 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ip_c_spec(va_list arg, t_pain bois)
{
	char	f2;
	int		tmp;
	int		c;

	c = 0;
	tmp = va_arg(arg, int);
	f2 = ft_check_z_m(bois.str, bois.i);
	p_control_flag(bois.str, bois.i);
	bois.size--;
	if (f2 == '-')
		c = c + p_c_spec_l(tmp, bois.size, ' ');
	else if (f2 == 'f' || f2 == '0')
		c = c + p_c_spec_r(tmp, bois.size, ' ');
	return (c);
}

int	ip_s_spec(va_list arg, t_pain bois)
{
	char	*tmp;
	int		c;
	char	f2;

	c = 0;
	tmp = va_arg(arg, char *);
	f2 = ft_check_z_m(bois.str, bois.i);
	p_control_flag(bois.str, bois.i);
	if ((tmp == NULL && bois.pex == 0)
		|| (tmp == NULL && bois.pex == 1 && bois.psize > 5))
		tmp = "(null)";
	else if (tmp == NULL && bois.pex == 1 && bois.psize < 6)
		tmp = NULL;
	if (bois.pex == 1)
		bois.size = bois.size - ft_strlen_p(tmp, bois.psize);
	else if (bois.pex == 0)
		bois.size = bois.size - ff_strlen(tmp);
	if (f2 == '-')
		c = c + p_s_spec_l(tmp, bois, ' ');
	else
		c = c + p_s_spec_r(tmp, bois, ' ');
	return (c);
}

int	ip_p_spec(va_list arg, t_pain bois)
{
	void	*tmp;
	int		c;
	char	f1;
	char	f2;
	char	*ito;

	c = 0;
	tmp = va_arg(arg, void *);
	if (tmp == NULL)
		return (ip_p_spec_null(tmp, bois));
	f2 = ft_check_z_m(bois.str, bois.i);
	f1 = p_control_flag(bois.str, bois.i);
	ito = ft_lhx_itoa(((long unsigned int)tmp));
	bois.size = bois.size - ff_strlen(ito);
	if (f2 == '-')
		c = c + p_p_spec_space_m(((long unsigned int)tmp), bois.size, ' ', f1);
	else if (f2 == 'f')
		c = c + p_p_spec_space_f(((long unsigned int)tmp), bois.size, ' ', f1);
	else if (f2 == '0')
		c = c + p_p_spec_zeros(((long unsigned int)tmp), bois.size, '0', f1);
	free (ito);
	return (c);
}

int	ip_d_spec(va_list arg, t_pain bois)
{
	int		tmp;
	int		c;
	char	f1;
	char	f2;
	char	*ito;

	c = 0;
	tmp = va_arg(arg, int);
	f2 = ft_check_z_m(bois.str, bois.i);
	f1 = p_control_flag(bois.str, bois.i);
	ito = f_itoa(tmp);
	bois.size = bois.size - ff_strlen(ito);
	if (f2 == '-')
		c = c + p_d_spec_space_m(tmp, bois, ' ', f1);
	else if (f2 == 'f')
		c = c + p_d_spec_space_f(tmp, bois, ' ', f1);
	else if (f2 == '0')
		c = c + p_d_spec_zero(tmp, bois, '0', f1);
	free (ito);
	return (c);
}
