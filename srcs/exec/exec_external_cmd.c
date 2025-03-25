/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:44:24 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/25 14:33:54 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* STEPS:
1 - fork() as an external command (execve) should be in child process:
2 - Redirections;
3 - If absolute/relative path (with slash)  - check access to executable file
4 - If only command name  - get the path from $PATH;
5 - Execution of external command by using a function execve(), execve() replaces the child proccess;
6 - Retrieving the exit code from child to parent with waitpid();
7 - Get exit status (with macros WIFSIGNALED, WTERMSIG, WEXITSTATUS)
*/

/*NOTE:
 The return status is exit status as provided by waitpid(), 
or 128+n if the command was terminated by signal n.
- handle signals*/

/*TO BE SOLVED
- add panic()
- 	//should be OK. check (1)empty "PATH=" in env - if unset PATH??? (2) empty cmd name/cmd?
*/

int	ft_exec_external_cmd(t_shell shell, t_exec *exec_node)
{
	char    *cmd_path;
    int		tmp_status;
	int		fork_pid;
	t_err_no	err_no;

	tmp_status = 0;
	// to handle signals??? ...
	fork_pid = fork();
	// to add error fork ...
    if (fork_pid == 0)
    {
		tmp_status = ft_redirections(exec_node);
		if (tmp_status != ENO_SUCCESS)
		{
			//panic();
			exit(tmp_status); // from child proccess
		}
		//execute with rel abs path
		if (ft_strnstr(exec_node->command, "/", ft_strlen(exec_node->command)))
		{
			cmd_path = exec_node->command;
			tmp_status = ft_check_access(cmd_path);
			if (tmp_status != ENO_SUCCESS)
			{
				//panic();
				exit(tmp_status); // from child proccess
			}
			else if (execve(cmd_path, exec_node->av, shell.envp_arr) == - 1)
			{
				// panic();
				// ft_err_msg("execve error", strerror(errno), NULL);
				exit(ENO_GENERAL); // from child process;
			}
		}
		else //exec no path
		{
			cmd_path = ft_get_env_path(shell, exec_node->command, &err_no); // err_no as ptr for saving its value
			// printf("path: %s\n", cmd_path);
			if (err_no != ENO_SUCCESS) //??change err_no to tmp status
			{
				//panic();
				exit(err_no); // from child proccess
			}
			else if (execve(cmd_path, exec_node->av, shell.envp_arr) == - 1)
			{
				free(cmd_path);
				//panic();
				// ft_err_msg("execve error", strerror(errno), NULL);
				exit(ENO_GENERAL); // from child process;
				}
			}
    }
    waitpid(fork_pid, &tmp_status, 0); //  parent process can retrieve the tmp status(exit code) of the child
	return (ft_get_exit_status(tmp_status));
}


int	ft_check_access(char *cmd_path) // check the permission to the file, print the error msg and return the error number
{	
	if (access(cmd_path, F_OK) != 0)
	{
		ft_err_msg(cmd_path, "No such file or directory", NULL);
		return (ENO_NOT_FOUND);
	}
	else if (ft_cmd_is_dir(cmd_path))
	{
		ft_err_msg(cmd_path, "Is a directory", NULL);
		return (ENO_CANT_EXEC);
	}			
	else if (access(cmd_path, X_OK) != 0)// no execution rights
	{
		ft_err_msg(cmd_path, "Permission denied\n", NULL); //??check: strerror(errno) instead "Permition denied"
		return (ENO_CANT_EXEC);
	}
	return (ENO_SUCCESS);
}

/*This function checks if a given command (or file path) is a directory. 
It uses the stat() to retrieve info about the file 
and stores it in a struct stat called cmd_stat. 
The S_ISDIR macro is then used to check if the file is a directory 
by examining the st_mode field of cmd_stat.*/

bool	ft_cmd_is_dir(char *cmd_path)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd_path, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}
