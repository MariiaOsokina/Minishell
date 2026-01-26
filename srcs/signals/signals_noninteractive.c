/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_noninteractive.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:41:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/05/02 10:49:26 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_termios_echo_nonint(bool canon)
{
	struct termios	termios_settings;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &termios_settings);
	if (status == -1)
		return (ENO_GENERAL);
	if (canon == true)
	{
		termios_settings.c_lflag |= ICANON;
		termios_settings.c_lflag |= ECHO;
	}
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &termios_settings);
	if (status == -1)
		return (ENO_GENERAL);
	return (0);
}

static void	ft_sigint_siquit_noninteract_handler(int signo)
{
	if (signo == SIGINT)
		g_signum = signo;
	if (signo == SIGQUIT)
		g_signum = signo;
}

void	ft_signals_noninteractive(void)
{
	ft_termios_echo_nonint(true);
	ft_termios_echoctl(false);
	signal(SIGINT, ft_sigint_siquit_noninteract_handler);
	signal(SIGQUIT, ft_sigint_siquit_noninteract_handler);
}
