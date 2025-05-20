/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:43:58 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 20:23:13 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (shell->exit_code);
		}
	}
	return (exit_code);
}
