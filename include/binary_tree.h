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
	N_HEREDOC,
	N_INF,
	N_OUTF,
	N_APPEND
}					t_node_type;

typedef struct s_node
{
	t_node_type		type;
}					t_node;

typedef enum e_inf_t
{
	INF,
	HERE,
}					t_inf_t;

typedef enum e_outf_t
{
	APP,
	ADD,
}					t_outf_t;

typedef struct s_inf
{
	t_inf_t			type;
	char			*name;
	char			*eof;
}					t_inf;

typedef struct s_outf
{
	t_outf_t		type;
	char			*name;
}					t_outf;

/*EXEC*/
typedef struct s_exec
{
	t_node			type;
	char			*command;
	char			**av;
	t_list			*infiles;
	t_list			*outfiles;
}					t_exec;

/*PIPES*/
typedef struct s_pipe
{
	t_node			type;
	t_exec			*left;
	t_exec			*right;
}					t_pipe;

/*New AST Type*/

typedef struct s_ast
{
	t_node_type		type;
	char			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*function headers*/
t_ast				*build_ast(t_shell *shell);
t_list				*next_token(t_list **current);
void				print_ast(t_ast *root, int level);
t_ast				*parse_term(t_list **curr, t_shell *shell);
t_ast				*parse_factor(t_list **curr, t_shell *shell);
t_ast				*parse_expression(t_list **curr, t_shell *shell);
void				print_top_bottom_ast(t_ast *node, int level);

/*buildtree.c*/
t_list				*get_name(t_list *tkn_lst);
void				*build_tree(t_shell *shell, t_list *token_lst);
void				*create_exec(t_shell *shell, t_list *token_lst);
void				*create_pipe(t_shell *shell, void *left, void *right);
void				*insert_node(t_shell *shell, void *node, t_list *token_lst);

/*buildtree_utils.c*/
int					count_args(t_list *tkn_lst);
char				**get_colors(t_shell *shell, char **av);
char				**get_argv(t_shell *shell, t_list *t_lst);
t_list				*get_infiles(t_shell *shell, t_list *tkn_lst,
						t_list **infs);
t_list				*get_outfiles(t_shell *shell, t_list *tkn_lst,
						t_list **outfs);

/*bst_free.c*/
void				free_bst(void *root);
void				free_exec(t_exec *node);
void				free_sub_pipes(t_pipe *pipe);

/*builtree_helpers.c*/
t_list				*skip_if(t_list *tmp);
t_list				*skip_else(t_list *tmp);
t_list				*check_w_args(t_list *tkn_lst, int *args);
t_list				*check_word(t_list **cur, char **av, int *i);

/*bst_print.c*/
void				print_exec(char **av, int space);
void				*print_bst(void *root, int space);
void				print_sub_pipe(t_pipe *pipe, int space);
void				print_bst_pipe(t_pipe *node, int space);
void				print_bst_exec(t_exec *node, int space);

/*bst_print_utils*/
void				print_infiles(t_list *infiles, int space);
void				print_outfiles(t_list *outfiles, int space);
