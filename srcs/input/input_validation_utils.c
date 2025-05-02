/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:25:34 by mosokina          #+#    #+#             */
/*   Updated: 2025/05/02 11:25:56 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_invalid_pipeseq(char *s, int *i, bool *in_single, bool *in_double)
{
	if (s[*i] == '|' && s[*i + 1] != '|' && !*in_single && !*in_double)
	{
		(*i)++;
		while (is_space(s[*i]))
			(*i)++;
		if (s[*i] == '|' && s[*i + 1] != '|')
			return (true);
	}
	else
		(*i)++;
	return (false);
}

bool	check_pipes(char *str)
{
	int		i;
	bool	in_single;
	bool	in_double;

	i = 0;
	in_single = false;
	in_double = false;
	if (str[i] == '|' && str[i + 1] != '|')
		return (false);
	if (str[strlen(str) - 1] == '|')
		return (false);
	while (str[i])
	{
		toggle_quotes(str[i], &in_single, &in_double);
		if (str[i] == '|' && str[i + 1] == '|' && str[i + 2] == '|')
			return (false);
		if (is_invalid_pipeseq(str, &i, &in_single, &in_double))
			return (false);
	}
	return (true);
}
