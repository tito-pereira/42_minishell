/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 17:35:38 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	p_check_spec(char *str, int *j)
{
	int	i;

	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '.'
		|| str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
	{
		i++;
		if (str[i] == 'd' || str[i] == 'i' || str[i] == 'p')
			return (str[i]);
		else if (str[i] == 'x' || str[i] == 'X')
			return (str[i]);
		else if (str[i] == 's' || str[i] == 'u' || str[i] == 'c')
		{
			*j = i;
			return (str[i]);
		}
	}
	if (see_if_spec(str[i]) == 1)
		*j = i;
	return (str[i]);
}

char	p_check_d(char *s, int *j)
{
	char	f;
	int		i;

	f = 'f';
	i = *j;
	while (s[i] == ' ' || s[i] == '+' || s[i] == '#'
		|| s[i] == '-' || (s[i] >= '0' && s[i] <= '9'))
	{
		if (s[i] == '+')
		{
			f = '+';
			break ;
		}
		i++;
	}
	while (s[i] == ' ' || s[i] == '+' || s[i] == '#' || s[i] == '0'
		|| s[i] == '-' || s[i] == '.' || (s[i] >= '0' && s[i] <= '9'))
		i++;
	*j = i;
	return (f);
}

char	p_check_x(char *s, int *j)
{
	char	f;
	int		i;

	f = 'f';
	i = *j;
	while (s[i] == ' ' || s[i] == '+' || s[i] == '#' || s[i] == '0'
		|| s[i] == '-' || (s[i] >= '0' && s[i] <= '9'))
	{
		if (s[i] == '#')
		{
			f = '#';
			break ;
		}
		i++;
	}
	while (s[i] == ' ' || s[i] == '+' || s[i] == '#' || s[i] == '0'
		|| s[i] == '-' || s[i] == '.' || (s[i] >= '0' && s[i] <= '9'))
		i++;
	*j = i;
	return (f);
}

char	p_control_flag(char *str, int *i)
{
	char	f;
	char	s;

	s = p_check_spec(str, i);
	if (s == 'd' || s == 'i' || s == 'p')
		f = p_check_d(str, i);
	else if (s == 'x' || s == 'X')
		f = p_check_x(str, i);
	else
		return (s);
	return (f);
}

char	p_check_spec_2(char *str, int *j)
{
	int	i;

	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '.'
		|| str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
	{
		i++;
		if (str[i] == 'd' || str[i] == 'i' || str[i] == 'p')
			return (str[i]);
		else if (str[i] == 'x' || str[i] == 'X')
			return (str[i]);
		else if (str[i] == 's' || str[i] == 'u' || str[i] == 'c')
		{
			return (str[i]);
		}
	}
	return (str[i]);
}
