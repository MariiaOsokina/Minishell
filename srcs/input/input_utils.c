/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:30:06 by aaladeok          #+#    #+#             */
/*   Updated: 2025/04/30 17:26:08 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	check_line_len(char *line)
{
	if (ft_strlen(line) > 400)
		return (ft_putendl_fd(LINE_ERROR, 2), false);
	return (true);
}

void	balance_message(int balance)
{
	if (balance < 0)
		ft_putendl_fd(CLOSE_ERROR, 2);
	else if (balance > 0)
		ft_putendl_fd(OPEN_ERROR, 2);
}

bool	handle_paren(char c, int *bal)
{
	if (c == '(')
		(*bal)++;
	else if (c == ')')
	{
		if (*bal == 0)
			return (false);
		(*bal)--;
	}
	return (true);
}

bool	check_empty_parens(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(' && str[i + 1] == ')')
			return (true);
		if (str[i] == ')')
		{
			if (i > 0 && str[i - 1] == '(')
				return (true);
			if (str[i + 1] == '(')
				return (true);
		}
		i++;
	}
	return (false);
}
