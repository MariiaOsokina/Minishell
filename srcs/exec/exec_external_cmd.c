/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:44:24 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/16 10:40:40 by mosokina         ###   ########.fr       */
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

static void	ft_exec_with_path(t_shell *shell, t_exec *exec_node)
{
	char	*cmd_path;
	int		tmp_status;
	
	cmd_path = exec_node->av[0];
	tmp_status = ft_check_access(cmd_path);
	if (tmp_status != ENO_SUCCESS)
		ft_exit_with_full_cleanup(shell, tmp_status);
	else if (execve(cmd_path, exec_node->av, shell->envp_arr) == -1)
		ft_exit_with_full_cleanup(shell, ENO_GENERAL);
}

static void	ft_exec_from_env(t_shell *shell, t_exec *exec_node)
{
	char		*cmd_path;
	t_err_no	err_no;

	cmd_path = ft_get_env_path(*shell, exec_node->av[0], &err_no);
	if (err_no != ENO_SUCCESS)
		ft_exit_with_full_cleanup(shell, err_no);
	else if (execve(cmd_path, exec_node->av, shell->envp_arr) == -1)
	{
		free(cmd_path);
		ft_exit_with_full_cleanup(shell, ENO_GENERAL);
	}
}

int	ft_exec_external_cmd(t_shell *shell, t_exec *exec_node)
{
    int		tmp_status;
	int		fork_pid;

	tmp_status = 0;
	fork_pid = fork();
	// to add error fork ...
    if (fork_pid == 0)
    {
		tmp_status = ft_redirections(shell, exec_node);
		if (tmp_status != ENO_SUCCESS)
			ft_exit_with_full_cleanup(shell, tmp_status);
		if (ft_strnstr(exec_node->av[0], "/", ft_strlen(exec_node->av[0])))
			ft_exec_with_path(shell, exec_node);
		else
			ft_exec_from_env(shell, exec_node);
    }
    waitpid(fork_pid, &tmp_status, 0);
	return (ft_get_exit_status(tmp_status));
}

// int	ft_exec_external_cmd(t_shell *shell, t_exec *exec_node)
// {
// 	char    *cmd_path;
//     int		tmp_status;
// 	int		fork_pid;
// 	t_err_no	err_no;

// 	tmp_status = 0;
// 	fork_pid = fork();
// 	// to add error fork ...
//     if (fork_pid == 0)
//     {
// 		tmp_status = ft_redirections(exec_node);
// 		if (tmp_status != ENO_SUCCESS)
// 		{
// 			ft_free_full_shell(shell);//panic
// 			exit(tmp_status); // from child proccess
// 		}
// 		if (ft_strnstr(exec_node->command, "/", ft_strlen(exec_node->command))) //execute with rel abs path
// 		{
// 			cmd_path = exec_node->command;
// 			tmp_status = ft_check_access(cmd_path);
// 			if (tmp_status != ENO_SUCCESS)
// 			{
// 				ft_free_full_shell(shell);
// 				exit(tmp_status); // from child proccess
// 			}
// 			else if (execve(cmd_path, exec_node->av, shell->envp_arr) == - 1) //all signals in execve reset to SIG_DEF!!!!
// 			{
// 				ft_free_full_shell(shell);
// 				exit(ENO_GENERAL); // from child process;
// 			}
// 		}
// 		else //exec no path
// 		{
// 			cmd_path = ft_get_env_path(*shell, exec_node->command, &err_no); // err_no as ptr for saving its value
// 			if (err_no != ENO_SUCCESS) //??change err_no to tmp status
// 			{
// 				ft_free_full_shell(shell);
// 				exit(err_no); // from child proccess
// 			}
// 			else if (execve(cmd_path, exec_node->av, (*shell).envp_arr) == - 1)
// 			{
// 				free(cmd_path);
// 				ft_free_full_shell(shell);
// 				exit(ENO_GENERAL); // from child process;
// 			}
// 		}
//     }
//     waitpid(fork_pid, &tmp_status, 0);
// 	return (ft_get_exit_status(tmp_status));
// }

/* check the permission to the file, print the error msg and return the error number*/

int	ft_check_access(char *cmd_path) 
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
		ft_err_msg(cmd_path, "Permission denied\n", NULL);
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
