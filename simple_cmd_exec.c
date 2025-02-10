/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:03:32 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/07 16:01:18 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}	t_err_msg;


typedef struct s_err
{
	t_err_no	no;
	t_err_msg	msg;
	char		*cause;
}	t_err;


typedef struct s_path
{
	t_err	err;
	char	*path;
}	t_path;


typedef enum e_err_no
{
	ENO_SUCCESS,//0
	ENO_GENERAL,//1
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND, //127
	ENO_EXEC_255 = 255
}	t_err_no;

//return is exit status
// 0: Success
// 1: General error
// 2: Misuse of shell builtins
// 126: Command invoked cannot execute
// 127: Command not found
// 128: Invalid argument to exit
// int	ft_exec_simple_cmd(t_node *node, bool piped)
bool piped = false;

typedef enum e_node_type
{
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD
}	t_node_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}	t_io_node;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef struct s_node
{
	t_node_type			type;
	t_io_node			*io_list;
	char				*args;
	char				**expanded_args;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

/* execute the simple command */

int	ft_exec_simple_cmd(t_node *node, bool piped)
{
	int		tmp_status;

	if (!node -> expanded_args) //1. if no cmd
	{
		tmp_status = ft_check_redirection(node); // handle redirection
		return (ft_reset_stds(piped), (tmp_status && ENO_GENERAL));
	}
	else if (ft_is_builtin((node -> expanded_args)[0])) //2. if builtin command
	{
		tmp_status = ft_check_redirection(node); // handle redirection
		if (tmp_status != ENO_SUCCESS)
			return (ft_reset_stds(piped), ENO_GENERAL);
		tmp_status = ft_exec_builtin(node -> expanded_args); // execute builtin
		return (ft_reset_stds(piped), tmp_status);
	}
	else
		return (ft_exec_child(node)); //3. if system command 
}

/*3. if system command*/ 

static int	ft_exec_child(t_list shell, t_node *cmd)
{
	// t_path	path_status;
	char    *path;
    int		tmp_status;
	int		fork_pid;

	// g_minishell.signint_child = true;
	fork_pid = fork();
    // if (fork_pid == -1)
    // perror("fork error"); // haddle errs later
    if (fork_pid == 0) //child process

    {
        tmp_status = ft_check_redirection();// handle redirections
        // if tmp_statis != sucsess = > error;
        path = ft_get_path(cmd->args[0]);//
        // if error path;
        execve(path, cmd->args, shell.evpl); //execution of command
        // if error execve; return of execve errno
            //TO DO free malloc/clean;
            ///exit (1);
    }
    waitpid(fork_pid, NULL, 0);//??
	// g_minishell.signint_child = false; //signals??
	return (ft_get_exit_status(tmp_status)); // return exit status
}

char *ft_get_path(char *)
{
    char *path;
    /////
    return (path);
}