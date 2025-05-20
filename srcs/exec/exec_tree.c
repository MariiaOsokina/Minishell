/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:20:57 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/30 11:13:16 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_execution(t_shell *shell)
{
	g_signum = 0;
	ft_process_heredocs(shell, shell->root);
	if (g_signum == SIGINT)
		shell->exit_code = 130;
	else
	{
		ft_signals_noninteractive();
		shell->exit_code = ft_exec_node(shell, shell->root);
		ft_signals_interactive();
		if (g_signum == SIGINT)
			ft_putstr_fd("^C\n", STDERR_FILENO);
		if (g_signum == SIGQUIT)
			ft_putstr_fd("^\\Quit\n", STDERR_FILENO);
		g_signum = 0;
	}
	ft_unlink_heredocs(shell->heredoc_names);
	if (shell->heredoc_names != NULL)
		ft_lstclear(&(shell)->heredoc_names, free);
}

static int	ft_exec_andif(t_shell *shell, t_andif *andif_node)
{
	shell->exit_code = ft_exec_node(shell, andif_node->left);
	if (shell->exit_code == ENO_SUCCESS)
		shell->exit_code = ft_exec_node(shell, andif_node->right);
	return (shell->exit_code);
}

static int	ft_exec_or(t_shell *shell, t_or *or_node)
{
	shell->exit_code = ft_exec_node(shell, or_node->left);
	if (shell->exit_code != ENO_SUCCESS)
		shell->exit_code = ft_exec_node(shell, or_node->right);
	return (shell->exit_code);
}

static int	ft_exec_subshell(t_shell *shell, t_op *subshell_node)
{
	pid_t	pid_subshell;
	int		tmp_status;

	pid_subshell = fork();
	if (pid_subshell == 0)
	{
		shell->in_child = true;
		tmp_status = ft_exec_node(shell, subshell_node->left);
		ft_exit_with_full_cleanup(shell, tmp_status);
	}
	else
	{
		waitpid(pid_subshell, &tmp_status, 0);
		return (ft_get_exit_status(tmp_status));
	}
	return (ENO_GENERAL);
}

int	ft_exec_node(t_shell *shell, void *node)
{
	t_node	*type_node;
	int		tmp_status;

	tmp_status = ENO_SUCCESS;
	type_node = (t_node *)node;
	if (type_node->type == N_SUBSHELL)
		tmp_status = ft_exec_subshell(shell, (t_op *)node);
	else if (type_node->type == N_ANDIF)
		tmp_status = ft_exec_andif(shell, (t_andif *)node);
	else if (type_node->type == N_OR)
		tmp_status = ft_exec_or(shell, (t_or *)node);
	else if (type_node->type == N_PIPE)
		tmp_status = ft_exec_pipeline(shell, (t_pipe *)node);
	else if (type_node->type == N_EXEC)
		tmp_status = ft_exec_simple_cmd(shell, (t_exec *)node);
	return (tmp_status);
}
