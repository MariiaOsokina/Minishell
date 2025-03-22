#pragma once

#include "minishell.h"

/*validation.c*/
bool	check_pipes(char *str);
bool	check_quotes(char *str);
bool	check_redirections(char *str);
bool	input_validation(t_shell *shell);

/*input_utils.c*/
bool	is_space(char c);
bool	check_line_len(char *line);
bool	check_parenthesis(char *str);

/*validation_utils.c*/
bool	is_quote(char c);
int		is_redirect(char *c);
int		jump_quotation(char *str, int i);
bool	handle_redir_error(char *str, int *i, int redir_len);
void	toggle_quotes(char c, bool *in_single_quote, bool *in_double_quote);