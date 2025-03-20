/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:53:30 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/20 00:55:52 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"

int ft_exec_pipeline(t_shell *shell, t_pipe *pipe_node)
{
	int 	pipe_fds[2];
	pid_t 	pid_left;
	pid_t 	pid_right;
	int		tmp_status;

	//signals
	pipe(pipe_fds);
	pid_right = fork();
	if (pid_right == 0)	//child process for right with recursion
		ft_exec_pipe_right(shell, pipe_node, pipe_fds);
	pid_left = fork();
	if (pid_left == 0)//child process for left with recursion
		ft_exec_pipe_left(shell, pipe_node, pipe_fds);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid_left,  &tmp_status, 0);
	waitpid(pid_right, &tmp_status, 0); // get exit status only from right
	//signals
	tmp_status = ft_get_exit_status(tmp_status);
	return (tmp_status);
}

void ft_exec_pipe_right(t_shell *shell, t_pipe *pipe_node, int *pipe_fds)
{
	dup2(STDIN_FILENO, pipe_fds[0]);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	ft_exec_node(shell, pipe_node->right);
}

void ft_exec_pipe_left(t_shell *shell, t_pipe *pipe_node, int *pipe_fds)
{
	dup2(STDOUT_FILENO, pipe_fds[1]);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	ft_exec_node(shell, pipe_node->left);
}


