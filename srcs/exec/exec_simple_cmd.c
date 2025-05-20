/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:03:32 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/29 10:00:27 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_reset_stdio(int tmp_stdin, int tmp_stdout)
{
	dup2(tmp_stdin, STDIN_FILENO);
	dup2(tmp_stdout, STDOUT_FILENO);
	close(tmp_stdin);
	close(tmp_stdout);
}

static int	ft_exec_no_cmd(t_shell *shell, t_exec *exec_node)
{
	int		tmp_stdin;
	int		tmp_stdout;
	int		tmp_status;

	(void)shell;
	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	tmp_status = ENO_SUCCESS;
	tmp_status = ft_redirections(shell, exec_node);
	ft_reset_stdio(tmp_stdin, tmp_stdout);
	return (tmp_status);
}

static int	ft_exec_builtins_start(t_shell *shell, t_exec *exec_node)
{
	int		tmp_stdin;
	int		tmp_stdout;
	int		tmp_status;

	tmp_stdin = dup(STDIN_FILENO);
	tmp_stdout = dup(STDOUT_FILENO);
	tmp_status = ft_redirections(shell, exec_node);
	if (tmp_status != ENO_SUCCESS)
	{
		ft_reset_stdio(tmp_stdin, tmp_stdout);
		return (tmp_status);
	}
	if (!ft_strcmp(exec_node->av[0], "exit") && shell->in_child == false)
		tmp_status = ft_exit_parent(shell, exec_node,
				tmp_stdin, tmp_stdout);
	else
		tmp_status = ft_exec_builtin(shell, exec_node);
	ft_reset_stdio(tmp_stdin, tmp_stdout);
	return (tmp_status);
}

int	ft_exec_simple_cmd(t_shell *shell, t_exec *exec_node)
{
	int	tmp_status;

	tmp_status = ENO_SUCCESS;
	ft_expand_args(shell, exec_node);
	if (exec_node->av == NULL || exec_node->av[0] == NULL)
		tmp_status = ft_exec_no_cmd(shell, exec_node);
	else if (ft_is_builtin(exec_node->av[0]))
		tmp_status = ft_exec_builtins_start(shell, exec_node);
	else
		tmp_status = ft_exec_external_cmd(shell, exec_node);
	return (tmp_status);
}
