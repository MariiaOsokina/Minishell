#include "minishell.h"

void	exit_failure(t_shell *shell, char *info) //MO: for malloc errors?
{
	// free_env_lst(shell->envp);
	if (shell->envp != NULL)
		ft_lstclear(&shell->envp, ft_free_env_node);
	free_shell(shell);
	ft_putstr_fd(RED"malloc error: "DFLT, 2);
	ft_putendl_fd(info, 2);
	exit(1);
}
