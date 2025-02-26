/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:30 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/26 23:30:50 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"


/* no options according to the subject
*/

void	builtin_exit(t_shell shell, t_node *cmd)
{
    int	exit_code;

	exit_code = shell.exit_code;

	//in pipe doesn't printed(incl redirections)
	printf("exit\n");
	if (cmd->expanded_args[1])
	{
		exit_code = 2;
		ft_err_msg("exit", cmd->expanded_args[1], "too many arguments");
	}
	//clean all
	printf("exit code :%d\n", exit_code); // just for testing
	exit(exit_code);
}