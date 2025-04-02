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
	while (true)
	{
		g_signum = 0;
		// printf("exit code in the begining of loop: %d and g_signum: %d\n", shell->exit_code, g_signum); //MO: for testing
		reset_shell(shell);
		shell_input(shell);
		// printf("exit code in the begining of loop: %d and g_signum: %d\n", shell->exit_code, g_signum); //MO: for testing
		ft_signals_interactive();
		ft_termios_change(true);
		shell->input = readline(shell->cwd);
		if (g_signum == SIGINT)
			shell->exit_code = 130;
		if (!shell->input)//MO: moved up! exit is deleted as it is a builtin function
			return (print_exit(), free_shell(shell)); //MO:exit code! exit(shell.exit_code)
		if (shell->input[0] && !input_validation(shell))
		{
			free_shell(shell);
			continue ;
		}
		// if (!shell->input || !ft_strcmp(shell->trimmed_input, "exit"))
		// 	return (print_exit(), free_shell(shell)); //MO:exit code! exit(shell.exit_code)
		if (*shell->input)
			add_history(shell->input);
		lexer(shell, shell->trimmed_input);
		// print_token_lst(shell->token_lst); // Printing token list
		shell->envp_arr = envp; //MO: added, need to be changed
		// shell->envp_arr = env_arr(shell);
		shell->path = path_list(shell, envp);
		// print_path_list(shell->path);
		// print_env_arr(shell); //Print array of env.
		shell->root = build_ltree(shell, shell->token_lst);
		// print_bst(shell->root, 5);
		ft_start_execution(shell);
		if (g_signum == SIGINT)
			shell->exit_code = 130;
		printf("exit status after execution %d\n", shell->exit_code);
		// Build and execute the cmd tree
		/*section to call test functions to print out token and command lists*/
		// lexec_tree(shell, shell->root);
		// free_shell(shell);
		// last_process(0); //Handles the last process in the pipeline.
	}
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	ft_lstclear(&shell->token_lst, del_token);
	if (shell->envp_arr)
	{
		while (shell->envp_arr[i])
			free(shell->envp_arr[i++]);
		free(shell->envp_arr);
	}
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
	if (!shell->exit_code) //MO: added
		shell->exit_code = 0;
}
