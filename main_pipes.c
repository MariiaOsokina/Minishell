/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:03:10 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/17 14:20:45 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/structs.h"

static void del(void *content) {
    (void)content;
	return;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_shell shell;
	t_list *path_next;
	t_list *path_next2;
    shell.exit_code = 0;
    ft_env_lst(&shell, env);
    shell.path = NULL;
    
    t_exec 	*exec_node1;
    t_exec 	*exec_node2;
    t_exec 	*exec_node3;
    t_exec 	*exec_node4;

    exec_node1 = malloc(sizeof(t_exec));
    exec_node2 = malloc(sizeof(t_exec));
    exec_node3 = malloc(sizeof(t_exec));
    exec_node4 = malloc(sizeof(t_exec));


    exec_node1->in_out_list = NULL;
    exec_node2->in_out_list = NULL;
    exec_node3->in_out_list = NULL;
    exec_node4->in_out_list = NULL;

	char *expanded_args1[2];
	expanded_args1[0] = "/usr/bin/ls";
    expanded_args1[1] = NULL;
    exec_node1->av = expanded_args1;
    exec_node1->command = expanded_args1[0];
    exec_node1->type.type = N_EXEC;

	char *expanded_args2[2];
	expanded_args2[0] = "ls";
    expanded_args2[1] = NULL;
    exec_node2->av = expanded_args2;
    exec_node2->command = expanded_args2[0];
    exec_node2->type.type = N_EXEC;
    
	char *expanded_args3[2];
	expanded_args3[0] = "ls";
    expanded_args3[1] = NULL;
    exec_node3->av = expanded_args3;
    exec_node3->command = expanded_args3[0];
    exec_node3->type.type = N_EXEC;


    char *expanded_args4[2];
	expanded_args4[0] = "ls";
    expanded_args4[1] = NULL;
    exec_node4->av = expanded_args4;
    exec_node4->command = expanded_args4[0];
    exec_node4->type.type = N_EXEC;


    t_pipe  *pipe1;
    t_pipe  *pipe2;
    t_pipe  *pipe3;

    pipe1 = malloc(sizeof(t_pipe));
    pipe2 = malloc(sizeof(t_pipe));
    pipe3 = malloc(sizeof(t_pipe));



    pipe3->type.type = N_PIPE;
    pipe3->left = pipe2;
    pipe3->right = exec_node4;

    pipe2->type.type = N_PIPE;
    pipe2->left = pipe1;
    pipe2->right = exec_node3;


    pipe1->type.type = N_PIPE;
    pipe1->left = exec_node1;
    pipe1->right = exec_node2;

    shell.root = pipe3;

    
	shell.envp_arr = env;
	// printf("env %s\n", shell.envp_arr[0]);
	shell.exit_code = ft_node_execution(&shell, &shell.root);
	printf("exit status %d\n", shell.exit_code);
    ft_free_env_lst(&shell.envp);
	ft_lstclear(&shell.path, &del);
	return (0);
}
