/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:12:19 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/03 12:56:26 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *data, t_io_fds *io)
{
	t_command	*cmd;

	cmd = data->cmd;
	//save in/out for restoring at the end of execute()
	io->stdin_backup = dup(0);
	io->stdout_backup = dup(1);
	//set the initial input
	if (io->infile)
	{
		io->fd_in = open(io->infile, O_RDONLY);
		// TODO chech fd -1
	}
	else
		//use default input
		io->fd_in = dup(io->stdin_backup);
	while (cmd)
	{
		//redirect input
		dup2(io->fd_in, 0);
		close(io->fd_in);
		//setup output
		if (cmd->next == NULL) // if the last cmd
		{
			if (io->outfile)
			{
				io->fd_out = open(io->outfile,  O_CREAT | O_RDWR | O_TRUNC, 0644); // TO DO think about mode
			}
			else
				io->fd_out = dup(io->stdout_backup); //use default output        
		}
		else // not the last cmd -> create pipe
		{
			pipe(io->fdpipe);
			io->fd_out = io->fdpipe[1];
			io->fd_in = io->fdpipe[0];
		}
		//redirect output
		dup2(io->fd_out, 1);
		close(io->fd_out);
		data->pid = fork();

		if (data->pid == -1)
			perror("fork error"); // haddle errs later
		if (data->pid == 0)
		{
			//child process
			execve(cmd->path, cmd->args, NULL);
			perror("execve");
			//TO DO free malloc;
			exit (1);
		}
		cmd = cmd->next;
	}

	// restore in/out defaults
	dup2(io->stdin_backup, 0);
	dup2(io->stdout_backup, 1);
	close(io->stdin_backup);
	close(io->stdout_backup);
	waitpid(data->pid, NULL, 0);
	return ;
}
