/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_noninteractive.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:41:16 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/31 23:44:01 by mosokina         ###   ########.fr       */
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
		ft_putstr_fd("^C\n", STDERR_FILENO);
		exit(2);
	}
}

void	ft_siguit_noninteract_handler(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		exit(3);
	}
}
