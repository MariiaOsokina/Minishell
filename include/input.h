/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:38:28 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 14:38:30 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "minishell.h"

/*validation.c*/
bool	check_pipes(char *str);
bool	check_quotes(char *str);
bool	check_redirections(char *str);
bool	input_validation(t_shell *shell);
bool	check_logical_or(char *str);

/*input_utils.c*/
bool	is_space(char c);
void	balance_message(int balance);
bool	check_line_len(char *line);
bool	check_parenthesis(char *str);
bool	check_empty_parens(char *str);
bool	handle_paren(char c, int *bal);

/*validation_utils.c*/
bool	is_quote(char c);
int		is_redirect(char *c);
int		jump_quotation(char *str, int i);
bool	handle_redir_error(char *str, int *i, int redir_len);
void	toggle_quotes(char c, bool *in_single_quote, bool *in_double_quote);
