/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_interactive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:40:26 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/01 01:28:45 by mosokina         ###   ########.fr       */
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
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signum = signo;
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
	if (signo == SIGINT)
	{
		g_signum = signo;
		ioctl(0, TIOCSTI, "\n");
	}
}
