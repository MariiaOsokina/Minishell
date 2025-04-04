#include "minishell.h"

// static void print_path_list(t_list *path_list)
// {
//     t_list *current;
//     int count;

//     if (!path_list)
//     {
//         printf("PATH is empty or not set\n");
//         return;
//     }

//     printf("PATH directories:\n");
//     current = path_list;
//     count = 0;
    
//     while (current)
//     {
//         // Print each path with an index
//         printf("[%d] %s\n", count++, (char *)current->content);
//         current = current->next;
//     }
    
//     printf("Total: %d directories in PATH\n", count);
// }


/*
	terminal.c
	calls the terminal function.
	This is where the magic starts
*/

void	terminal(t_shell *shell, char **envp)
{
	(void)envp;
	shell->exit_code = 0;
	while (true)
	{
		g_signum = 0;
		printf("exit code in the begining of loop: %d and g_signum: %d\n", shell->exit_code, g_signum); //MO: for testing
		reset_shell(shell);
		shell_input(shell);
		// printf("exit code in the begining of loop: %d and g_signum: %d\n", shell->exit_code, g_signum); //MO: for testing
		ft_signals_interactive();
		shell->input = readline(shell->cwd);
		if (g_signum == SIGINT)
			shell->exit_code = 130;
		if (!shell->input)// Note: CTRL+D (EOF) case
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			//panic
			ft_free_env_lst(&(shell)->envp);
			free_shell(shell);
			exit(shell->exit_code);
		}
		if (input_validation(shell) == false|| !shell->input[0]) //MO: Made changes by ADEWALE plus my changes to confirm
		{
			add_history(shell->input); //MO: added
			free_shell(shell);
			continue ;
		}
		// if (!shell->input || !ft_strcmp(shell->trimmed_input, "exit"))
		// 	return (print_exit(), free_shell(shell)); //MO:exit code! exit(shell.exit_code). TO THINK ABOUT "exit" msg
		if (*shell->input)
			add_history(shell->input);
		lexer(shell, shell->trimmed_input);
		// // print_token_lst(shell->token_lst); // Printing token list
		shell->envp_arr = ft_env_arr(shell);
		shell->path = ft_path_list(shell);
		// print_path_list(shell->path);
		// print_env_arr(shell); //Print array of env.
		shell->root = build_ltree(shell, shell->token_lst);
		print_bst(shell->root, 5);
		// ft_start_execution(shell);
		// printf("exit status after execution %d\n", shell->exit_code); //MO: for testing
		// // Build and execute the cmd tree
		// /*section to call test functions to print out token and command lists*/
		// // lexec_tree(shell, shell->root);
		free_shell(shell);
		// last_process(0); //Handles the last process in the pipeline.
	}
}

void	free_shell(t_shell *shell)
{
	// int	i;

	// i = 0;
	ft_lstclear(&shell->token_lst, del_token);
	// if (shell->envp_arr)
	// {
	// 	while (shell->envp_arr[i])
	// 		free(shell->envp_arr[i++]);
	// 	free(shell->envp_arr);
	// }
	ft_free_str_arr(shell->envp_arr, ft_arr_size(shell->envp_arr)); //MO: added
	ft_lstclear(&shell->path, free);
	if (shell->input)
		free(shell->input);
	if (shell->trimmed_input)
		free(shell->trimmed_input);
	if (shell->cmd_path)
		free(shell->cmd_path);
	if (shell->root)
		ltree_free(shell->root);
	if (shell->cwd)
		free(shell->cwd);
	ft_lstclear(&(shell)->heredoc_names, &ft_unlink_heredoc);  //MO: added
	reset_shell(shell);
}

bool	is_env_empty(t_shell *shell)
{
	return (shell->envp == NULL || ft_lstsize(shell->envp) == 0);
}

void	reset_shell(t_shell *shell)
{
	shell->envp_arr = NULL;
	shell->path = NULL;
	shell->token_lst = NULL;
	shell->input = NULL;
	shell->trimmed_input = NULL;
	shell->cmd_path = NULL;
	shell->cwd = NULL;
	shell->root = NULL;
	shell->heredoc_names = NULL; //MO: added
	// shell->exit_code = 0; MO: moved up, we need exit code for the next loop iteration and for exit from minishell
	//shell.envp = NULL???
}
