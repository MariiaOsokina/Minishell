/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_noninteractive.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:41:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/23 11:04:45 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_siquit_noninteract_handler(int signo)
{
	if (signo == SIGINT)
		g_signum = signo;
	if (signo == SIGQUIT)
		g_signum = signo;
}

void	ft_signals_noninteractive(void)
{
	ft_termios_echo(true);
	ft_termios_echoctl(false);
	signal(SIGINT, ft_sigint_siquit_noninteract_handler);
	signal(SIGQUIT, ft_sigint_siquit_noninteract_handler);
}
