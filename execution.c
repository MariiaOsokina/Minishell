/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:12:19 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/03 11:36:42 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    
    t_data data;
    t_command cmd1, cmd2;
    
    char *args1[] = {"/usr/bin/cat", NULL};
    char *args2[] = {"/usr/bin/cat", NULL};// t_command cmd1, cmd2, cmd3;

    // Initialize cmd1
    cmd1.path = args1[0];


    cmd1.args = args1;
    cmd1.next = &cmd2;
    cmd1.prev = NULL;

    // Initialize cmd2
    cmd2.path = args2[0];
    cmd2.args = args2;
    cmd2.prev = &cmd1;
    cmd2.next = NULL;

    // // Initialize 
    // cmd3.path = "/bin/echo";
    // cmd3.args = {"/bin/echo", "Hello, world!", NULL};
    // cmd3.next = NULL;
    // cmd3.prev = &cmd2;
    // Initialize t_data
    data.cmd = &cmd1;
    data.pid = 0; // or any appropriate value

    t_io_fds io;
    io.fd_in = -1;
    io.infile = "infile1.txt";
    // io.infile = NULL;

    io.fd_out = -1;
    io.outfile = NULL;

    io.stdin_backup = -1;
    io.stdout_backup = -1;
    io.fdpipe[0] = -1;
    io.fdpipe[1] = -1;
    data.io = &io;
    execute(&data, &data.io);
    return (0);
}


void     execute(t_data *data, t_io_fds *io)
{
    t_command *cmd;

    cmd = data->cmd;
    //save in/out for restoring at the end of execute()
    io->stdin_backup = dup(0);
    io->stdout_backup = dup(1);
    //set the initial input
    if (io->infile)
    {
        io->fd_in = open(io->infile, O_RDONLY);
        printf("std %i\n", io->fd_in);
        // TODO chech fd -1
    }
    else
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
                io->fd_out = open(io->outfile, O_RDONLY);
            }
            else
                io->fd_out = dup(io->stdout_backup);            
        }
        else
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
            printf("child process\n");
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
