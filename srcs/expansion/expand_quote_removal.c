/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_removal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:38:31 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/29 23:36:05 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_single_quotes(const char *w, size_t *i, char *new_w, size_t *j)
{
	(*i)++;
	while (w[*i] && w[*i] != '\'')
		new_w[(*j)++] = w[(*i)++];
	if (w[*i] == '\'')
		(*i)++;
}

void	ft_skip_double_quotes(const char *w, size_t *i, char *new_w, size_t *j)
{
	(*i)++;
	while (w[*i] && w[*i] != '\"')
		new_w[(*j)++] = w[(*i)++];
	if (w[*i] == '\"')
		(*i)++;
}

char	*ft_quote_removal(const char *word)
{
	size_t	i;
	size_t	j;
	char	*new_word;

	i = 0;
	j = 0;
	if (!word)
		return (NULL);
	if (word[i] == '$' && ft_strcmp(&word[i], "$") != 0)
		i++;
	new_word = malloc(ft_strlen((char *)word) + 1);
	if (!new_word)
		return (NULL);
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
