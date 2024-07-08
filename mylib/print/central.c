/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:58:36 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 17:34:57 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	see_if_spec(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == '%'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	else
		return (0);
}

int	ft_treat_spec(va_list arg, char c, char f, t_pain bois)
{
	int	r;

	r = 1;
	if (c == 'c')
		r = ft_c_spec(arg);
	else if (c == 's')
		r = ft_s_spec(arg, bois);
	else if (c == 'p')
		r = ft_p_spec(arg, f);
	else if (c == 'd' || c == 'i')
		r = ft_d_spec(arg, f, bois);
	else if (c == 'u')
		r = ft_u_spec(arg, bois);
	else if (c == 'x')
		r = ft_x_spec(arg, f, bois);
	else if (c == 'X')
		r = ft_bx_spec(arg, f, bois);
	else if (c == '%')
		ft_putchar('%');
	return (r);
}

int	normie(va_list args, int *c, t_pain bois)
{
	int		j;
	int		cc;
	char	f;

	f = 'f';
	cc = *c;
	j = *bois.i;
	f = ft_control_flag(bois.str, &j);
	if (see_if_spec(bois.str[j]) == 1)
		cc = cc + ft_treat_spec(args, bois.str[j], f, bois);
	*bois.i = j;
	return (cc);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		c;

	va_start(args, s);
	i = -1;
	c = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == '%')
			death_star(args, ((char *)s), &i, &c);
		else
		{
			ft_putchar(s[i]);
			c++;
		}
	}
	va_end(args);
	return (c);
}
