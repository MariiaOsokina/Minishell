/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:38:31 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/26 01:21:01 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_quote_removal(const char *word)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*new_word;

// 	i = 0;
// 	j = 0;
// 	if (!word)
// 		return (NULL);
// 	new_word = malloc(ft_strlen((char *)word) + 1);
// 	if (!new_word)
// 		return (NULL);
// 	while (word[i])
// 	{
// 		if (word[i] == '\'')
// 		{
// 			i++;
// 			while (word[i] && word[i] != '\'')
// 				new_word[j++] = word[i++];
// 			if (word[i] == '\'') i++; // skip closing '

// 		}
// 		else if (word[i] == '\"')
// 		{
// 			i++;
// 			while (word[i] && word[i] != '\"')
// 				new_word[j++] = word[i++];
// 			if (word[i] == '\"') i++; // skip closing '
// 		}
// 		else
// 			new_word[j++] = word[i++];
// 	}
// 	new_word[j] = '\0';
// 	return (new_word);
// }

static void	ft_skip_single_quotes(const char *word, size_t *i, char *new_word, size_t *j)
{
	(*i)++; // Skip opening '
	while (word[*i] && word[*i] != '\'')
		new_word[(*j)++] = word[(*i)++];
	if (word[*i] == '\'')
		(*i)++; // Skip closing '
}

static void	ft_skip_double_quotes(const char *word, size_t *i, char *new_word, size_t *j)
{
	(*i)++; // Skip opening "
	while (word[*i] && word[*i] != '\"')
		new_word[(*j)++] = word[(*i)++];
	if (word[*i] == '\"')
		(*i)++; // Skip closing "
}

char	*ft_quote_removal(const char *word)
{
	size_t	i;
	size_t	j;
	char	*new_word;

	if (!word)
		return (NULL);
	new_word = malloc(ft_strlen((char *)word) + 1);
	if (!new_word)
		return (NULL);

	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			ft_skip_single_quotes(word, &i, new_word, &j);
		else if (word[i] == '\"')
			ft_skip_double_quotes(word, &i, new_word, &j);
		else
			new_word[j++] = word[i++];
	}
	new_word[j] = '\0';
	return (new_word);
}
