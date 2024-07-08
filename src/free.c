/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:43:48 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 15:46:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*free_str(char *str)
{
	free(str);
	return (NULL);
}

char	**free_db_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
		free_str(str[i]);
	free(str);
	return (NULL);
}

int	*free_int_arr(int *str)
{
	free(str);
	return (NULL);
}

t_chunk	*free_chunk(t_chunk *chunk)
{
	//char **infiles
	if (chunk->infiles)
		chunk->infiles = free_db_str(chunk->infiles);
	//int *here_dcs
	if (chunk->here_dcs)
		chunk->here_dcs = free_int_arr(chunk->here_dcs);
	//char *here_file
	if (chunk->here_file)
		chunk->here_file = free_str(chunk->here_file);
	//char *delimiter
	if (chunk->delimiter)
		chunk->delimiter = free_str(chunk->delimiter);
	//char **outfiles
	if (chunk->outfiles)
		chunk->outfiles = free_db_str(chunk->outfiles);
	//int *app_dcs
	if (chunk->app_dcs)
		chunk->app_dcs = free_int_arr(chunk->app_dcs);
	//char *og
	if (chunk->og)
		chunk->og = free_str(chunk->og);
	//char **cmd_n_args
	if (chunk->cmd_n_args)
		chunk->cmd_n_args = free_db_str(chunk->cmd_n_args);
	//char *path
	if (chunk->path)
		chunk->path = free_str(chunk->path);
	free(chunk);
	return (NULL);
}

/*
typedef struct s_execlist {
	t_chunk	**chunk;
	int		cmd_nmb;
	int		pipe_nmb;
	char	***my_envp;
	int		valid_cmds;
	int		*pipe_loc;
	int		*exit_stt;
	int		*to_end;
	int		*env_pipe;
}	t_execlist;
*/

t_execlist	*free_exec(t_execlist *execl, int mode)
{
	int	i;

	i = -1;
	if (!execl)
		return (NULL);
	if (execl->chunk)
	{
		while (execl->chunk[++i])
			execl->chunk[i] = free_chunk(execl->chunk[i]);
	}
	if (execl->my_envp && mode == 2)
	{
		*(execl->my_envp) = free_db_str(*(execl->my_envp));
		free(*(execl->my_envp));
		execl->my_envp = NULL;
	}
	//int *pipe_loc
	//printf("free pipe locs\n");
	if (execl->pipe_loc)
		execl->pipe_loc = free_int_arr(execl->pipe_loc);
	//printf("free env pipe\n");
	if (execl->env_pipe)
		execl->env_pipe = free_int_arr(execl->env_pipe);
	//printf("free execl\n");
	free(execl);
	//printf("done frees\n");
	return (NULL);
}

/*
ERROR
(export, cd, unset) + exit
(export, cd, unset) + (export, cd, unset)
(export, cd, unset) simplesmente assim da erro
(provavelmente as my_envp)
ontem estava a dar (acho eu), o que raio mudei

cd && unset sem args
testar ja isto. se estiver bem, nao preciso de mudar nada
-----
export VAR=value | env (nao muda)
export TESTVAR=hello (muda)
env | grep TESTVAR (nao muda)
unset TESTVAR | env (nao muda)
env | grep TESTVAR  
cd <local> | pwd
pwd
export TESTVAR1=foo
export TESTVAR2=bar
export TESTVAR1=newvalue | unset TESTVAR2 | env


- ja retirei o to_end do header e n me deu nenhum erro.. espero n haver esqueletos prai
- para testar o free my_envp, tem que ser modo 2 (exit ou erros)

ENVP:
envp leva malloc de char ** e varios char *
o envp em si (char ***) nao leva malloc nem deve levar free
c jeito o free_db podia levar char *** e dar free ao char ** original
e returnar NULL
env = create_env
while
{
execl.env = env
execl = new_env (pos exec)
//env = execl.env
}

EXIT_STT
X malloc na main (sem maloc, um int local)
malloc geral da struct, não do pointer especifico
vamos simplesmente nao dar free a exit_stt nenhum e no
fim ver se sobram leaks ou nao

ENV PIPE
p_1 = NULL
exec usado ou nao
free aqui
p_1, etc

exit stt
to end (posso apenas tirar)
env pipe
. o que é?
my envp??
. o que é? a minha duplicacao das env vars
(main.c, p_1.c, etc)
testar com ls que nao altera envp
talvez testar aqueles comandos unset e o crl p verificar que funciona?
*/