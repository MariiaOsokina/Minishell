/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:18:01 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/17 10:38:07 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Purpose: Moves the index i past a "word", considering quotes.

A "word" ends at a space unless it’s enclosed in quotes.

If it sees ' or ", it skips everything inside the quotes too.
*/


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

/*
Purpose: Allocates memory for each word in the result array.

It loops through the string word.

For every word it finds, it calculates its length (using ft_skip_word) and allocates memory for it using ft_calloc.
*/

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


/*
Purpose: Fills the already-allocated new_arr[j] with the actual word from s.

It handles quoted strings just like before.

It copies characters into the string, including the quotes.
*/
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

/*
Purpose: Goes through s again and fills all allocated strings using ft_fill_words.

It's essentially the final population of the strings after allocation.
*/

static char	**ft_fill_arr(char const *word, char **new_arr)
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

/*
Purpose: Main function for word splitting.

Counts words.

Allocates space.

Fills the strings.

Returns the array of split words.*/

#include <stddef.h>  // for size_t
#include <stdlib.h>  // for malloc, calloc

// Function to count the number of words in the input string
size_t ft_count_words(const char *word)
{
    size_t word_count;
    size_t i;

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

// Refactored main function
char **ft_expand_word_split(char const *word)
{
    size_t word_count;
    char **new_arr;

    if (!word)
        return NULL;

    word_count = ft_count_words(word);
    if (word_count == 0)
        return NULL;

    new_arr = ft_calloc(word_count + 1, sizeof(char *));
    if (!new_arr)
        return NULL;

    new_arr = ft_words_alloc(word, new_arr);  // Allocate memory for each word
    if (!new_arr)
        return NULL;

    new_arr = ft_fill_arr(word, new_arr);     // Fill each word's content
    return new_arr;
}
