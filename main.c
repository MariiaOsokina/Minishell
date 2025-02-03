/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:11:42 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/03 12:47:30 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	
	t_data	data;
	t_command	cmd1,	cmd2, cmd3;
	t_io_fds	io;

	char *args1[] = {"/usr/bin/cat", NULL};
	char *args2[] = {"/usr/bin/cat", NULL};
	char *args3[] = {"/usr/bin/cat", NULL};
	// char *args1[] = {"bin/echo", "hello", NULL};
	// char *args2[] = {"/usr/bin/cat", NULL};
	// char *args3[] = {"/usr/bin/cat", NULL};

	// Initialize cmd1
	cmd1.args = args1;
	cmd1.path = cmd1.args[0];
	cmd1.next = &cmd2;
	cmd1.prev = NULL;

	// Initialize cmd2
	cmd2.args = args2;
	cmd2.path = cmd2.args[0];
	cmd2.prev = &cmd1;
	cmd2.next = &cmd3;

	// // Initialize cmd3
	cmd3.args = args3;
	cmd3.path = cmd3.args[0];
	cmd3.prev = &cmd2;
	cmd3.next = NULL;
	// Initialize t_data
	data.cmd = &cmd1;
	data.pid = 0; // or any appropriate value

	io.fd_in = -1;
	io.infile = "infile1.txt";
	// io.infile = NULL;

	io.fd_out = -1;
	io.outfile = "outfile3.txt";
    // io.outfile = NULL;

	io.stdin_backup = -1;
	io.stdout_backup = -1;
	io.fdpipe[0] = -1;
	io.fdpipe[1] = -1;
	data.io = io;
	execute(&data, &data.io);
	return (0);
}
