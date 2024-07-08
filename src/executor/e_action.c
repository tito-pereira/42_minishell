/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_action.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:10 by tibarbos          #+#    #+#             */
/*   Updated: 2024/06/29 02:51:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    write_heredoc(t_execlist *execl, char *str, int **fd, int i, int *nfd)
{
    int pid;

	pid = fork();
    if (pid == 0)
    {
		close_pipes(execl, fd, i, 1, 0);
		close(nfd[0]);
		write(nfd[1], str, ft_strlen(str));
		close(nfd[1]);
		exit(0);
	}
    wait(0);
}

void	write_infile(t_execlist *execl, char *str, int **fd, int i, int *nfd)
{
	int 	pid;
	int		infile;
	char	*shovel;

	pid = fork();
    if (pid == 0)
    {
		close_pipes(execl, fd, i, 1, 0);
		close(nfd[0]);
		infile = open(str, O_RDONLY); //possivel erro de nao haver file
		shovel = get_next_line(infile);
		while (shovel != NULL)
		{
			write(nfd[1], shovel, ft_strlen(shovel)); //talvez seja preciso '\n' depois
			free(shovel);
			shovel = get_next_line(infile);
		}
		close(infile);
		close(nfd[1]);
		exit(0);
	}
    wait(0);
}

/*
espera ai.. eu escrevo para o meu proprio pipe certo?
what if, eu ja tiver escrito para esse mesmo pipe do comando anterior, e
estiver agora a escrever por cima?
o que posso fazer é garantir no exec tipo, if [i + 1]infiles, entao simplesmente
nao escrevas
ou tenho que criar um NOVO pipe
*/

void	exec_input(t_execlist *execl, int **fd, int i)
{
	int	n_file;
	int	*nfd;

	n_file = execl->chunk[i]->nmb_inf;
	nfd = (int *)ft_calloc(2, sizeof(int));
	pipe(nfd);
    close_pipes(execl, fd, i, 0, 1);
	if (execl->chunk[i]->infiles && execl->chunk[i]->here_dcs[n_file] == 1 ) //heredoc
	{
        write_heredoc(execl, execl->chunk[i]->infiles[n_file], fd, i, nfd);
		//dup2(fd[i][0], STDIN_FILENO);
		dup2(nfd[0], STDIN_FILENO);
	}
    else if (execl->chunk[i]->infiles && execl->chunk[i]->here_dcs[n_file] == 0) //infile
    {
		//printf("infile redir [%d]\n", i);
		write_infile(execl, execl->chunk[i]->infiles[n_file], fd, i, nfd);
		//dup2(fd[i][0], STDIN_FILENO);
		dup2(nfd[0], STDIN_FILENO);
    }
	else if (!execl->chunk[i]->infiles && i > 0) //inpipe
        dup2(fd[i][0], STDIN_FILENO);
    close(nfd[0]);
	close(nfd[1]);
	free(nfd);
	close(fd[i][1]);
	close(fd[i][0]);
}

/*
ou seja, só tenho 4 tipos de input
- input redirection
	- infile
	- heredoc
- no input redirection
	- pipe
	- no pipe (first || only cmd)
*/

void	ex_redir_file(t_execlist *execl, int i)
{
	int	tmp;
	int	n_file;

	tmp = 0;
	n_file = execl->chunk[i]->nmb_outf;
	if (execl->chunk[i]->app_dcs[n_file] == 1) //append
		tmp = open(execl->chunk[i]->outfiles[n_file], \
		O_RDWR | O_CREAT | O_APPEND, 0644);
	else // truncate
		tmp = open(execl->chunk[i]->outfiles[n_file], \
		O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(tmp, STDOUT_FILENO);
	close(tmp); //depois de dup, fecha-se
	//execve(exec_str[i][0], exec_str[i], *(execl->my_envp));
}

void	exec_output(t_execlist *execl, int **fd, int i)
{
	//int		tmp;

	//ft_printf("preparing output for exec[%d]\n", i);
	if ((i + 1) < execl->valid_cmds) //fechar ultimo pipe
		close(fd[i + 1][0]);
	if (execl->chunk[i]->outfiles != NULL) //1, outfile (append + trunc)
	{
		ex_redir_file(execl, i);
		return ; //ou resolvo assim simplesmente e vai direto para o exec
	}
	else if ((i + 1) < execl->valid_cmds && execl->chunk[i]->outfiles == NULL) //2, outpipe
		dup2(fd[i + 1][1], STDOUT_FILENO);
	if ((i + 1) < execl->valid_cmds)
		close(fd[i + 1][1]); //acho que é tranquilo tanto outfile como outpipe entrarem aqui
}

/*
sera que o outfile deve entrar na mesma no if final para fechar o last pipe?

testing:
tenho TODOS os inputs e outputs sem falha
<		,x	, cat <example
<		,v	, X //echo <ex
<<		,x	, cat <<lim
<<		,v	, X //echo <<lim >f1
>		,x	, ls >f1
>		,v	, pwd >f1
>>		,x 	, ls >>f1
>>		,v 	, pwd >>f1
<>		,x	, cat <ex>f1
<>+		,x	, cat <ex>f1>f2>f3
<>+>>	,x	, cat <ex>f1>f2>>f3
wc -l
ls | wc -l
ls | wc -l | cat
ls | wc -l>out
ls | wc -l>>out
pwd >f1
pwd >f1|ls
pwd >f1|ls|wc -l
pwd >f1|ls|wc -l|ls
pwd >f1|pwd >f2|pwd >f3|pwd >f4|pwd >f5
pwd >f1 | ls >f2 | cat >f3
pwd >>f1 | ls >>f2 | cat >>f3
cat -e | cat -e | ls
cat -e <example.txt>f1
cat <example | cat -e> out
cat <<lim | cat -e>> out
cat <<lim | cat -e | cat -e | cat -e >outt
cat <<lim | cat -e | cat -e | cat -e >>outt
cat <ex>f1 | cat -e>f2 | cat -e>f3
cat <<lim>f1 | cat -e>f2 | cat -e>f3
cat <<lim>f1 | ls >f2 | pwd >f3
cat <<lim>>f1 | ls >>f2 | pwd >>f3
cat -e<ex>f1 | cat -e<ex>f2 | cat -e<ex>f3
cat -e<ex>>f1 | cat -e<ex>>f2 | cat -e<ex>>f3
cat -e<<lim>>f1 | cat -e<<lim>>f2 | cat -e<<lim>>f3
cat <ex>f1|pwd >f2|pwd >f3|cat <ex>f4|pwd >f5
cat <ex>f1|ls >f2|ls >f3|cat <ex>f4|ls >f5
cat -e <<lim>f1 |cat -e<ex>f2 | cat >f3
cat <<lim>f1 | pwd >f2 |cat -e <ex>f3

se calhar algum plano mais detalhado? para atacar partes especificas do codigo?
idk
*/

/*
outfile
	- append
	- trunc
X outfile
	- outpipe
	- terminal
*/

/*
[i]:
(casos [i] sao tratados no input)
[i + 1]:
(caso sejam first || last commands, nem sequer fecham os [i + 1])
(else, fecham o primeiro logo no inicio e o segundo no fim, c
ou sem dup2, acho q ta a resultar)

resolver agora os open && closes dos related pipes
(sobretudo de input)
*/

/*
void    write_heredoc(t_execlist *execl, char *str, int **fd, int i)
{
    int pid;

	//ft_printf("writing heredoc.\n");
	pid = fork();
    if (pid == 0)
    {
		if ((i + 1) < execl->valid_cmds)
		{
			close(fd[i + 1][0]);
			close(fd[i + 1][1]);
		}
		close(fd[i][0]);
		//ft_printf("will write '%s' into pipe, with %d len\n", str, ft_strlen(str));
		//ft_printf("will write into fd[%d][1]=%d;\n", i, fd[i][1]);
		write(fd[i][1], str, ft_strlen(str));
		//ft_printf("%d bytes were written\n", ret);
		//close_pipes(execl, fd, i, 1, 0);
		close(fd[i][1]);
		exit(0);
	}
    wait(0);
}


void	write_infile(t_execlist *execl, char *str, int **fd, int i)
{
	int 	pid;
	int		infile;
	char	*shovel;

	pid = fork();
    if (pid == 0)
    {
		if ((i + 1) < execl->valid_cmds)
		{
			close(fd[i + 1][0]);
			close(fd[i + 1][1]);
		}
		close(fd[i][0]);
		infile = open(str, O_RDONLY); //possivel erro de nao haver file
		shovel = get_next_line(infile);
		while (shovel != NULL)
		{
			write(fd[i][1], shovel, ft_strlen(shovel)); //talvez seja preciso '\n' depois
			free(shovel);
			shovel = get_next_line(infile);
		}
		close(infile);
		close(fd[i][1]);
		exit(0);
	}
    wait(0);
}

void	exec_input(t_execlist *execl, int **fd, int i)
{
	int	n_file;

	n_file = execl->chunk[i]->nmb_inf;
	//ft_printf("preparing input for exec[%d]\n", i);
    close_pipes(execl, fd, i, 0, 1);
	//ft_printf("In input, closed(fd[%d][1] = %d)\n", i, fd[i][1]);
	if (execl->chunk[i]->inpipe == 1
		&& execl->chunk[i]->here_dcs && execl->chunk[i]->here_dcs[n_file] == 1 ) //inpipe + heredocs
	{
		//ft_printf("heredoc input [%d]\n", i);
        write_heredoc(execl, execl->chunk[i]->infiles[n_file], fd, i);
		//ft_printf("will read from fd[%d][0]=%d;\n", i, fd[i][0]);
		dup2(fd[i][0], STDIN_FILENO);
	}
	//close(fd[i][1]); //fecha o pipe local (so escreve no proximo)
    if (execl->chunk[i]->inpipe == 1
		&& ((execl->chunk[i]->here_dcs && execl->chunk[i]->here_dcs[n_file] == 0)
		|| (execl->chunk[i]->here_dcs == NULL))
		&& execl->chunk[i]->infiles != NULL) //inpipe + !heredocs + infiles
    {
		//ft_printf("infile input [%d]\n", i);
		write_inpipe(execl, execl->chunk[i]->infiles[n_file], fd, i);
		dup2(fd[i][0], STDIN_FILENO);
    }
	close(fd[i][1]); 
	if (i > 0) //resto, ate ao ultimo
	{
		//ft_printf("pipeline input [%d]\n", i);
        dup2(fd[i][0], STDIN_FILENO); //last pipe, fd[i - 1][0];
		//ft_printf("dup2(fd[%d][0] = %d, STDIN_FILENO = %d);\n", i, fd[i][0], STDIN_FILENO);
	}
	if (execl->chunk[i]->outfiles == NULL)
	{
		//printf("closing inpipe in [%d]\n", i);
    	close(fd[i][0]);
	}
	//porque ainda vou precisar desta ponta do pipe para ler redir
}
*/