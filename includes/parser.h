/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/06 00:56:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/minishell.h"

# define BUILTIN_CMD 11
# define SHELL_CMD 12

// parser_main.c
t_parser	*create_parser_node(t_mshell *init, char *cmds, t_parser *node);
void		parser_node_push_back(t_mshell *init, t_parser **begin_list, \
				char *cmds, t_parser *node);
t_parser	*parser_node_router(t_mshell *init, char ***envp_copy, \
				t_parser *parser, char *cmds);
int			check_pipe_syntax(t_mshell *init, t_lexer *lexer);
void		parser_main(t_mshell *init, char ***envp_copy, t_parser *parser, \
				char *cmds);

// parser_main_utils.c
t_parser	**create_parser_node_aux(t_mshell *init, t_parser **node);
void		parser_main_aux1(t_mshell *init, t_lexer **lexer);
void		parser_main_aux2(t_mshell *init, t_lexer **lexer);
void		parser_main_aux3(t_mshell *init);

// parser_cmd.c
int			cmd_router(char *cmd);
char		**parse_path(char **env_path);
char		*get_cmd_path(char **envp_paths, char *cmd, char *tpath, \
				char *newpath);
char		*find_cmd(char *cmd, t_mshell *init, char ***envp_copy, \
				char *not_found);

// parser_utils.c
int			check_redir_syntax(t_mshell *init);
char		*get_redirs(t_mshell *init, char *og_redirs, t_lexer **lexer);
char		*parser_merge_split(char *og_str, char *lexer_str);
void		free_parser_temps(char *cmds, char *redirs, char *cmd_path, \
				char **cmd_full);
void		free_parser_vars(char **cmds, char **redirs);

// structs_init.c
void		parser_init(t_parser *parser);

#endif
