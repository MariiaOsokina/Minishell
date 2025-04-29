#pragma once

#include "structs.h"

typedef enum s_token_type
{
	WORD,
	PIPE,
	APPEND,
	OUTFILE,
	INFILE,
	HEREDOC,
	AND_IF,
	OR,
	PARENTHESIS
}					t_token_type;

typedef enum s_token_state
{
	GENERAL,
	IN_DQUOTES,
	IN_SQUOTES,
	EXPAND,
}					t_token_state;

typedef struct s_token
{
	int				pos;
	char			*value;
	t_token_type	type;
	t_token_state	state;
}					t_token;

/*create_token_lst.c*/
void				tokenize_input(t_shell *shell, char *input);
int					handle_pipe(t_shell *shell, char *input, int i);
int					handle_word_token(t_shell *shell, char *input, int i);
int					handle_redirection(t_shell *shell, char *input, int i);
int					set_hered(t_shell *sh, t_token *nw_tkn, char *input, int i);

/*expand_utils.c*/
bool				is_meta(char *str, int i);
bool				is_expandable(char *token);
bool				in_quotes(char *input, int i);
int					set_append(t_shell *sh, t_token *nw_tkn, char *input,
						int i);
int					set_simple(t_shell *sh, t_token *nw_tkn, char *input,
						int i);

/*handle_parenthesis.c*/
bool				validate_subs(char *subs);
int					handle_parenthesis(t_shell *shell, char *input, int i);
int					handle_closing(t_shell *shell, char *input, int i,
						bool valid);
int					handle_opening(t_shell *shell, char *input, int i,
						bool valid);

/*tokenization_utils.c*/
int					ft_flag(char c, int *i, bool flag);
char				*ft_strjoin_char(char *str, char c);
t_token				*create_token(t_shell *shell, char *str);
int					check_escapes(char *input, int start, int i, char quote);
int					join_strs(t_shell *shell, char **str, char *input, int i);

/*lexer.c*/
t_token_type		token_type(char *value);
void				del_token(void *token_node);
void				set_token_position(t_list *lst);
int					check_balance(char *input, int i);
bool				lexer(t_shell *shell, char *input);
bool				check_paren_types(t_shell *shell);

/*handlers.c*/
int					handle_or(t_shell *shell, char *input, int i);
int					handle_andif(t_shell *shell, char *input, int i);
int					handle_quotes(t_shell *shell, char *input, int i);
int					hndl_nonquoted_str(t_shell *shell, char **str, char *input,
						int i);
int					hndl_quoted_str(t_shell *shell, char **str, char *input,
						int i);
