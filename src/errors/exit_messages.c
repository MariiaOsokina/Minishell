#include "minishell.h"

void	exit_failure(t_shell *shell, char *info)
{
	free_env_lst(shell->envp);
	free_shell(shell);
	ft_putstr_fd(RED"malloc error: "DFLT, 2);
	ft_putendl_fd(info, 2);
	exit(1);
}
