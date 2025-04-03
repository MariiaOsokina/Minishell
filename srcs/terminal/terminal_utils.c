#include "minishell.h"

/*
	This function concatenates a series of textual info and
	saves it in the shell cwd which is display in by the shell prompt.
	The shell prompt displays the texts concatenated in this function.
*/
void	shell_input(t_shell *shell)
{
	char	*cwd;
	char	*tmp;
	char	*tmp2;
	char	*code;
	char	*prompt;

	code = ft_itoa(exit_code(-1));
	cwd = getcwd(NULL, 0);
	prompt = ESC_START PROMPT ESC_RESET;
	tmp = ft_strjoin(prompt, code);
	free(code);
	if (!tmp)
		exit_failure(shell, "shell_input");
	tmp2 = ft_strjoin(tmp, ESC_CODE);
	free(tmp);
	if (!tmp2)
		exit_failure(shell, "shell_input");
	tmp = ft_strjoin(tmp2, cwd);
	free(tmp2);
	if (!tmp)
		exit_failure(shell, "shell_input");
	shell->cwd = ft_strjoin(tmp, ARROW);
	free(cwd);
	free(tmp);
}

/*
Will be used in exec???
int	handle_exec_node(t_shell *shell, void *root, int *status)
{
	t_exec	*exec;

	exec = NULL;
	if (((t_node *)root)->type == N_EXEC)
	{
		exec = (t_exec *)root;
		if (is_parent_builtin(exec))
		{
			exec->av = expand_av(shell, exec->av);
			exec_parent_builtin(shell, exec);
			free_expanded(exec->av);
			return (1);
		}
		else
		{
			if (fork() == 0)
				exec_tree(shell, root);
			waitpiad(-1, status, 0);
			return (1);
		}
	}
	return (0);
}

void	exec_processes(t_shell *shell, void *root)
{
	int	status;

	status = 0;
	set_main_signals();
	handle_heredoc();
	if (handle_exec_node(shell, root, &status))
		return ;
	if (fork() == 0)
		exec_tree(shell, root);
	waitpid(-1, &status, 0);
	exit_status(status);
}
*/
