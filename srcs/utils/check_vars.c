/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:42:06 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 17:42:10 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_args(int ac, char **av, char **envp)
{
	(void) av;
	if (!envp || !*envp)
		ft_putendl_fd(RED "No envp: " DFLT, 2);
	if (ac > 1)
	{
		ft_putendl_fd(RED "Invalid input" DFLT, 2);
		exit(1);
	}
	return (0);
}
