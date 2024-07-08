/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_2c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:24:37 by marvin            #+#    #+#             */
/*   Updated: 2024/06/25 19:24:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*empty_heredoc(int fd)
{
	char	*shovel;
	char	*chest;
	char	*old;

	shovel = get_next_line(fd);
	chest = NULL;
	while (shovel != NULL)
	{
		if (!chest)
			chest = ft_strdup(shovel);
		else
		{
			old = chest;
			chest = ft_strjoin(chest, shovel);
			free(shovel);
			shovel = NULL;
			free(old);
		}
		shovel = get_next_line(fd);
	}
	close(fd);
	return (chest);
}

void	heredoc_chest(char **chest, char **input)
{
	char	*old;

	if (!(*chest))
		*chest = ft_strdup(*input);
	else
	{
		old = *chest;
		*chest = ft_strjoin(*chest, *input);
		free (old);
	}
	old = *chest;
	*chest = ft_strjoin(*chest, "\n");
	free(old);
	free(*input);
}

char	*heredoc_rd(char *lim)
{
	char	*input;
	char	*chest;

	input = NULL;
	chest = NULL;
	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			return (NULL);
		if (ft_strncmp(lim, input, 4096) == 0)
		{
			free(input);
			break ;
		}
		heredoc_chest(&chest, &input);
	}
	return (chest);
}

char    *heredoc_read(char *lim)
{
    int     *fd;
    int     pid;
    char    *input;
    char    *ret;
	//int		test;

    fd = (int *)ft_calloc(2, sizeof(int));
	//printf("inside heredoc read\n");
	sig_handlerr(3); //only change global
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        sig_handlerr(2); //heredoc exit
        input = heredoc_rd(lim);
		//printf("input received is '%s'\n", input);
		if (!input)
		{
			//printf("warning: here-document delimited by end-of-file\n");
			close(fd[1]);
			exit(0); //exit(EXIT_FAILURE);
		}
		write(fd[1], input, ft_strlen(input)); //test =
		//printf("write return was %d\n", test);
		free(input);
        close(fd[1]);
		exit(0);
    }
    close(fd[1]);
    wait(NULL);
    if (g_sig == 130) // ou g_sig == siqguit?
    {
		close(fd[0]);
    	free(fd);
		//printf("\nglobal is actually 130\n");
		return (NULL);
    }
    ret = empty_heredoc(fd[0]);
	//printf("read received is '%s'\n", ret);
    close(fd[0]);
    free(fd);
    return (ret);
}

/*
ctrl C

-----
ctrl D

no ctrl D nem precisas de dar free a nada
so vais controlar, tal e qual como no prompt, um null input, nada mais

else if (input == NULL) //ctrl-D stoppage, SIGINT (ctrl-\ ignores)
	exit(0);

if (!input)
{
	printf("minishell: warning: here-document delimited by end-of-file \
(wanted `%s')\n", init->eof);
	close(pipe_fd[1]);
	delete_lists(init);
	exit(EXIT_FAILURE);
}
-----

ctrl \ é simplesmente ignorar
-----

agora o texto normal em si é que da erros

parece que o numero de comandos que eu ponho em heredoc é o numero de
vezes que tenho que escrever exit ate finalmente sair

o ze nao tinha algo tipo uns random "clear history" ou replace line
ou o crl espalhados algures no codigo? lembro me de ver
procurar isso talvez depois para resolver

-> os exit extra eram afinal o child process que nao estava a fechar,
ficava ali a existir perpetuamente

agora vai faltar é um loop de ler tudo da get_next_line
*/