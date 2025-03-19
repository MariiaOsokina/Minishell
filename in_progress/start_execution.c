/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:20:57 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/18 10:44:27 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"

int ft_exec_pipeline(t_shell *shell, t_pipe *pipe_node);


int ft_node_execution(t_shell *shell, void *node)
{
	t_node *type_node;

	type_node = (t_node*)node;
	if (type_node->type == N_OR)
		return (ft_exec_andif(shell, (t_or *)node));
	if  (type_node->type == N_ANDIF)
		return (ft_exec_or(shell, (t_andif *)node));
	if (type_node->type == N_PIPE)
		return (ft_exec_pipeline(shell, (t_pipe *)node));
	if (type_node->type == N_EXEC)
		return (ft_exec_simple_cmd(shell, (t_exec *)node));
	return (ENO_GENERAL);
}

int ft_exec_andif(t_shell *shell, t_andif *andif_node)
{
	int		tmp_status;

	tmp_status = ft_node_execution(shell, andif_node->left);
	if (tmp_status == ENO_SUCCESS)
		tmp_status= ft_node_execution(shell, andif_node->right);
	return (tmp_status);
}

int ft_exec_or(t_shell *shell, t_or *or_node)
{
	int		tmp_status;

	tmp_status = ft_node_execution(shell, or_node->left);
	if (tmp_status != ENO_SUCCESS)
		tmp_status= ft_node_execution(shell, or_node->right);
	return (tmp_status);
}

int ft_exec_pipeline(t_shell *shell, t_pipe *pipe_node)
{
	int pipe_fds[2];
	pid_t pid_left;
	pid_t pid_right;
	int		tmp_status;

	//signals
	pipe(pipe_fds);
	pid_right = fork();
	if (pid_right == 0)
	{
		//child process for right with recursion
		dup2(STDIN_FILENO, pipe_fds[0]);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		printf("STDIN: %d\n", STDIN_FILENO);
		printf("STDOUT: %d\n", STDOUT_FILENO);
		ft_node_execution(shell, pipe_node->right);
	}
	pid_left = fork();
	if (pid_left == 0)
	{
		//child process for left with recursion
		dup2(STDOUT_FILENO, pipe_fds[1]);
		printf("STDIN: %d\n", STDIN_FILENO);
		printf("STDOUT: %d\n", STDOUT_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		ft_node_execution(shell, pipe_node->left);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid_left,  &tmp_status, 0);
	waitpid(pid_right,  &tmp_status, 0); // get exit status only from right
	//signals
	return (ft_get_exit_status(tmp_status));
}


// void start_execution(t_shell shell)
// {
//     signal(SIGQUIT, ft_sigquit_handler); //activate SIGQUIT NOT INTERACTIVE MODE
	
	//init_tree
	//inside save io_list(HERE_DOC) save all heredocs
	//if signal ctrl + C:inside heredoc:
		//1-save  exit code = 130 
		//2 - clear ast and this iteration's history;
		//3 and continue in while (1)(i.e. stop this iteration and move n to next iteration)
// }
