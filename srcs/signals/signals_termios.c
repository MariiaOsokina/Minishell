/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_termios.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:22:47 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/10 18:34:35 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This function modifies the terminal settings to enable 
or disable the ECHOCTL flag. 
The ECHOCTL flag in terminal settings controls 
whether control characters are echoed as visible characters. 
When ECHOCTL is enabled, control characters (like Ctrl+C and CTRL+\)
 are displayed as ^C and ^\ in the terminal. 
When it is disabled, these characters are not displayed.
*/

int	ft_termios_echoctl(bool echo_ctl_chr)
{
	struct termios	termios_settings;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &termios_settings);
	if (status == -1)
		return (ENO_GENERAL);
	if (echo_ctl_chr)
		termios_settings.c_lflag |= ECHOCTL;
	else
		termios_settings.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &termios_settings);
	if (status == -1)
		return (ENO_GENERAL);
	return (0);
}

/*
This function modifies the terminal settings to enable 
or disable the ICANON and ECHO flag. 
ICANON: This flag enables canonical mode, where input 
is processed line by line. 
In canonical mode, input is buffered until a newline 
character is received, 
and special characters like backspace are handled by the terminal.

ECHO: This flag controls whether input characters 
are echoed back to the terminal. 
If ECHO is enabled, characters typed by the user are displayed on the screen.
 If it is disabled, input characters are not displayed.
*/

int	ft_termios_echo(bool echo)
{
	struct termios	termios_settings;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &termios_settings);
	if (status == -1)
		return (ENO_GENERAL);
	if (echo == true)
	{
		termios_settings.c_lflag &= ~ICANON;
		termios_settings.c_lflag |= ECHO;
	}
	else
	{
		termios_settings.c_lflag |= ICANON;
		termios_settings.c_lflag &= ~ECHO;
	}
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &termios_settings);
	if (status == -1)
		return (ENO_GENERAL);
	return (0);
}
