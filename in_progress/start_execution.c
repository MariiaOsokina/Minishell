/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:20:57 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/14 11:29:46 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

int ft_node_execution(t_shell shell, t_node *tree)
{
    if (!tree)
        return(ENO_GENERAL);
    if (tree->type == N_PIPE)
        return (ft_exec_pipeline(shell, tree));
    //check AND and OR
    if (tree->type == N_CMD)
        return (ft_exec_simple_cmd(shell, tree));
    return (ENO_GENERAL);
}

int ft_exec_pipeline(t_shell shell, t_node *pipe_node)
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
        //child process for left with recursion
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
    // think about wait()?? and order of child proceess
    //signals
    return (ft_get_exit_status(tmp_status));
}

void start_execution(t_shell shell)
{
    signal(SIGQUIT, ft_sigquit_handler); //activate SIGQUIT NOT INTERACTIVE MODE
    
    //init_tree
    //inside save io_list(HERE_DOC) save all heredocs
    //if signal ctrl + C:inside heredoc:
        //1-save  exit code = 130 
        //2 - clear ast and this iteration's history;
        //3 and continue in while (1)(i.e. stop this iteration and move n to next iteration)
}
