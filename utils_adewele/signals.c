#include "minishell.h"

void	sig_main(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit_code(130);
	}
}


void	sig_pipe(int signo)
{
	if (signo == SIGPIPE)
	{
		//Look into this later
		//SIG_IGN can play the same role if thos does not require explicit handling.
	}
}

void	set_main_signals(void)
{
	signal(SIGINT, SIG_IGN); //We ignore interruption signal in the main process.
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, sig_pipe);
}

void	set_fork1_signal(void)
{
	signal(SIGINT, SIG_DFL);//SIG_DFL resets response to default.
	signal(SIGQUIT, SIG_DFL);
}

void	handle_signals(void)
{
	signal(SIGINT, sig_main);
	signal(SIGQUIT, SIG_IGN);
}


// static void	ft_sigint_handler(int num)
// {
// 	(void)num;
// 	if (g_minishell.signint_child)
// 	{
// 		ft_putstr_fd("\n", 1);
// 		g_minishell.signint_child = false;
// 		g_minishell.heredoc_sigint = true;
// 	}
// 	else
// 	{
// 		ft_putstr_fd("\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	ft_sigquit_handler(int num)
// {
// 	(void)num;
// 	ft_putstr_fd("Quit: 3\n", 1);
// }

// void	ft_init_signals(void)
// {
// 	struct termios	term;

// 	term = g_minishell.original_term;
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// 	g_minishell.heredoc_sigint = false;
// 	g_minishell.signint_child = false;
// 	signal(SIGINT, ft_sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }
