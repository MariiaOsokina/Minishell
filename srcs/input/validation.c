/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:32:01 by aaladeok          #+#    #+#             */
/*   Updated: 2025/05/02 10:52:43 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_parenthesis(char *str)
{
	int		i;
	int		bal;
	bool	sq;
	bool	dq;

	i = 0;
	bal = 0;
	sq = false;
	dq = false;
	if (check_empty_parens(str))
		return (ft_putendl_fd(SYNTAX_ERROR CLOSE_ERROR, 2), (false));
	while (str[i])
	{
		toggle_quotes(str[i], &sq, &dq);
		if (!sq && !dq && !handle_paren(str[i], &bal))
			return (balance_message(-1), false);
		i++;
	}
	if (sq || dq)
		return (ft_putendl_fd(OPEN_QUOTE, 2), false);
	if (bal != 0)
		return (balance_message(bal), false);
	return (true);
}

bool	check_logical_or(char *str)
{
	int		i;
	bool	in_single;
	bool	in_double;

	i = 0;
	in_single = false;
	in_double = false;
	if (!str || (str[i] == '|' && str[i + 1] == '|'))
		return (false);
	while (str[i])
	{
		toggle_quotes(str[i], &in_single, &in_double);
		if (str[i] == '|' && str[i + 1] == '|' && !in_single && !in_double)
		{
			i += 2;
			while (is_space(str[i]))
				i++;
			if (!str[i] || (str[i] == '|' && str[i + 1] == '|'))
				return (false);
		}
		else
			i++;
	}
	return (true);
}
