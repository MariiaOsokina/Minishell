/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process_hd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:27:52 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 13:52:22 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_process_hd_pipe(t_shell *shell, t_pipe *pipe)
{
	if (pipe->left)
		ft_process_heredocs(shell, pipe->left);
	if (pipe->right && g_signum != SIGINT)
		ft_process_heredocs(shell, pipe->right);
}

static void	ft_process_hd_andif(t_shell *shell, t_andif *andif)
{
	if (andif->left && g_signum != SIGINT)
		ft_process_heredocs(shell, andif->left);
	if (andif->right && g_signum != SIGINT)
		ft_process_heredocs(shell, andif->right);
}

static void	ft_process_hd_or(t_shell *shell, t_or *or)
{
	if (or->left && g_signum != SIGINT)
		ft_process_heredocs(shell, or->left);
	if (or->right && g_signum != SIGINT)
		ft_process_heredocs(shell, or->right);
}

static void	ft_process_hd_subshell(t_shell *shell, t_op *sub)
{
	if (sub->left && g_signum != SIGINT)
		ft_process_heredocs(shell, sub->left);
}

void	ft_process_heredocs(t_shell *shell, void *node)
{
	t_node	*type_node;

	if (g_signum == SIGINT || !node)
		return ;
	type_node = (t_node *)node;
	if (type_node->type == N_SUBSHELL)
		ft_process_hd_subshell(shell, (t_op *)node);
	if (type_node->type == N_ANDIF)
		ft_process_hd_andif(shell, (t_andif *)node);
	else if (type_node->type == N_OR)
		ft_process_hd_or(shell, (t_or *)node);
	if (type_node->type == N_PIPE)
		ft_process_hd_pipe(shell, (t_pipe *)node);
	else if (type_node->type == N_EXEC)
		ft_handle_heredocs(shell, (t_exec *)node);
	return ;
}
