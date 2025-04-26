/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:37:19 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/26 01:15:02 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_handle_dquote_str(char *word, size_t *i)
{
	size_t	start;
	char	*ret;

	start = *i;
	while (word[*i] != '"' && word[*i] != '$')
		(*i)++;
	ret = ft_substr(word, start, *i - start);
	return (ret);
}

static char	*ft_handle_squotes(char *word, size_t *i)
{
	size_t	start;
	char	*ret;

	start = *i;
	(*i)++;
	while (word[*i] != '\'')
		(*i)++;
	(*i)++;
	ret = ft_substr(word, start, *i - start);
	return (ret);
}

static char	*ft_handle_normal_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && \
		str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*ft_handle_dquotes(t_shell *shell, char *word, size_t *i)
{
	char	*ret;

	ret = ft_strdup("\"");
	(*i)++;
	while (word[*i] != '"')
	{
		if (word[*i] == '$')
			ret = ft_strjoin_f(ret, ft_handle_env_expand(shell, word, i));
		else
			ret = ft_strjoin_f(ret, ft_handle_dquote_str(word, i));
	}
	(*i)++;
	ret = ft_strjoin_f(ret, ft_strdup("\""));
	return (ret);
}

char	*ft_var_expansion(t_shell *shell, char *word)
{
	size_t	i;
	char	*new_word;

	i = 0;
	new_word = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '\'')
			new_word = ft_strjoin_f(new_word, ft_handle_squotes(word, &i));
		else if (word[i] == '\"')
			new_word = ft_strjoin_f(new_word, \
			ft_handle_dquotes(shell, word, &i));
		// else if (word[i] == '$' && (word[i++] == '\'' || word[i++] == '\"'))
		// 	i += 1; //just skip $
		else if (word[i] == '$')
			new_word = ft_strjoin_f(new_word, \
			ft_handle_env_expand(shell, word, &i)); //DELETE FROM ARGS IF ""
		else
			new_word = ft_strjoin_f(new_word, ft_handle_normal_str(word, &i));
	}
	return (new_word);
}
