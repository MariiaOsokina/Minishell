#pragma once

#include "libft.h"
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

/*Command structs and typedefs*/
typedef enum e_node_type
{
	N_PIPE,
	N_EXEC,
	N_ANDIF,
	N_OR,
}				t_node_type;

typedef struct s_node
{
	t_node_type	type;
}				t_node;

typedef struct s_exec
{
	t_node		type;
	char		*command;
	char		**av;
	t_list		*infiles;
	t_list		*outfiles;
}				t_exec;
