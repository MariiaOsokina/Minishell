/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:37:17 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 14:37:22 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h" //delete???
# include "minishell.h"
# include <limits.h>

// /*Utils.h:  Shell Utils */
// void	free_shell(t_shell *shell);

/*terminal.c & terminal_utils.c*/
void	free_shell(t_shell *shell);
void	shell_input(t_shell *shell);

/* terminal.c  && terminal_utils.c*/
void	reset_shell(t_shell *shell);
// bool	is_env_empty(t_shell *shell);
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
