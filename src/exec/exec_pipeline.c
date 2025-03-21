/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:53:30 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/21 00:27:48 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"

int ft_exec_pipeline(t_shell *shell, t_pipe *pipe_node)
{
	int 	pipe_fds[2];
	pid_t 	pid_left;
	pid_t 	pid_right;
	int		tmp_status;


	// printf("ft_exec_pipeline\n");

	//signals
	pipe(pipe_fds);
	pid_right = fork();
	if (pid_right == 0)	//child process for right with recursion
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
			waitpid(pid_right, &tmp_status, 0); // get exit status only from right
			//signals
			tmp_status = ft_get_exit_status(tmp_status);
			return (tmp_status); // ???
		}
	}
	return (ENO_GENERAL);
}

void ft_exec_pipe_right(t_shell *shell, t_pipe *pipe_node, int *pipe_fds)
{
	// ft_putstr_fd("RIGHT PIPE CMD, pipe nbr %d\n", STDERR_FILENO);
	// ft_putnbr_fd(pipe_node->nbr, STDERR_FILENO);
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	ft_exec_node(shell, pipe_node->right);
}

void ft_exec_pipe_left(t_shell *shell, t_pipe *pipe_node, int *pipe_fds)
{
	// ft_putstr_fd("LEFT PIPE CMD, pipe nbr %d\n", STDERR_FILENO);
	// ft_putnbr_fd(pipe_node->nbr, STDERR_FILENO);
	close(pipe_fds[0]);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	ft_exec_node(shell, pipe_node->left);
}
