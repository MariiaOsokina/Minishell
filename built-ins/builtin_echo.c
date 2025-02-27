/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:16:04 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/27 14:31:23 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

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

int	builtin_echo(t_shell shell, t_node *cmd)
{
	char 	**echo_args;
	bool    n_op;
	int		i;

	i = 0;
	echo_args = &(cmd->expanded_args[1]);
	while ((echo_args[i] != NULL) && (ft_is_n_option(echo_args[i])))
	{
		n_op = true;
		i ++;
	}
	while (echo_args[i])
	{
		ft_putstr_fd(echo_args[i], STDOUT_FILENO);
		if (echo_args [i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i ++;
	}
	if (n_op == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (ENO_SUCCESS);
}


