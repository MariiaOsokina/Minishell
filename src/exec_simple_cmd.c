/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:03:32 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/19 23:35:26 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"

/* STEPS:
1 - No command:
	- Redirections;
	- Reset STDIN and STDOUT???
2 - Built-ins: 
	- Check is it built-in (is cmd in the  built-ins list)
	- Redirections;
	- execution(call built-in function);
	- Reset STDIN and STDOUT???
3 - External command(execve) in child process;
*/

/*TO BE SOLVED
- panic()*/


int	ft_exec_simple_cmd(t_shell *shell, t_exec *exec_node)
{
	int		tmp_status;
		

	//1. if no cmd
	if (exec_node->command == NULL)
	{
		tmp_status = ft_redirection(exec_node);
		// //reset stds???
		//dup2(STDIN, 0);
		//dup2(STDOUT, 1);
		return (tmp_status);
	}
	//2. if builtin command
	if (ft_is_builtin(exec_node->command)) 
	{
		tmp_status = ft_redirection(exec_node);
		if (tmp_status != ENO_SUCCESS)
		{
			//panic();
			//reset stds???
			//dup2(STDIN, 0);
			//dup2(STDOUT, 1);
			return (tmp_status); // from child proccess
		}
		tmp_status = ft_exec_builtin(shell, exec_node);
			//reset stds???
			//dup2(STDIN, 0);
			//dup2(STDOUT, 1);
		return (tmp_status); //128+n if signals
	}
	//3. system command (child process)
	else
	{
		tmp_status = ft_exec_external_cmd(*shell, exec_node);
		return (tmp_status);
	}
}
