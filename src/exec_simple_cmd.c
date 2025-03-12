/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:03:32 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/12 16:53:31 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"

/*
1 - No command:
	- Redirections (see below);
	- Reset STDIN and STDOUT???
2 - Built-ins: 
	- Check is it built-in (is cmd in the  built-ins list)
	- Redirections  (see below);
	- execution(call built-in functions);
	- Reset STDIN and STDOUT???
3 - System command(execve) (in child process);
*/

/*NOTE:
 The return status is exit status as provided by waitpid(), 
or 128+n if the command was terminated by signal n.
- handle signals*/

int	ft_exec_simple_cmd(t_shell shell, t_exec *exec_node)
{
	int		tmp_status;
		
	printf("test\n");

	//1. if no cmd
	if (exec_node->command == NULL)
	{
		printf("test\n");
		tmp_status = redirection(exec_node);
		//reset stds???
		return (tmp_status);
	}
	//2. if builtin command
	if (ft_is_builtin(exec_node->command)) 
	{
		tmp_status = redirection(exec_node);
		if (tmp_status != ENO_SUCCESS)
		{
			//all clear;
			//reset stds???
			return (tmp_status); // from child proccess
		}
		tmp_status = ft_exec_builtin(shell, exec_node);
		//reset stds???
		return (tmp_status); //128+n if signals
	}
	//3. system command (child process)
	else
	{
		tmp_status = ft_exec_external_cmd(shell, exec_node);
		return (tmp_status);
	}
}
