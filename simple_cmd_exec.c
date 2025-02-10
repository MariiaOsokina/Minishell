/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:03:32 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/10 14:09:55 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
// #include "libft/libft.h"
#include <sys/wait.h>
#include <stdio.h>

int	ft_exec_child(t_shell shell, t_node *cmd, char **expanded_args);
int	ft_exec_simple_cmd(t_shell shell, t_node *cmd, char **expanded_args);

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_shell shell;
	t_node 	cmd;
	char *expanded_args[2];

	expanded_args[0] = "/usr/bin/ls";
	expanded_args[1] = NULL;
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
	// else if (ft_is_builtin((node -> expanded_args)[0])) //2. if builtin command
	// {
	// 	tmp_status = ft_check_redirection(node); // handle redirection
	// 	if (tmp_status != ENO_SUCCESS)
	// 		return (ft_reset_stds(piped), ENO_GENERAL);
	// 	tmp_status = ft_exec_builtin(node -> expanded_args); // execute builtin
	// 	return (ft_reset_stds(piped), tmp_status);
	// }
	// else
	// {
		tmp_status = ft_exec_child(shell, cmd, expanded_args);
		return (tmp_status);
	// }
}

/*3. if system command, should be in child process*/
/*No such file or directory*/

int	ft_exec_child(t_shell shell, t_node *cmd, char **expanded_args)
{
	char    *path;
    int		tmp_status;
	int		fork_pid;
	
	// to handle signals??? ...
	fork_pid = fork();
	// to add error fork ...
    if (fork_pid == 0)
    {
		//to add redirections ...
		if (ft_strnstr(expanded_args[0],"/", ft_strlen(expanded_args[0])))
		{
			execve(expanded_args[0], expanded_args, shell.envp_arr);
			printf("No such file or directory\n");
		}
		// else
		// {
		// 	path = ft_get_path(cmd->args[0]);
		// 	execve(path, cmd->args, shell.envp);
		// 	//to add error ...;
		// }
    }
    waitpid(fork_pid, &tmp_status, 0);
	//to add tmp_status + 127(signals)
	return (tmp_status); // return exit status
}
