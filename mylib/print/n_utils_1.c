/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_utils_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:55:42 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 17:27:34 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ff_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_p(char *str, int psize)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while ((str[i] != '\0') && (psize > 0))
	{
		i++;
		psize--;
	}
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != '\0')
	{
		write (1, &str[i], 1);
		i++;
	}
}

int	ft_putstr_c(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		write (1, &str[i], 1);
		i++;
		c++;
	}
	return (c);
}

int	ft_putstr_c_p(char *str, int psize)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (str == NULL)
		return (0);
	while ((str[i] != '\0') && (psize > 0))
	{
		write (1, &str[i], 1);
		i++;
		c++;
		psize--;
	}
	return (c);
}
