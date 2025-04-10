/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:43:58 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/10 19:49:17 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
tests:

exit
echo $?

exit 10
echo $?

exit -10
echo $?


exit 2929229
echo $?

exit 16767676767676767677777777777777
echo $?

echo $SHLVL
exit ab112hjh
echo $SHLVL

exit ab112hjh
echo $?

echo $SHLVL
exit 70 args
echo $SHLVL

exit 70 args
echo $?
*/

/*TO BE SOLVED:
1- add panic function;
2 - !!!!subshell flag -- exit message only if one cmd not in subshell;
*/

/*STEPS:
1 - if not subshell (flagg) ???!!! put to STDERR!!! message “exit\n”;
2 - If only command exists (w/o arguments), then panic() and exit() 
with saved exit_code from the last command executed;
3 - if 1st arg exists:
	- get exit code (number) from arg1
	- check if 1st arg is not numeric (with no digits or >LONG_MAX), then 
		(a)error message  "numeric argument required" and panic() 
		and exit() with exit code 2;
	- check if 2st arg exists, then (a) STDERR “too many arguments”, 
		(b)exit status should be 1 and 
		(c)just!!!! return (not exit from process);
	- else - panic() and exit() with exit code getted from 1st arg (modulo %256);
*/

static void	ft_exit_panic(t_shell *shell, int in, int out)
{
	ft_unlink_heredocs(shell->heredoc_names);
	ft_free_full_shell(shell);
	close(in);
	close(out);
	return ;
}

int	ft_exit_parent(t_shell *sh, t_exec *exec_node, int in, int out)
{
	int	exit_code;	

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!exec_node->av[1])
		exit_code = sh->exit_code;
	else
	{
		exit_code = ft_get_exit_code(exec_node->av[1]);
		if (exit_code == -1)
		{
			ft_err_msg("exit", exec_node->av[1], "numeric argument required");
			exit_code = 2;
			ft_exit_panic(sh, in, out);
			exit(exit_code);
		}
		if (exec_node->av[2])
		{
			ft_err_msg("exit", exec_node->av[2], "too many arguments");
			sh->exit_code = ENO_GENERAL;
			return (sh->exit_code);
		}
	}
	ft_exit_panic(sh, in, out);
	exit (exit_code);
}

int	ft_exit_child(t_shell *shell, t_exec *exec_node)
{
	int	exit_code;

	if (!exec_node->av[1])
		exit_code = shell->exit_code;
	else
	{
		exit_code = ft_get_exit_code(exec_node->av[1]);
		if (exit_code == -1)
		{
			ft_err_msg("exit", exec_node->av[1], "numeric argument required");
			exit_code = 2;
			return (exit_code);
		}
		if (exec_node->av[2])
		{
			ft_err_msg("exit", exec_node->av[2], "too many arguments");
			shell->exit_code = ENO_GENERAL;
			// printf("exit status %d\n", shell->exit_code);
			return (shell->exit_code);
		}
	}
	return (exit_code);
}
