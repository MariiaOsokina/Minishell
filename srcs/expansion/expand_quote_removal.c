/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:38:31 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/16 19:09:28 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_quote_removal(const char *word)
{
	size_t	i = 0;
	size_t	j = 0;
	char	*new_word;

	if (!word)
		return (NULL);
	new_word = malloc(ft_strlen((char *)word) + 1); // Result will never be longer than original
	if (!new_word)
		return (NULL);

	while (word[i])
	{
		if (word[i] == '\'')
		{
			i++; // skip opening '
			while (word[i] && word[i] != '\'')
				new_word[j++] = word[i++];
		}
		else if (word[i] == '\"')
		{
			i++; // skip opening "
			while (word[i] && word[i] != '\"')
				new_word[j++] = word[i++];
		}
		else
			new_word[j++] = word[i++];
	}
	new_word[j] = '\0';
	return (new_word);
}