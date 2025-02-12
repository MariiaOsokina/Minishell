/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:03:32 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/12 01:37:54 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
// #include "libft/libft.h"
#include <sys/wait.h>
#include <stdio.h>

int	ft_exec_child(t_shell shell, t_node *cmd, char **expanded_args);
int	ft_exec_simple_cmd(t_shell shell, t_node *cmd, char **expanded_args);
t_err	ft_check_access(char *file);

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_shell shell;
	t_node 	cmd;
	char *expanded_args[3];

	expanded_args[0] = "/usr/bin/ls";
	// expanded_args[0] = "cd";
	// expanded_args[0] = "/ls";
	// expanded_args[0] = "./test1";
	expanded_args[1] = "-la";
	expanded_args[2] = NULL;
	shell.envp_arr = env;
	// printf("env %s\n", shell.envp_arr[0]);
	ft_exec_simple_cmd(shell, &cmd, expanded_args);
	return(0);
}


/* execute the simple command */
/*The return status (see Section 3.7.5 [Exit Status], page 44)
of a simple command is its exit status as provided by the posix 1003.1 waitpid function, 
or 128+n if the command was terminated by signal n.*/


/*error messsage: cdhhh: command not found
*/
 
int	ft_exec_simple_cmd(t_shell shell, t_node *cmd, char **expanded_args)
{
	int		tmp_status;

	// if (!node -> expanded_args) //1. if no cmd
	// {
	// 	tmp_status = ft_check_redirection(node); // handle redirection
	// 	return (ft_reset_stds(piped), (tmp_status && ENO_GENERAL));
	// }
	if (ft_is_builtin((expanded_args)[0])) //2. if builtin command
	{
		printf("exec builtin\n");
		//to add redirections ...
		tmp_status = ft_exec_builtin(expanded_args);
		return (tmp_status);
	}
	else
	{
		tmp_status = ft_exec_child(shell, cmd, expanded_args);
		return (tmp_status);
	}
}

/*3. if it's system command, itshould be in child process*/

int	ft_exec_child(t_shell shell, t_node *cmd, char **expanded_args)
{
	char    *path;
    int		tmp_status;
	int		fork_pid;
	t_err	err_struct;
	
	// to handle signals??? ...
	fork_pid = fork();
	// to add error fork ...
    if (fork_pid == 0)
    {
		//to add redirections ...
		if (ft_strnstr(expanded_args[0], "/", ft_strlen(expanded_args[0])))
		{
			
			err_struct = ft_check_access(expanded_args[0]);// chech access(permission and that file is existed )
			if (err_struct.no != ENO_SUCCESS)
			{
				ft_err_msg(err_struct);
				//all clear;
				exit(err_struct.no); // from child proccess
			}
			else if (execve(expanded_args[0], expanded_args, shell.envp_arr) == - 1)
			{
				// all clear;
				exit(ENO_GENERAL); // from child process;
			};
		}
		else
		{
			printf("Need to seach path\n");
			// path = ft_get_path(cmd->args[0]);
		// 	execve(path, cmd->args, shell.envp);
		// 	//to add error ...;
		}
    }
    waitpid(fork_pid, &tmp_status, 0); //  tmp_status - parent process can retrieve the exit status of the child
	//to add tmp_status + 127(signals)
	return (tmp_status);
}

t_err	ft_check_access(char *file)
{
	t_err err_struct;
	
	if (access(file, F_OK) == 0) // file exists
	{
		if (access(file, X_OK) == -1) // no exection rights
			err_struct = (t_err){ENO_CANT_EXEC, ERRMSG_PERM_DENIED, file};
		else
			err_struct = (t_err){ENO_SUCCESS, 42, NULL}; //42??
	}
	else //file doesn't exist
		err_struct = (t_err){ENO_NOT_FOUND, ERRMSG_NO_SUCH_FILE, file};
	// ((t_err){ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, file}); // no slash
	return (err_struct);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len > s2_len)
		return (ft_strncmp(s1, s2, s1_len));
	else
		return (ft_strncmp(s1, s2, s2_len));
}

bool ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "echo") 
		|| !ft_strcmp(cmd, "cd") 
		|| !ft_strcmp(cmd, "exit") 
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env"))
		return (true);
	return (false);
}

t_err_no ft_exec_builtin(char **args)
{
	char *cmd;

	cmd = args[0];
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(args));
	else if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(args));
	else if (!ft_strcmp(cmd, "export"))
		return (builtin_export(args));
	else if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(args));
	else if (ft_strcmp(cmd, "env"))
		return (builtin_env(args));
	else if (!ft_strcmp(cmd, "exit"))
		return (builtin_exit(args)); // ENO_GENERAL?
	else
		return (ENO_NOT_FOUND);
}

t_err_no redirection(t_node)
{
	
}

ft_out
ft_is
ft_append


heredoc
