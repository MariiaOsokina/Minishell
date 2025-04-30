/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:11:34 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 12:04:58 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal(t_shell *shell)
{
	while (true)
	{
		reset_shell(shell);
		shell_input(shell);
		ft_signals_interactive();
		shell->input = readline(shell->cwd);
		if (g_signum == SIGINT)
			shell->exit_code = 130;
		if (!shell->input)
			ft_exit_with_full_cleanup(shell, shell->exit_code);
		add_history(shell->input);
		if (input_validation(shell) == true || !shell->input[0])
		{
			free_shell(shell);
			continue ;
		}
		if (!lexer(shell, shell->trimmed_input))
			continue ;
		shell->envp_arr = ft_env_arr(shell, shell->envp);
		shell->path = ft_path_list(shell);
		shell->root = build_ast(shell);
		ft_start_execution(shell);
		free_shell(shell);
	}
}

void	free_shell(t_shell *shell) //it should not free evp list
{
	if (shell->token_lst != NULL)
		ft_lstclear(&shell->token_lst, del_token);
	ft_free_str_arr(shell->envp_arr, ft_arr_size(shell->envp_arr));
	if (shell->path != NULL)
		ft_lstclear(&shell->path, free);
	if (shell->heredoc_names != NULL)
		ft_lstclear(&shell->heredoc_names, free);
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
	shell->in_child = false;
	g_signum = 0;
}
