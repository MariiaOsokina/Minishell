/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:06:59 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 17:17:08 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "minishell.h"

#define LINE_ERROR "line too long!"
#define CLOSE_ERROR "near unexpected token `)'"
#define OPEN_ERROR "near unexpected token `('"
#define OPEN_QUOTE "`open quote'"
#define PIPE_ERROR "near unexpected token `|'"
#define AND_ERROR "near unexpected token `&'"
#define REDIR_ERROR "near unexpected token `newline'"
#define TOKEN_ERROR "near unexpected token `"
#define SYNTAX_ERROR "minishell: syntax error "

/*exit_messages.c*/
void	exit_failure(t_shell *shell, char *info);
void	print_exit(void);
int		exit_code(t_shell *shell, int value);
bool	syntax_error_msg(char *str);
char	*itoa_exit(t_shell *shell, char **str);
