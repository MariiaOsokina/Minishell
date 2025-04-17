#include "minishell.h"

/*
	terminal.c
	calls the terminal function.
	This is where the magic starts
*/

void	terminal(t_shell *shell)
{
	while (true)
	{
		// printf("exit code in the begining of loop: %d and g_signum: %d\n", shell->exit_code, g_signum); //MO: for testing
		reset_shell(shell);
		shell_input(shell);
		ft_signals_interactive();
		shell->input = readline(shell->cwd);
		if (g_signum == SIGINT)
			shell->exit_code = 130;
		if (!shell->input)// Note: CTRL+D (EOF) case
		{
			// ft_putstr_fd("exit\n", STDERR_FILENO); //MO: reset, muted for testing
			ft_exit_with_full_cleanup(shell, shell->exit_code);
		}
		add_history(shell->input);
		if (input_validation(shell) == true || !shell->input[0]) //MO: Made changes by ADEWALE plus my changes to confirm
		{
			free_shell(shell);
			continue ;
		}
		lexer(shell, shell->trimmed_input);
		// // print_token_lst(shell->token_lst); // Printing token list
		shell->envp_arr = ft_env_arr(shell, shell->envp);
		shell->path = ft_path_list(shell);
		// print_path_list(shell->path);
		// print_env_arr(shell); //Print array of env.
		shell->root = build_ltree(shell, shell->token_lst);
		// print_bst(shell->root, 5);
		ft_process_av(shell, shell->root);
		ft_start_execution(shell);
		// printf("exit status after execution %d\n", shell->exit_code); //MO: for testing
		free_shell(shell);
	}
}

void	free_shell(t_shell *shell) //it should not free evp list
{
	// int	i;

	// i = 0;
	if (shell->token_lst != NULL)
		ft_lstclear(&shell->token_lst, del_token);
	// if (shell->envp_arr)
	// {
	// 	while (shell->envp_arr[i])
	// 		free(shell->envp_arr[i++]);
	// 	free(shell->envp_arr);
	// }
	ft_free_str_arr(shell->envp_arr, ft_arr_size(shell->envp_arr)); //MO: added
	if (shell->path != NULL)
		ft_lstclear(&shell->path, free);
	if (shell->heredoc_names !=NULL)
		ft_lstclear(&shell->heredoc_names, free);
//MO: added
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
	reset_shell(shell);
}

// bool	is_env_empty(t_shell *shell)
// {
// 	return (shell->envp == NULL || ft_lstsize(shell->envp) == 0);
// }

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
	shell->heredoc_names = NULL;
	shell->in_child = false; //MO: added
	// shell->exit_code = 0; MO: moved up, we need exit code for the next loop iteration and for exit from minishell
	//shell.envp = NULL???
	g_signum = 0;
}
