/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:32:01 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 17:32:07 by aaladeok         ###   ########.fr       */
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
