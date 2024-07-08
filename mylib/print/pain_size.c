/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pain_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:06:25 by tibarbos          #+#    #+#             */
/*   Updated: 2023/12/26 18:04:55 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	mw_atoi_pnt_1(char *str, int *j)
{
	int	i;

	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '0'
		|| str[i] == '.' || str[i] == '-'
		|| (str[i] >= '1' && str[i] <= '9'))
		i++;
	if (see_if_spec(str[i]) == 1)
	{
		i--;
		while (str[i] >= '0' && str[i] <= '9')
			i--;
		return (i + 1);
	}
	return (0);
}

int	mw_atoi_pnt_2(char *str, int *j)
{
	int	i;

	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '0'
		|| str[i] == '.' || str[i] == '-'
		|| (str[i] >= '1' && str[i] <= '9'))
		i++;
	if (see_if_spec(str[i]) == 1)
	{
		i--;
		while (str[i] >= '0' && str[i] <= '9')
			i--;
		if (str[i] == '.')
		{
			i--;
			while (str[i] >= '0' && str[i] <= '9')
				i--;
			return (i + 1);
		}
	}
	return (0);
}

int	point_atoi_pointer(char *str, int *j)
{
	int	i;

	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '0'
		|| str[i] == '.' || str[i] == '-'
		|| (str[i] >= '1' && str[i] <= '9'))
		i++;
	if (see_if_spec(str[i]) == 1)
	{
		i--;
		while (str[i] >= '0' && str[i] <= '9')
			i--;
		if (str[i] == '.')
			return (i + 1);
	}
	return (0);
}

int	check_mw_size(char *str, int *i)
{
	int	s;
	int	p;

	s = 0;
	if (c_valid_mw_point(str, i) == 1)
		p = mw_atoi_pnt_2(str, i);
	else if (c_valid_min_w(str, i) == 1)
		p = mw_atoi_pnt_1(str, i);
	s = ft_mini_atoi(str, &p);
	return (s);
}

int	check_point_size(char *str, int *i)
{
	int	s;
	int	p;

	s = 0;
	if (c_valid_point(str, i) == 1)
		p = point_atoi_pointer(str, i);
	s = ft_mini_atoi(str, &p);
	return (s);
}
