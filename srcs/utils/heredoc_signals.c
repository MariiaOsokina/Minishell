#include "minishell.h"

// t_shell	*shell_struct(t_shell *shell, int flag)
// {
// 	static t_shell	*ptr;

// 	if (flag)
// 		return (ptr);
// 	ptr = shell;
// 	return (ptr);
// }

// void	heredoc_sigint_handler(int signo)
// {
// 	const t_shell *shell = shell_struct(NULL, 1);

// 	if (signo == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		close(shell->fd);
// 		// free_env_lst(shell->envp);
// 		ft_free_env_lst(&shell->envp); //MO add
// 		free_shell((t_shell *)shell);
// 		exit_code(130);
// 		exit(130);
// 	}
// }

// void	heredoc_signal(void)
// {
// 	signal(SIGINT, heredoc_sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	heredoc_sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signum = signo;
		ioctl(0, TIOCSTI, "\n");
		// exit(130);ls
	}
}
