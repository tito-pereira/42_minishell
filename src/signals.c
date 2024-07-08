/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:05:50 by marvin            #+#    #+#             */
/*   Updated: 2024/04/04 19:05:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_global(int num)
{
	if (num == SIGINT || num == SIGQUIT)
	{
		//printf("inside SIGINT only changes global handler function\n");
		g_sig = 128 + num;
	}
}

void	sig_hd_repeat(int num)
{
	if (num == SIGINT)
	{
		//printf("inside SIGINT exits heredoc handler function\n");
		g_sig = 128 + SIGINT;
		write(1, "\n", 1);
		exit(g_sig);
	}
}

/*
nao vai fucionar no meu porque eu nao faço heredoc em nenhum fork

empty heredoc + ctrl-C -> escape, new prompt
full heredoc + ctrl-C -> escape, new prompt
*/

void	sig_repeat(int num)
{
	if (num == SIGINT)
	{
		g_sig = 128 + SIGINT;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handlerr(int mode)
{
	struct	sigaction	sa_repeat;
	struct	sigaction	sa_hd_repeat;
	struct	sigaction	sa_global;
	struct	sigaction	sa_ign;
	struct	sigaction	sa_dfl;

	sa_repeat.sa_handler = &sig_repeat;
	sigemptyset(&sa_repeat.sa_mask);
	sa_repeat.sa_flags = 0;
	sa_hd_repeat.sa_handler = &sig_hd_repeat;
	sigemptyset(&sa_hd_repeat.sa_mask);
	sa_hd_repeat.sa_flags = 0;
	sa_global.sa_handler = &sig_global;
	sigemptyset(&sa_global.sa_mask);
	sa_global.sa_flags = 0;
	sa_ign.sa_handler = SIG_IGN;
	sigemptyset(&sa_ign.sa_mask);
	sa_ign.sa_flags = 0;
	sa_dfl.sa_handler = SIG_DFL;
	sigemptyset(&sa_dfl.sa_mask);
	sa_dfl.sa_flags = 0;
	//sa_dfl.sa_handler = SIG_DFL;
	if (mode == 1) //prompt
	{
		sigaction(SIGINT, &sa_repeat, NULL);
		sigaction(SIGQUIT, &sa_ign, NULL);
	}
	else if (mode == 2) //heredoc ???
	{
		//printf("SIGINT exits heredoc activated\n");
		sigaction(SIGINT, &sa_hd_repeat, NULL);
		sigaction(SIGQUIT, &sa_ign, NULL); //ja foi definida antes, n posso tirar isto?
	}
	else if (mode == 3) //pre executor ???
	{
		//printf("SIGINT only changes global activated\n");
		sigaction(SIGINT, &sa_global, NULL);
		sigaction(SIGQUIT, &sa_global, NULL);
	}
	else if (mode == 4) //DFL ???
	{
		printf("SIG_DFL activated\n");
		sigaction(SIGINT, &sa_dfl, NULL);
		sigaction(SIGQUIT, &sa_dfl, NULL);
	}
	else if (mode == 5) //IGN ???
	{
		printf("SIG_IGN activated\n");
		sigaction(SIGINT, &sa_ign, NULL);
		sigaction(SIGQUIT, &sa_ign, NULL);
	}
}

/*
sig_handler(1) - main.c
sig_handler(2) - p_2c.c
sig_handler(3) - e_main.c

() empty prompt
() full prompt
() empty / one line + empty heredoc
() full / one line + full heredoc
() empty blocking command
() full blocking command

(vanilla, SIGINT)
.(V) ctrl C, empty prompt, repeat (vanilla: )
.(V) ctrl C, some lines, repeat (vanilla: )
.(X) ctrl C, heredoc, repeat (vanilla: )
.(V) ctrl C, blocking commands, (repeat?)
◦ ctrl-C displays a new prompt on a new line.
(new, repeat)

(vanilla, EOF)
.(V) ctrl D, empty prompt, quit (vanilla: NULL input && repeat)
.(V) ctrl D, full prompt, nothing (vanilla: nothing)
.(X) ctrl D, heredoc, repeat (vanilla: )
.(-) ctrl D, blocking commands, (quit/nothing) (vanilla: NULL input && repeat)
◦ ctrl-D exits the shell.
(new, SIGINT)

(vanilla, SIGQUIT)
.(V) ctrl \, empty prompt, ignore
.(V) ctrl \, full prompt, ignore
.(V) ctrl \, heredoc, ignore
.(V) ctrl \, blocking commands, nothing
◦ ctrl-\ does nothing.
(new, SIG_IGN)

-----
BASH (heredoc):
root_tito@tabp:~$ cat <<lim (ctrl-C)
> ^C
root_tito@tabp:~$ cat <<lim
> stuff^C
root_tito@tabp:~$ cat <<lim
> stuff
> l^C
root_tito@tabp:~$ cat <<lim (ctrl-D)
>
-bash: warning: here-document at line 23 delimited by end-of-file (wanted `lim')
root_tito@tabp:~$ cat <<lim
> stuff
> lim
stuff
root_tito@tabp:~$ echo <<lim (ctrl-\ is ignored)

ZÉ (heredoc):
minishell:~/jose$ echo <<lim
> ^C
minishell:~/jose$ echo <<lim
>
minishell: warning: here-document delimited by end-of-file (wanted `lim')

minishell:~/jose$ echo <<lim
>

(o do zé está igualzinho wtf)

TITO (heredoc):
>> minishell: echo <<lim (ctrl-C)
>> minishell: echo <<lim (ctrl-D) (return NULL)
heredoc>
-----

teste triplo ecra:
- empty prompt
- full prompt
- empty heredoc
- full heredoc
- blocking command

- nao acho que o sigpipe seja necessário, apenas acrescenta uma mensagem extra

usos da global var:
-> mal entra no lexer main, se o global for 130, a mesma historia,
exit code 130, baza
(lexer vem antes do parser e exec por isso deve ser mesmo a seguir ao prompt
de input)
-> durante o heredoc, o parent process espera pelo filho
logo a seguir, verifica se o global é 130, caso seja, exit code = 130
e retorno -1

-> sig_handler_fork
ambos SIGINT e SIGQUIT levam ign e apenas mudam a global

-> (executer_utils_1.c)
signal(SIGINT, sigint_hdhandler);
signal(SIGQUIT, SIG_IGN);
cada vez que ele recebe heredoc input é num fork novo por isso que ele
repete as sighandlers em todos os forks (sera que o parent process tambem realiza
sighandling neste caso?)

if (!input)
{
	printf("minishell: warning: here-document delimited by end-of-file \
(wanted `%s')\n", init->eof);
	close(pipe_fd[1]);
	delete_lists(init);
	exit(EXIT_FAILURE);
}
*/

/*
--------------------------------------------------
void	sigpipe_handler(int signo)
{
	(void)signo;
	printf("Received SIGPIPE signal. Pipe closed by child process.\n");
	exit(EXIT_FAILURE);
}

void	sigint_hdhandler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		write(1, "\n", 1);
		exit(g_signo);
	}
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sighandler_fork(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
		g_signo = 128 + signo;
}

void	set_signals(void)
{
	g_signo = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
*/