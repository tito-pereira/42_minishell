/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pain_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:45:06 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 17:26:47 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_if_s(char *str, int *j)
{
	int	i;

	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '.'
		|| str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
	{
		i++;
		if (str[i] == 's')
			return (1);
	}
	return (0);
}

int	ft_check_if_one(char *str, int *j)
{
	int	i;

	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#' || str[i] == '.'
		|| str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
	{
		i++;
		if (str[i] == '%')
			return (1);
	}
	return (0);
}

char	ft_check_z_m(char *str, int *j)
{
	char	f;
	int		i;

	f = 'f';
	i = *j;
	while (str[i] == ' ' || str[i] == '+' || str[i] == '#'
		|| str[i] == '.' || str[i] == '-' || str[i] == '0')
	{
		if (str[i] == '0')
			f = '0';
		else if (str[i] == '-')
		{
			f = '-';
			break ;
		}
		i++;
	}
	return (f);
}

int	ft_mini_atoi(char *str, int *j)
{
	int	i;
	int	ret;

	i = *j;
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = (ret * 10) + (str[i] - 48);
		i++;
	}
	return (ret);
}
