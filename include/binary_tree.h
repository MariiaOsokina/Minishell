/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:39:36 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 14:39:37 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "structs.h"
#include <stdio.h>

/*Types of command nodes*/
typedef enum e_node_type
{
	N_PIPE,
	N_EXEC,
	N_ANDIF,
	N_OR,
	N_SUBSHELL,
}				t_node_type;

typedef struct s_node
{
	t_node_type	type;
}				t_node;

typedef enum e_io_type
{
	INF,
	HERE,
	APP,
	ADD,
}				t_io_type;

typedef struct s_in_out
{
	t_io_type	type;
	char		*name;
	char		*eof;
}				t_in_out;

/*EXEC*/
typedef struct s_exec
{
	t_node		type;
	char		*command;
	char		**av;
	t_list		*i_ofiles;
}				t_exec;

/*PIPES*/
typedef struct s_pipe
{
	t_node		type;
	t_exec		*left;
	t_exec		*right;
}				t_pipe;

typedef struct s_op
{
	t_node		type;
	t_exec		*left;
	t_exec		*right;
}				t_op;

/*New AST functions*/
int				get_av_len(char **av);
void			populate_args(t_list **curr, char **args, int i);
void			copy_and_populate(char **av, t_list **curr, char **args);
void			repopulate_args(t_shell *shell, t_list **curr, t_exec *node);
void			print_i_ofiles(t_list *in_ofiles, int space);
void			free_ast_node(void *node);
int				is_operator(t_list *token);
char			**collect_args(char **argv, t_list **curr);
t_list			*next_token(t_list **current);
int				is_redirection(t_list *token);
void			past_parenthesis(t_list **curr);
void			*parse_factor(t_shell *shell, t_list **curr, bool in_subshell);
void			*parse_term(t_shell *shell, t_list **curr, bool in_subshell);
void			*build_ast(t_shell *shell);
void			*create_exec_node(t_shell *shell, t_list **curr);
void			*parse_expression(t_shell *shell, t_list **curr,
					bool in_subshell);
void			collect_io(t_shell *shell, t_list **curr, t_list **i_ofiles);

/*bst_free.c*/
void			free_bst(void *root);
void			free_exec(t_exec *node);
void			free_sub_pipes(t_pipe *pipe);

/*bst_print.c*/
void			print_exec(char **av, int space);
void			*print_bst(void *root, int space);
void			print_sub_pipe(t_pipe *pipe, int space);
void			print_bst_pipe(t_pipe *node, int space);
void			print_bst_exec(t_exec *node, int space);
