/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:30 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/05 13:07:03 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"


/*TO BE SOLVED:
1- add panic function;
*/
/*
1 - NOTES: Options (e.g.  [n]) are not in the Minishell Subject!
2 - Get exit code (saved in shell.exit code from the last command executed)
3 - Put to STDERR!!! message “exit\n”;
4 - If more than one arg, error message to STDERR “too many arguments”, exit code should be 2.
5 - !!!Clean all -panic function -  to be done
6 - Exit() - termination current shell process with proper exit code.
*/



int	builtin_exit(t_shell shell, t_node *cmd)
{
    int	exit_code;

	exit_code = shell.exit_code;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->expanded_args[1])
	{
		exit_code = STDERR_FILENO;
		ft_err_msg("exit", cmd->expanded_args[1], "too many arguments");
	}
	//clean all //panic function;
	exit(exit_code);
}