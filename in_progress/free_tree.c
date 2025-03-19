/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:28:23 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/18 16:12:31 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"
// #include <stdlib.h>

/* Forward declaration for recursive function */
void free_node(t_node *node);

// /**
//  * Recursively frees a node in the tree
//  * @param node The node to free
//  */
void free_node(t_node *node)
{
    t_pipe *pipe_node;
    t_exec *exec_node;
    if (!node)
        return;

    if (node->type == N_PIPE)
    {
        pipe_node = (t_pipe *)node;
        /* Recursively free left and right branches */
        if (pipe_node->left)
            free_node((t_node *)pipe_node->left);
        if (pipe_node->right)
            free_node((t_node *)pipe_node->right);
        /* Free the pipe node itself */
        if (pipe_node)
            free(pipe_node);
    }
    else if (node->type == N_EXEC)
    {
        exec_node = (t_exec *)node;
        /*
        if (exec_node->av) {
            int i = 0;
            while (exec_node->av[i]) {
                free(exec_node->av[i]);
                i++;
            }
            free(exec_node->av);
        }
        */
        
        // /* Free the in_out_list if it exists */
        // if (exec_node->in_out_list) {
        //     /* Assuming you have a function to free t_list */
        //     /* This part depends on your t_list implementation */
        //     ft_lstclear(&exec_node->in_out_list, free);
        // }
        
        /* Free the exec node itself */
        if (exec_node)
            free(exec_node);
    }
    else
    {
        /* Just free the node if type is unknown */
        if (node)
            free(node);
    }
}

/**
 * Cleans up and frees all memory allocated for the shell structure*/
void clean_shell(t_shell *shell)
{
    if (!shell || !shell->root)
        return;
    
    /* Start the recursive cleanup from the root */
    free_node(shell->root);
    
    /* Reset the root pointer to avoid double free */
    shell->root = NULL;
}
