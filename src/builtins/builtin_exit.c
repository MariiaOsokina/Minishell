/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:30 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/07 11:05:42 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

/*TO BE SOLVED:
1- add panic function;
*/

/*
1 - Put to STDERR!!! message “exit\n”;
2 - If only command exit (w/o arguments), then panic() and exit() 
with saved exit_code from the last command executed;
3 - if 1st arg exist:
	- get exit code (number) from arg1
	- check if 1st arg is not numeric (with no digits or >LONG_MAX), then 
		(a)error message  "numeric argument required" and panic() 
		and exit() with exit code 2;
	- check if 2st arg exists, then (a) STDERR “too many arguments”, 
		(b)exit status should be 1 and 
		(c)just!!!! return (not exit from process);
	- else - panic() and exit() with exit code getted from 1st arg;
*/

static bool	ft_is_numeric(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

/*skip spaces and get sign*/
static void	ft_handle_space_and_sign(char *s, int *nbr, int *sign)
{
	while (s[*nbr] && s[*nbr] == ' ')
		(*nbr)++;
	if (s[*nbr] == '+' || s[*nbr] == '-')
	{
		if (s[*nbr] == '-')
			*sign *= -1;
		(*nbr)++;
	}
}

static int	get_exit_code(char *exit_arg)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;

	i = 0;
	sign = 1;
	ft_handle_space_and_sign(exit_arg, &i, &sign);
	if (!ft_is_numeric(exit_arg + i))
	{
		return (-1);
	}
	result = 0;
	while (exit_arg[i])
	{
		result = (result * 10) + (exit_arg[i] - '0');
		if (result > LONG_MAX)
			return (-1);
		i++;
	}
	return ((result * sign) % 256);
}

int	builtin_exit(t_shell shell, t_node *cmd)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->expanded_args[1])
		exit_code = shell.exit_code;
	else
	{
		exit_code = get_exit_code(cmd->expanded_args[1]);
		if (exit_code == -1)
		{
			ft_err_msg("exit", cmd->expanded_args[1], \
			"numeric argument required");
			exit_code = STDERR_FILENO;
		}
		if (cmd->expanded_args[2])
		{
			ft_err_msg("exit", cmd->expanded_args[2], \
			"too many arguments");
			shell.exit_code = ENO_GENERAL;
			return (shell.exit_code);
		}
	}
	//panic()
	exit(exit_code);
}
