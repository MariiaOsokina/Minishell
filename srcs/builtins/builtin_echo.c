/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:37:02 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/25 20:19:49 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_is_n_option(char *str)
{
	if (*str != '-')
		return (false);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

int	ft_builtin_echo(t_shell *shell, t_exec *exec_node)
{
	char	**echo_args;
	bool	n_op;
	int		i;

	(void)shell;
	i = 0;
	n_op = false;
	echo_args = &(exec_node->av[1]);
	while ((echo_args[i] != NULL) && (ft_is_n_option(echo_args[i])))
	{
		n_op = true;
		i ++;
	}
	while (echo_args[i])
	{
		ft_putstr_fd(echo_args[i], STDOUT_FILENO);
		if (echo_args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i ++;
	}
	if (n_op == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (ENO_SUCCESS);
}
