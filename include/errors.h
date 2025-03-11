#pragma once

#include "minishell.h"

#define LINE_ERROR "line too long!"
#define CLOSE_ERROR "near unexpected token `)'"
#define OPEN_ERROR "near unexpected token `('"
#define OPEN_QUOTE "`open quote'"
#define PIPE_ERROR "near unexpected token `|'"
#define REDIR_ERROR "near unexpected token `newline'"

/*exit_messages.c*/
void	exit_failure(t_shell *shell, char *info);
