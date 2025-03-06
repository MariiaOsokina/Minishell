/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:30 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/06 14:46:28 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"


/*TO BE SOLVED:
1- add panic function;
*/
/*
1 - Put to STDERR!!! message “exit\n”;
2 - If only command exit (w/o arguments), then exit code  is (saved in shell.exit_code) from the last command executed)
3 - if 1st arg exist:
		- get exit code (number) from arg1 and check if  1st arg is not numeric (with no digits or >LONG_MAX), then (a)error message  "numeric argument required" then exit code 2);
		- check if 2st arg exists, then (a) STDERR “too many arguments”, (b)exit status should be 1 and (c)just!!!! return (not exit from process);
4 - panic() and exit() with exit code
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

int	builtin_exit(t_shell shell, t_node *cmd)
{
    int	exit_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->expanded_args[1])
		exit_code = shell.exit_code;
	else
	{
		exit_code = get_exit_code(cmd->expanded_args[1]);
		if (exit_code = -1)
		{
			ft_err_msg("exit", cmd->expanded_args[1], "numeric argument required");
			exit_code = STDERR_FILENO; //2
		}
		if (cmd->expanded_args[2])
		{
			ft_err_msg("exit", cmd->expanded_args[1], "too many arguments");
			shell.exit_code = ENO_GENERAL; //1
			return (shell.exit_code);
		}
	}
		//panic()
		exit(exit_code);
}


static void	ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

static int	get_exit_code(char *s)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;

	i = 0;
	sign = 1;
	ft_skip_spaces_and_get_sign(s, &i, &sign);
	if (!ft_isnumber(s + i))
	{
		return (-1);
	}
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > LONG_MAX)
		{
			return (-1);
		}
		i++;
	}
	return ((result * sign) % 256);
}