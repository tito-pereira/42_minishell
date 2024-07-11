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

static int	is_valid_number(char *str, int *sig)
{
	int	i;

	i = 0;
	if (ft_isdigit (str[i]) || str[0] == '+' || str[0] == '-')
	{
		i++;
		if (str[0] == '-')
			*sig *= -1;
	}
	while (str && str[i])
	{
		if (!(ft_isdigit (str[i])))
			return (0);
		i++;
	}
	if ((*sig == 1 && ft_atol(str) > LLONG_MAX)
		|| (*sig == -1 && ft_atol(str) > ((unsigned long long)(LLONG_MAX) + 1)))
		return (0);
	return (1);
}

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
	if (((!cmd[1]) || (!cmd[2] && is_only_zeros(cmd[1]) == 1))
		&& execl->cmd_nmb == 1)
	{
		free_exec(execl, 2);
		exit(0);
	}
	if (!cmd[2] && is_valid_number(cmd[1], &sign) == 1 && execl->cmd_nmb == 1)
	{
		code = ft_atol(cmd[1]);
		code = ((code * sign) % 256 + 256) % 256;
		free_exec(execl, 2);
		ft_printf("minishell: exited with error code: %d\n", code);
		exit(code);
	}
	ft_printf("minishell: exit: %s: Numeric argument required\n", cmd[1]);
}

/*
if (*execl && (*execl)->cmd_nmb == 1
	&& ft_strncmp((*execl)->chunk[0]->cmd_n_args[0], "exit", 10) == 0)
	ft_exit((*execl)->chunk[0]->cmd_n_args, *execl);

ou seja, é para fazer a verificacao dos argumentos na mesma
mas sem mudar o exit_stt
e sem sair da shell

minishell:~/jose$ exit 234 | echo stuff
exit
minishell: exit: too many arguments
minishell:~/jose$ echo $?
1
vs
root_tito@tabp:~$ exit 234 | echo stuff
stuff
root_tito@tabp:~$ echo $?
0

minishell:~/jose$ exit adc | echo stuff
exit
minishell: exit: adc: numeric argument required
root_tito@tabp:~/jose$ echo $?
2
vs
root_tito@tabp:~$ exit adc | echo stuff
stuff
bash: exit: adc: numeric argument required
root_tito@tabp:~$ echo $?
0

echo one| echo two | exit abc | echo stufftwo
bash: exit: abc: numeric argument required
stufftwo (exit stt 0)

echo two | exit abc | exit def | echo stufftwo
bash: exit: abc: numeric argument required
bash: exit: def: numeric argument required
stufftwo (exit stt 0)

eu executo primeiro os echos e só depois venho ao exit
mas tem que ser agora nao vou mudar
(o proprio bash as vezes varia a ordem é tranquilo)

*/