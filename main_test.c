/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:59:19 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/22 18:44:30 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <sys/wait.h>
#include <stdio.h>



static void del(void *content) {
    (void)content;
	return;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_shell shell;
	t_node 	cmd;
	t_list *path_next;
	t_list *path_next2;

    t_list *io_list;
    io_list = malloc(sizeof(t_list));
    t_list *io_list2;
    io_list2 = malloc(sizeof(t_list));


    t_io    *io_1;
    t_io    *io_2;
    io_1 = malloc(sizeof(t_io));
    io_2 = malloc(sizeof(t_io));


    cmd.io_list = io_list;
    io_list->content = (t_io*)io_1;
    io_list->next = NULL;
    
    io_list2->content = (t_io*)io_2;
    io_list2->next = NULL;
    ft_lstadd_back(&io_list, io_list2);

    char *str_arr[2];
    str_arr[0] = "outfile1";
    str_arr[1] = NULL;
    io_1->expanded_value = str_arr;

    io_1->fd_here_doc = -1;
    io_1->type = IO_APPEND;
    io_1->value = "outfile1";

    char *str_arr2[2];
    str_arr2[0] = "outfile2";
    str_arr2[1] = NULL;
    io_2->value = "outfile2";

    // // for checking *wildcard
    // char *str_arr2[3];
    // str_arr2[0] = "infile2";
    // str_arr2[1] = "infile";
    // str_arr2[2] = NULL;
    // io_2->value = "inf*";

    io_2->expanded_value = str_arr2;

    io_2->fd_here_doc = -1;
    io_2->type = IO_APPEND;



    

	shell.path = ft_lstnew("/usr/bin/");
	path_next = ft_lstnew("/usr/local/bin");
	path_next2 = ft_lstnew("/home/mosokina/.local/bin");
	ft_lstadd_back(&shell.path, path_next);
	ft_lstadd_back(&shell.path->next, path_next2);

	
    // // for checking no command(just redirections)
    // cmd.expanded_args = NULL;
    
	char *expanded_args[3];
	cmd.expanded_args = expanded_args;

	// expanded_args[0] = "wrongcommand";
	expanded_args[0] = "cd";
	// expanded_args[0] = "wrongcmd";

	// expanded_args[0] = "./test1";
	expanded_args[1] = "";
	// expanded_args[1] = "invalidargs";
	// expanded_args[1] = "./tests/test.o";
	// expanded_args[1] = "./tests/test.c";


	expanded_args[2] = NULL;
	shell.envp_arr = env;
	// printf("env %s\n", shell.envp_arr[0]);
	shell.exit_code = ft_exec_simple_cmd(shell, &cmd);
	// printf("exit status %d\n", shell.exit_code);
	ft_lstclear(&shell.path, &del);
	return (0);
}
