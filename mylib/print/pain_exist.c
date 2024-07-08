/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pain_exist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:47:05 by tibarbos          #+#    #+#             */
/*   Updated: 2023/12/26 18:04:15 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	c_valid_min_w(char *str, int *j)
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
		while (str[i] == '0' || str[i] == '.')
			i--;
		if (str[i] >= '1' && str[i] <= '9')
			return (1);
	}
	return (0);
}

int	c_valid_point(char *str, int *j)
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
			return (1);
	}
	return (0);
}

int	c_valid_mw_point(char *str, int *j)
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
			while (str[i] == '0')
				i--;
			if (str[i] >= '1' && str[i] <= '9')
				return (1);
		}
	}
	return (0);
}

int	ft_check_mw(char *str, int *i)
{
	if (c_valid_min_w(str, i) == 1)
	{
		if (c_valid_point(str, i) == 1)
		{
			if (c_valid_mw_point(str, i) == 1)
				return (1);
			else
				return (0);
		}
		return (1);
	}
	return (0);
}
