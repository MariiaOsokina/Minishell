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

// void	sig_pipe(int signo)
// {
// 	if (signo == SIGPIPE)
// 	{
// 		//Look into this later
// 		//SIG_IGN can play the same role if thos does not require explicit handling.
// 	}
// }

// void	set_main_signals(void)
// {
// 	signal(SIGINT, SIG_IGN); //We ignore interruption signal in the main process.
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGPIPE, sig_pipe);
// }

// void	set_fork1_signal(void)
// {
// 	signal(SIGINT, SIG_DFL);//SIG_DFL resets response to default.
// 	signal(SIGQUIT, SIG_DFL);
// }

void	handle_signals(void)
{
	signal(SIGINT, sig_main);
	signal(SIGQUIT, SIG_IGN);
}

void ft_sigquit_handler(int signo)
{
	if (signo == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
}