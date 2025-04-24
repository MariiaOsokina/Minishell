#ifndef MINISHELL_H
# define MINISHELL_H

# include "binary_tree.h"
# include "builtins.h"
# include "errors.h"
// # include "exec.h"
# include "input.h"
// # include "libft.h"
# include "logic_tree.h"
# include "structs.h"
# include "tokens.h"
# include "utils.h"
# include <colors.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*Minishell.h:  Macro Defs*/
# define ESC_START "\001\e[1;91m\002"
# define ESC_RESET "\001\e[0;93m\002"
# define PROMPT "Minishell ["
# define ESC_CODE "\001\e[1;91m\002] [\001\e[0;39m\002"
# define ARROW "\001\e[1;91m]\002 \001→\002\001\e[0m\002  \b"
# define MINISHELL "\001\e[0;93mminishell\e[0;39m\002"

/* Minishell.h: Metachars */
# define METACHARS "|;<>"

/*Minishell.h: This is a general util function*/
int		check_args(int ac, char **av, char **envp);

/* Minishell.h: Input management functions*/
bool	check_line_len(char *line);

/*terminal_utils.c*/
void	shell_input(t_shell *shell);
// void	exec_processes(t_shell *shell, void *root);
// int		handle_exec_node(t_shell *shell, void *root, int *status);

/*To go in errors.h*/
void	print_exit(void);
int		exit_code(int value);
bool	syntax_error_msg(char *str);
char	*itoa_exit(t_shell *shell, char **str);
# define SYNTAX_ERROR "minishell: syntax error "

#endif
