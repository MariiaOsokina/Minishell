/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:27:11 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/19 11:53:11 by mosokina         ###   ########.fr       */
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

	char *delimeter_test;
	delimeter_test = "DELIMETER";

	t_shell shell;
	t_exec 	*exec_node;
	exec_node = malloc(sizeof(t_exec));
	// t_list *path_next;
	// t_list *path_next2;
    shell.exit_code = 0;
    
    // ft_env_lst(&shell, env);
	// ft_print_env_lst(shell.envp);
	// ft_free_env_lst(&shell.envp);
    
    exec_node->in_out_list = NULL;

    // HEREDOC redirections:

    t_list *in_out_list1;
    in_out_list1 = malloc(sizeof(t_list));

    t_in_out    *io_1;
    io_1 = malloc(sizeof(t_in_out));
	
    exec_node->in_out_list = in_out_list1;
    in_out_list1->content = (t_in_out*)io_1;
    in_out_list1->next = NULL;

    io_1->type = HERE;
	io_1->eof = ft_strdup(delimeter_test);
	io_1->fd_heredoc = -1;
	io_1->name = NULL;
    io_1->expanded_name = NULL;

    shell.path = NULL;
    exec_node->av = NULL;
	
	shell.envp_arr = env;
	shell.envp = NULL;

	// shell.exit_code = ft_exec_simple_cmd(shell, &exec_node);
	printf("exit status %d\n", shell.exit_code);
	free(io_1->eof);
	free(io_1);
	free(in_out_list1);
	free(exec_node);
	return (0);
}
