/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_noninteractive.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:41:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/02 02:31:38 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signals_noninteractive(void)
{
	signal(SIGINT, ft_sigint_noninteract_handler);
	signal(SIGQUIT, ft_siguit_noninteract_handler);
}

void	ft_sigint_noninteract_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signum = signo;
	}
}

void	ft_siguit_noninteract_handler(int signo)
{
	if (signo == SIGQUIT)
	{
		g_signum = signo;
	}
}

// void	ft_signals_noninteractive(void)
// {
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// }

int		ft_termios_change(bool echo_ctl_chr)
{
	struct termios	terminos_p;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (ENO_GENERAL);
	if (echo_ctl_chr)
		terminos_p.c_lflag |= ECHOCTL;
	else
		terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (ENO_GENERAL);
	return (0);
}



