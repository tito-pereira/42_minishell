/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 00:55:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "../includes/structs.h"
# include "../includes/lexer.h"
# include "../includes/expander.h"
# include "../includes/parser.h"
# include "../includes/executer.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>

# define ERROR 1
# define SUCCESS 0
# define TRUE_EXIT 300
# define ARGS_EXIT 400
# define CMD_NOT_FOUND 127
# define IN_FILE 0
# define IN_HD 1
# define OUT_FOWR 2
# define OUT_FAPND 3
# define IO_PIPE 4
# define NO_RED 5
# define INVALID 6

extern int	g_signo;
// minishell.c
char		*prompt_line(char **envp_copy);
int			minishell(int exit_code, char **envp, char *input, char *line);

// minishell_utils.c
int			check_forwardslash(char *cmd);
void		set_prompt_and_get_input(char **envp, char **input, char **line);
void		parse_and_execute(t_mshell *init, char ***envp_copy, \
				int *exit_code);
void		free_and_clear(char **envp);
int			check_whitespace(char *input);

// structs_init.c
void		env_table_init(t_env *env_table);
t_mshell	*mshell_init(t_mshell *init, char *input, char **envp);

// env_main.c
char		**envp_dup(char **envp, int i);
char		**update_envp_copy(t_mshell *init, char ***env_copy, int i, \
				t_env *node);
void		env_node_push_back(t_env *begin_list, char **temp);
t_env		*create_env_node(char **temp);
int			*create_env_list(t_mshell *init, char **envp_copy);

// error.c
int			file_error(char *file_name);
int			redirs_error(t_mshell *init, t_parser *parser_node, int *exit_code);
int			args_error(void);
int			fd_error(int fd);
int			pipe_error(int pid);
int			fork_error(int fd);
int			malloc_error(void *input);
int			quotes_error(void);
void		safe_close(int fd);

// free_mem.c
void		free_expander(t_expand *expander);
void		free_parser(t_parser *parser);
void		free_env(t_env *env);
void		free_lexer(t_lexer *lexer);
void		delete_lists(t_mshell *init);

// builtins
char		*get_oldpwd(t_mshell *init);
void		pwd(t_mshell *init, t_parser *parser);
void		cd(t_mshell *init, t_parser *parser, int *exit_code, \
				char ***envp_copy);
void		env(t_mshell *init, t_parser *par_node);
void		echo(t_mshell *init, t_parser *parser, t_lexer *lex_nd, int i);
void		export(t_mshell *init, char ***envp_copy, int *exit_code);
void		unset(t_mshell *init, char ***envp_copy);
int			check_numeric(char **exit_in, int i);
int			check_exit_args(char **exit_in, int *exit_code, int i, int sign);
int			exit_arguments(char *input, int exit_code, char **exit_in);
int			process_exit(char *input, int *exit_code);

// new_var_set.c
int			new_var_checker(t_mshell *init, char ***envp_copy);
void		free_hd_vars(char **redirs, char *input, int pipe_fd);

// export_utils_1.c
t_env		*assign_val(t_env **count, int *flag, t_mshell *init);
void		save_in_stash(t_env *node, t_env *stash);
int			check_stash(t_env *node, t_env *stash);
void		sort_list(t_env **prnt, t_env *env_node, t_mshell *init, \
				t_env *stash);
void		check_oldpwd(t_env *prnt, int *flag);

// export_utils_2.c
void		get_content(char **export_split, t_env *env_node);

// signals.c
void		sigpipe_handler(int signo);
void		sigint_hdhandler(int signo);
void		sigint_handler(int sig);
void		sighandler_fork(int signo);
void		set_signals(void);

// print_utils.c
void		print_parser(t_mshell *init);
void		print_lexer(t_mshell *init);
void		print_env(t_mshell *init);

#endif
