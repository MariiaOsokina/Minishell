/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:53:30 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/08 11:10:08 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exec_pipeline(t_shell *shell, t_pipe *pipe_node)
{
	int 	pipe_fds[2];
	pid_t 	pid_left;
	pid_t 	pid_right;
	int		tmp_status;

	pipe(pipe_fds);
	pid_right = fork();
	if (pid_right == 0)//child process for right with recursion
		ft_exec_pipe_right(shell, pipe_node, pipe_fds);
	else
	{
		pid_left = fork();
		if (pid_left == 0)//child process for left with recursion
			ft_exec_pipe_left(shell, pipe_node, pipe_fds);
		else
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			waitpid(pid_left,  &tmp_status, 0);
			waitpid(pid_right, &tmp_status, 0);
			free_shell(shell);
			// printf ("exit status from tmps status waitpid %d\n", tmp_status); // get exit status only from right
			return (ft_get_exit_status(tmp_status));
		}
	}
	return (ENO_GENERAL);
}

int ft_exec_pipe_right(t_shell *shell, t_pipe *pipe_node, int *pipe_fds)
{
	int tmp_status;

	shell->in_child = true;
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	tmp_status = ft_exec_node(shell, pipe_node->right);
	ft_free_full_shell(shell);
	exit(tmp_status);
}

int ft_exec_pipe_left(t_shell *shell, t_pipe *pipe_node, int *pipe_fds)
{
	int tmp_status;

	shell->in_child = true;
	close(pipe_fds[0]);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	tmp_status = ft_exec_node(shell, pipe_node->left);
	ft_free_full_shell(shell);
	exit(tmp_status);
}
