#include "minishell.h"

#define del_token "To be implemented in lexer"

void	terminal(t_shell *shell, char **envp)
{
	while (true)
	{
		reset_shell(shell);
		handle_signals();
		shell_input(shell);
		shell->input = readline(shell->cwd);
		if (!shell->input || !ft_strcmp(shell->trimmed_input, "exit"))
			return (print_exit(), free_shell(shell));
		if (shell->input[0] && !input_validation(shell))
		{
			free_shell(shell);
			continue ;
		}
		if (*shell->input)
			add_history(shell->input); //Clarified!!
		lexer(shell, shell->trimmed_input); // Tokenization
		shell->envp_arr = env_arr(shell);   // Prep envs
		shell->path = path_list(shell, envp); //Prep path
		shell->root = build_ltree(shell, shell->token_lst); //Build and execute the cmd tree
		lexec_tree(shell, shell->root);
		free_shell(shell);
		last_process(0); //Handles the last process in the pipeline.
	}
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	ft_lstclear(&shell->token_lst, del_token);// TODO: In tokenization
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

void	is_env_empty(t_shell *shell)
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
	shell->exit_code = 0;
}
