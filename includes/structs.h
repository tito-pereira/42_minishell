/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:44:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/05 15:15:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../includes/minishell.h"
# include <stdbool.h>

typedef struct s_env
{
	char			*var;
	char			*content;
	int				visibility;
	struct s_env	*next;
}	t_env;

typedef struct s_mshell
{
	char				***envp_copy;
	char				*in;
	char				*origin_in;
	bool				set_var;
	char				**tcmd_full;
	char				*tcmd_path;
	char				*tredirs;
	char				*eof;
	char				**redirs;
	char				**paths;
	int					nbr_pipes;
	int					*child_pids;
	int					**pipe_fds;
	int					**closed_pipes;
	int					cmd_index;
	int					og_stdin;
	int					og_stdout;
	int					red_input;
	int					red_output;
	int					parser_flag;
	bool				expand_heredoc;
	bool				stop_exec;
	bool				var_nf;
	struct s_env		*env_table;
	struct s_expand		*exp;
	struct s_lexer		*lexer;
	struct s_parser		*parser;
}	t_mshell;

typedef struct s_lexer
{
	char			*str;
	int				operator;
	int				i;
	int				d_quote_expand;
	int				is_node;
	bool			true_sign;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_expand
{
	int		i;
	int		macro_len;
	int		s_quote;
	int		d_quote;
	char	*new_input;
}	t_expand;

typedef struct s_parser
{
	char			**cmd_exec;
	char			*path_exec;
	char			*redirs;
	bool			file_nf;
	bool			token_err;
	bool			var_nf;
	int				cmd_type;
	int				input_t;
	int				output_t;
	int				input;
	int				output;
	struct s_parser	*next;
}	t_parser;

#endif
