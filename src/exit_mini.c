/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:45:13 by marvin            #+#    #+#             */
/*   Updated: 2024/06/27 01:45:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_number(char *str, int *sign)
{
	int					i;

	i = 0;
	if (ft_isdigit (str[i]) || str[0] == '+' || str[0] == '-')
	{
		i++;
		if (str[0] == '-')
			*sign *= -1;
	}
	while (str && str[i])
	{
		if (!(ft_isdigit (str[i])))// || str[i] == '+' || str[i] == '-'))
			return (0);
		i++;
	}
	//ret = ft_atol(str);
	if ((*sign == 1 && ft_atol(str) > LLONG_MAX)
		|| (*sign == -1 && ft_atol(str) > ((unsigned long long)(LLONG_MAX) + 1)))
		return (0);
	return (1);
}

/*
ft_atoll(exit_in[1]) > LLONG_MAX) ||
(sign == -1 && ft_atoll(exit_in[1]) > (unsigned long long)(LLONG_MAX) + 1)))

*sign == -1 && ft_atol(str) > 0
*/

static int	is_only_zeros(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] != '0')
			return (0);
	}
	return (1);
}

void	ft_exit(char **cmd, t_execlist *execl)
{
	unsigned long long	code;
	int					sign;
	
	sign = 1;
	if ((!cmd[1] && execl) || (!cmd[2] && is_only_zeros(cmd[1]) == 1 && execl))
	{
		free_exec(execl, 2);
		exit(0);
	}
	if (!cmd[2] && is_valid_number(cmd[1], &sign) == 1 && execl) //1 arg numero valido
	{
		code = ft_atol(cmd[1]);
		code = ((code * sign) % 256 + 256) % 256;
		free_exec(execl, 2);
		ft_printf("minishell: exited with error code: %d\n", code);
		exit(code);
	}
	ft_printf("minishell: exit: %s: Numeric argument required\n", cmd[1]);
	free_exec(execl, 2);
	exit(2);
}

/*
- exit
	invalid arg, exit_code = 2 (kinda nao preciso)
		digits, +, -
		> LLONG_MAX
		< -LLONG_MAX - 1
	valid arg, calculates exit_code between 0-255
		((int)(ft_atoll(exit_in[1]) * sign) % 256 + 256) % 256

LLONG_MAX: 9223372036854775807 (2^63 - 1)
LLONG_MIN: -9223372036854775808 (-2^63)

exit
exit | ls
ls | exit
ls | exit | ls | exit
exitt
exit 100
exit 100 23450
exit 4635t
exit 0000000000
exit abc
exit --124 (V)
exit -124 (V) (always non negative)
exit 124 (V)
1000 -> 232
-1000 -> 24
300 -> 44
-300 -> 212
50 -> 50
-50 -> 206
LLONG_MAX: 9223372036854775807 (2^63 - 1)
LLONG_MIN: -9223372036854775808 (-2^63)

sign V
long numbers V (good enough)
conversion V

# Test exit code 1000
(bash -c "exit 1000")
echo $?

# Test exit code -1000
(bash -c "exit -1000")
echo $?

if (!cmd[1] && execl) //sem args, válido
{
	free_exec(execl, 2);
	exit(0);
}
if (!cmd[2] && is_only_zeros(cmd[1]) == 1 && execl) //apenas zeros, válido
{
	free_exec(execl, 2);
	exit(0);
}
*/