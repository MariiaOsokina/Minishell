/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:18:01 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/26 02:21:36 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_skip_word(char const *s, size_t	*i)
{
	char	quotes;

	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] != '\'' && s[*i] != '"')
			(*i)++;
		else
		{
			quotes = s[(*i)++];
			while (s[(*i)] != quotes)
				(*i)++;
			(*i)++;
		}
	}
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
	// printf("test: count words in splitting: %ld\n", word_count);
	return (word_count);
}

static char	**ft_words_alloc(char const *s, char **new_arr)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			start = i;
			ft_skip_word(s, &i);
			new_arr[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!new_arr[j])
			{
				while (j-- > 0)
					free(new_arr[j]);
				free(new_arr);
				return (NULL);
			}
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (new_arr);
}

char	**ft_expand_word_split(char const *word)
{
	size_t	word_count;
	char	**new_arr;

	if (!word)
		return (NULL);
	word_count = ft_count_words(word);
	if (word_count == 0)
		return (NULL);
	new_arr = ft_calloc(word_count + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	new_arr = ft_words_alloc(word, new_arr);
	if (!new_arr)
		return (NULL);
	new_arr = ft_fill_arr(word, new_arr);
	return (new_arr);
}
