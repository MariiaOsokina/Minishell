#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "minishell.h"
# include <limits.h>

/*Utils.h:  Shell Utils */
void	free_shell(t_shell *shell);

// /*Utils.h: Signals */
// void	sig_main(int signo);
// void	sig_pipe(int signo); // Might remove, doing nothing.
// void	handle_signals(void);
// void	set_main_signals(void);
// void	set_fork1_signal(void);

// /*Utils.h: Heredoc signal handling functions*/
// void	heredoc_signal(void);
// void	heredoc_sigint_handler(int signo);
// t_shell	*shell_struct(t_shell *shell, int flag);

/*terminal.c & terminal_utils.c*/
void	free_shell(t_shell *shell);
void	shell_input(t_shell *shell);

/* terminal.c  && terminal_utils.c*/
void	reset_shell(t_shell *shell);
bool	is_env_empty(t_shell *shell);
// void	terminal(t_shell *shell, char **envp);
void	terminal(t_shell *shell);

/*Function_file: input_utils.c, validation_utils.c, validation.c, check_vars.c*/
bool	is_space(char c);
bool	is_quote(char c);
int		is_redirect(char *c);
bool	check_pipes(char *str);
bool	check_quotes(char *str);
bool	check_line_len(char *line);
bool	check_parenthesis(char *str);
bool	check_redirections(char *str);
int		jump_quotation(char *str, int i);
int		is_exact_var(t_env *env_var, const char *var_name);
bool	handle_redir_error(char *str, int *i, int redir_len);
void	toggle_quotes(char c, bool *in_single_quote, bool *in_double_quote);

/*printers.c*/
void	print_lst(t_list *lst);
void	print_token_lst(t_list *lst);
void	print_cmd_lst(t_shell *shell);
// void	print_env_arr(t_shell *shell);

#endif
