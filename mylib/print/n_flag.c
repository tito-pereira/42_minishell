/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 08:46:16 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/21 16:42:06 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	ft_control_flag(char *str, int *i)
{
	char	f;
	char	s;

	f = 'f';
	s = ft_check_spec(str, i);
	if (s == 'd')
		f = ft_check_d(str, i);
	else if (s == 'x')
		f = ft_check_x(str, i);
	return (f);
}

char	ft_check_spec(char *str, int *j)
{
	int	i;

	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '.'
		|| str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
	{
		i++;
		if (str[i] == 'd' || str[i] == 'i' || str[i] == 'p')
			return ('d');
		else if (str[i] == 'x' || str[i] == 'X')
			return ('x');
	}
	if (see_if_spec(str[i]) == 1)
		*j = i;
	return ('f');
}

char	ft_check_d(char *str, int *j)
{
	char	f;
	int		i;

	f = 'f';
	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '.'
		|| str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
	{
		if (str[i] == ' ')
			f = ' ';
		else if (str[i] == '+')
		{
			f = '+';
			break ;
		}
		i++;
	}
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '.'
		|| str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	*j = i;
	return (f);
}

char	ft_check_x(char *str, int *j)
{
	char	f;
	int		i;

	f = 'f';
	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '.'
		|| str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
	{
		if (str[i] == '#')
		{
			f = '#';
			break ;
		}
		i++;
	}
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '.'
		|| str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	*j = i;
	return (f);
}
