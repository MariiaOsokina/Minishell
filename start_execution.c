/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:20:57 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/28 10:55:15 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"



int ft_exec_pipeline(t_shell shell, t_node *tree)
{
    int pipe_fds[2];
    pid_t pid_left;
    pid_t pid_right;
    int		tmp_status;

    //signals
    pipe(pipe_fds);
    pid_left = fork();
    if (pid_left == 0)
    {
        //child process for left with recursion
    }
    pid_right = fork();
    if (pid_right == 0)
    {
        ////child process for right with recursion
    }
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    waitpid(pid_left,  &tmp_status, 0);
    waitpid(pid_right,  &tmp_status, 0); // think about wait()?? and order of child proceess
    //signals
    return (ft_get_exit_status(tmp_status));
}

int ft_node_execution(t_shell shell, t_node *tree)
{
    if (!tree)
        return(ENO_GENERAL);
    if (tree->type == N_PIPE)
        return (ft_exec_pipeline(shell, tree));
    //check AND and OR
    if (tree->type == N_CMD)
        ft_exec_simple_cmd(shell, tree);
    return (ENO_GENERAL);
}