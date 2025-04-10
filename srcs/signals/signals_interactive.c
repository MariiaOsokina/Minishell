/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_interactive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:40:26 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/10 18:33:01 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_interact_handler(int signo);
static void	ft_sigint_heredoc_handler(int signo);

void	ft_signals_interactive(void)
{
	ft_termios_echoctl(true);
	ft_termios_echo(true);
	signal(SIGINT, ft_sigint_interact_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signals_heredoc(void)
{
	ft_termios_echoctl(true);
	signal(SIGINT, ft_sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	ft_sigint_interact_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signum = signo;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ft_sigint_heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_termios_echo(false);
		ioctl(0, TIOCSTI, "\n");
		g_signum = signo;
		ft_termios_echo(true);
	}
}
