/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printed_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:24:48 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 13:24:51 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_error_msg(char *str)
{
	static bool	message_printed;

	message_printed = false;
	if (!message_printed)
	{
		ft_putstr_fd(SYNTAX_ERROR, 2);
		if (str)
			ft_putendl_fd(str, 2);
		message_printed = true;
	}
	else
		message_printed = false;
	return (true);
}

void	print_exit(void)
{
	static int	value = 0;

	if (value == 0)
		ft_putstr_fd("exit\n", 1);
	value++;
}
