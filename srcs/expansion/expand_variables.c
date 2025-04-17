/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:37:19 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/17 19:41:48 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_f(char *s1, char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	new_str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	free(s1);
	free(s2);
	return (new_str);
}

static char *ft_handle_env_expand(t_shell *shell, char *word, size_t *i)
{
	size_t	start;
	t_env	*tmp_env;
	char	*var;

	(*i)++;
	start = *i;
	if (word[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_code));
	}
	while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
		(*i)++;

	if (*i == start)
		return (ft_strdup("$"));
	var = ft_substr(word, start, *i - start);
	if (var)
	{
		tmp_env = ft_get_env_node(*shell, var);
		free(var);
		if (tmp_env && tmp_env->value)
			return (ft_strdup(tmp_env->value));
	}
	return (ft_strdup(""));
}

static char	*ft_handle_dquote_str(char *word, size_t *i)
{
	size_t	start;
	char *ret;

	start = *i;
	while (word[*i] != '"' && word[*i] != '$')
		(*i)++;
	ret = ft_substr(word, start, *i - start);
	return (ret);
}

char	*ft_handle_squotes(char *word, size_t *i)
{
	size_t	start;
	char *ret;

	start = *i;
	(*i)++;
	while (word[*i] != '\'')
		(*i)++;
	(*i)++;
	ret = ft_substr(word, start, *i - start);
	return (ret);
}

char	*ft_handle_normal_str(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_dquotes(t_shell *shell, char *word, size_t *i)
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
	char *new_word;

	i = 0;
	new_word = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '\'')
			new_word = ft_strjoin_f(new_word, ft_handle_squotes(word, &i));
		else if (word[i] == '\"')
			new_word = ft_strjoin_f(new_word, ft_handle_dquotes(shell, word, &i));
		// else if (word[i] == '$' && (word[i++] == '\'' || word[i++] == '\"'))
		// 	i += 1; //just skip $
		else if (word[i] == '$')
			new_word = ft_strjoin_f(new_word, ft_handle_env_expand(shell, word, &i));
		else
			new_word = ft_strjoin_f(new_word, ft_handle_normal_str(word, &i));
	}
	return (new_word);
}
