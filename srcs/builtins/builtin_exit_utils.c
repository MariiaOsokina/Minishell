/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:57:08 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/30 00:25:45 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_get_exit_code(char *exit_arg)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	if (exit_arg[0] == '\0')
		return (-1);
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
