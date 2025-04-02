/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_interactive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:40:26 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/02 13:32:30 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signals_interactive(void)
{
	signal(SIGINT, ft_sigint_interact_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sigint_interact_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signum = signo;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// ioctl(0, TIOCSTI, "\n");
	}
}

void	ft_signals_heredoc(void)
{
	signal(SIGINT, ft_sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sigint_heredoc_handler(int signo)
{
	// int tmpstdin;
	// tmpstdin = dup(STDIN_FILENO);
	if (signo == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		// close(STDIN_FILENO);
		// ft_termios_notecho(); //test!!! it is needed that it indicates a newline should be processed, but not printed.
		g_signum = signo;
		// open(tmpstdin, O_RDONLY);
	}
}


// The ICANON and ECHO flags are part of the terminal's local modes, which control how input is processed.

// ICANON: This flag enables canonical mode, where input is processed line by line. 
// In canonical mode, input is buffered until a newline character is received, and special characters like backspace are handled by the terminal.

// ECHO: This flag controls whether input characters are echoed back to the terminal. 
// If ECHO is enabled, characters typed by the user are displayed on the screen.
//  If it is disabled, input characters are not displayed.

// In your function, ICANON is enabled, and ECHO is disabled. 
// This means input is processed line by line, but characters are not echoed back to the terminal.

// int		ft_termios_notecho(void)
// {
// 	struct termios	terminos_p;
// 	int				status;

// 	status = tcgetattr(STDOUT_FILENO, &terminos_p);
// 	if (status == -1)
// 		return (ENO_GENERAL);

// 	terminos_p.c_lflag |= ICANON;
// 	terminos_p.c_lflag &= ~ECHO;
	
// 	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
// 	if (status == -1)
// 		return (ENO_GENERAL);
// 	return (0);
// }

// int		ft_termios_echo(void)
// {
// 	struct termios	terminos_p;
// 	int				status;

// 	status = tcgetattr(STDOUT_FILENO, &terminos_p);
// 	if (status == -1)
// 		return (ENO_GENERAL);

// 	terminos_p.c_lflag &= ~ICANON;
// 	terminos_p.c_lflag |= ECHO;
	
// 	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
// 	if (status == -1)
// 		return (ENO_GENERAL);
// 	return (0);
// }
