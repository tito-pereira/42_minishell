/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/05 15:15:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "../includes/minishell.h"
# include <dirent.h>

// executer_main.c
void	get_exit_code(int status, int *exit_code);
void	executer_fork_router(t_mshell *init, char ***env, int *exit_code, \
			int i);
void	executer_main(t_mshell *init, char ***envp_copy, int *exit_code);

// executer_utils_1.c
void	write_here_doc(t_mshell *init, char *eof, int *pipe_fd, int *exit_code);
int		process_here_doc(t_mshell *init, char *eof, int *exit_code, int export);
void	get_pipes(t_mshell *init);
void	exec_executable(t_mshell *init, t_parser *parser_node, char ***envp);
void	executer_cmd_router(t_mshell *init, t_parser *parser_node, \
			char ***strings_env, int *exit_code);

// executer_utils_2.c
void	free_all_exit_code(t_mshell *init, char ***envp, int *exit_code);
void	free_all(t_mshell *init, char ***envp);
void	free_hd_vars(char **redirs, char *input, int pipe_fd);
void	pre_env_exec(t_mshell *init, t_parser *parser_node, char ***envp);
void	free_exec_helper(t_mshell *init, t_parser *parser_node, char ***envp, \
			char *file_err);

// executer_utils_3.c
void	safe_closedir(DIR *dir);
void	safe_closedir_fd(DIR *dir, int fd);

// executer_single_cmd.c
int		single_cmd_isdir(char *cmd);
int		single_cmd_notfound(t_mshell *init, int file_fd, DIR *dir);
void	fork_single_cmd(t_mshell *init, t_parser *parser_node, \
			char ***strings_env, int *exit_code);
void	process_single_cmd(t_mshell *init, char ***strings_env, int *exit_code);
void	single_redirs_router(t_mshell *init, t_parser *node, int *exit_code, \
			int i);

// executer_multi_cmds.c
int		multi_cmd_isdir(t_mshell *init, char *cmd);
int		multi_cmd_notfound(t_mshell *init, t_parser *parser_node, int file_fd, \
			DIR *dir);
void	process_pipes(t_mshell *init);
void	process_child(t_mshell *init, t_parser *parser_node, \
									char ***strings_env, int *exit_code);
void	process_parent(t_mshell *init, int *exit_code);

// executer_multi_redirs.c
void	multi_check_input(t_mshell *init, t_parser *node, int i);
void	multi_check_output(t_mshell *init, t_parser *node, int i);
void	multi_redir_input(t_mshell *init, t_parser *node, int *exit_code);
void	multi_redir_output(t_mshell *init, t_parser *node);
void	multi_redirs_router(t_mshell *init, t_parser *node, int *exit_code);

// executer_multi_utils.c
void	exit_err_multi_cmds(t_mshell *init, t_parser *parser_node, \
			int *exit_code, char ***envp);
void	close_parent_pipes(t_mshell *init);
void	close_redirs_pipes(t_mshell *init, t_parser *node);
void	close_child_pipes(t_mshell *init);
void	close_pipes(t_mshell *init, int i, int j);

// executer_redirs_utils.c
int		check_red_error(char *redir_syntax);
int		process_file(t_mshell *init, char *file_name, int file_type);

// executer_heredoc_expander.c
void	heredoc_expander(t_mshell *init, char **input, int *exit_code);

#endif
