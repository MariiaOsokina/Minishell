/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_scan_for_asterisk.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:34:04 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/29 10:29:35 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_has_quoted_asterisk(const char *word)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			if (!quote)
				quote = word[i];
			else if (quote == word[i])
				quote = 0;
			i++;
		}
		else if (word[i] == '*' && quote != 0)
			return (true);
		else
			i++;
	}
	return (false);
}

static bool	ft_has_unquoted_asterisk(const char *word)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			if (!quote)
				quote = word[i];
			else if (quote == word[i])
				quote = 0;
			i++;
		}
		else if (word[i] == '*' && quote == 0)
			return (true);
		else
			i++;
	}
	return (false);
}

bool	ft_scan_for_asterisk(const char *word)
{
	if (ft_has_quoted_asterisk(word))
		return (false);
	return (ft_has_unquoted_asterisk(word));
}

size_t	ft_count_words(const char *word)
{
	size_t	word_count;
	size_t	i;

	word_count = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] != ' ' && ++word_count)
			ft_skip_word(word, &i);
		while (word[i] && word[i] == ' ')
			i++;
	}
	return (word_count);
}
