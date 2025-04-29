/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:18:01 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/29 11:45:46 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				return (free(new_arr), NULL);
			}
			j++;
		}
		while (s[i] && s[i] == ' ')
			i++;
	}
	return (new_arr);
}

static void	ft_fill_words(const char *word, char **new_arr, size_t *i, size_t j)
{
	char	quotes;
	size_t	k;

	k = 0;
	while (word[(*i)] && word[(*i)] != ' ')
	{
		if (word[(*i)] != '\'' && word[(*i)] != '"')
			new_arr[j][k++] = word[(*i)++];
		else
		{
			quotes = word[(*i)++];
			new_arr[j][k++] = quotes;
			while (word[(*i)] != quotes)
				new_arr[j][k++] = word[(*i)++];
			new_arr[j][k++] = word[(*i)++];
		}
	}
}

char	**ft_fill_arr(char const *word, char **new_arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (word[i] && new_arr[j])
	{
		if (word[i] != ' ')
		{
			ft_fill_words(word, new_arr, &i, j);
			j++;
		}
		while (word[i] && word[i] == ' ')
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
