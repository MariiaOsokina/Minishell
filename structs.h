/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:40:25 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/10 14:05:10 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft/libft.h"
#include <limits.h>
#include <stdbool.h>

/*May require a pointer to cwd and old working dir*/
typedef struct s_shell
{
	t_list *envp;        // Stores environment variables as a linked list.
	char **envp_arr;     // Stores environ variables as an array for execve().
	t_list *path;        // Stores directories from $PATH in a linked list.
	t_list *token_lst;   // Stores parsed command tokens for execution.
	char *input;         // Stores the raw command input from the user.
	char *trimmed_input; // Stores trimmed input (no leading/trailing spaces).
	void *root;          // Root of an AST (Abstract Syntax Tree) for parsing
	char *cmd_path;      // Stores the full executable path for a command.
	char *cwd;           // Current working directory
	int exit_code;       // Stores the exit code of the last command
	int fd;              // Stores the file descriptor used for redirections.
}				t_shell;

typedef struct s_env
{
	char		*value; //Value
	char		*content; //Key
	bool		is_export;
	bool		is_printed;
}				t_env;

// /*Command structs and typedefs*/
// typedef enum e_node_type
// {
// 	N_PIPE,
// 	N_EXEC,
// 	N_ANDIF,
// 	N_OR,
// }				t_node_type;

// typedef struct s_node
// {
// 	t_node_type	type;
// }				t_node;

// typedef struct s_exec
// {
// 	t_node		type;
// 	char		*command;
// 	char		**av;
// 	t_list		*infiles;
// 	t_list		*outfiles;
// }				t_exec;

//mo_suggestions

typedef enum e_node_type
{
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD
}	t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;


typedef struct s_io
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					fd_here_doc;
}	t_io;


typedef struct s_node
{
	t_node_type			type;
	t_io	*io;
	t_list				*io_list; // t_list list.content should be t_io(io);
	char				*args;
	char				**expanded_args;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

// t_list *io_list;
// t_io io;

// io_list.content = &io;

// io.type
// io_list.content.type

// int	io_list_set_type(t_node_type tp)
// {

// }

