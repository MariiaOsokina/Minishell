/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:30 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/13 09:53:04 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

/*
tests:

exit
echo $?

exit 10
echo $?

exit -10
echo $?


exit 2929229
echo $?

exit 16767676767676767677777777777777
echo $?

echo $SHLVL
exit ab112hjh
echo $SHLVL

exit ab112hjh
echo $?

echo $SHLVL
exit 70 args
echo $SHLVL

exit 70 args
echo $?
*/

/*TO BE SOLVED:
1- add panic function;
*/

/*STEPS:
1 - Put to STDERR!!! message “exit\n”;
2 - If only command exists (w/o arguments), then panic() and exit() 
with saved exit_code from the last command executed;
3 - if 1st arg exists:
	- get exit code (number) from arg1
	- check if 1st arg is not numeric (with no digits or >LONG_MAX), then 
		(a)error message  "numeric argument required" and panic() 
		and exit() with exit code 2;
	- check if 2st arg exists, then (a) STDERR “too many arguments”, 
		(b)exit status should be 1 and 
		(c)just!!!! return (not exit from process);
	- else - panic() and exit() with exit code getted from 1st arg (modulo %256);
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

int	ft_builtin_exit(t_shell *shell, t_exec *exec_node)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!exec_node->av[1])
		exit_code = shell->exit_code;
	else
	{
		exit_code = get_exit_code(exec_node->av[1]);
		if (exit_code == -1)
		{
			ft_err_msg("exit", exec_node->av[1], \
			"numeric argument required");
			exit_code = STDERR_FILENO;
				//panic()
			exit(exit_code);
		}
		if (exec_node->av[2])
		{
			ft_err_msg("exit", exec_node->av[2], \
			"too many arguments");
			shell->exit_code = ENO_GENERAL;
			return (shell->exit_code);
		}
	}
	//panic()
	exit(exit_code);
}
