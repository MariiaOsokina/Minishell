/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 00:24:25 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/29 23:30:25 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_remove_arg_from_av(char **av, int index)
{
	int		i;
	int		j;
	char	**new_av;

	if (!av)
		return (NULL);
	new_av = ft_calloc(ft_arr_size(av), sizeof(char *));
	if (!new_av)
		return (NULL);
	i = 0;
	j = 0;
	while (av[i])
	{
		if (i != index)
			new_av[j++] = av[i];
		else
			free(av[i]);
		i++;
	}
	free(av);
	return (new_av);
}

int	ft_match_count(const char *pattern)
{
	int				match_count;
	DIR				*dir;
	struct dirent	*entry;
	int				pattern_starts_with_dot;

	match_count = 0;
	pattern_starts_with_dot = (pattern[0] == '.');
	dir = opendir(".");
	if (!dir)
		return (-1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!pattern_starts_with_dot && entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (ft_match_pattern(pattern, entry->d_name))
			match_count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (match_count);
}

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

char	*ft_handle_env_expand(t_shell *shell, char *word, size_t *i)
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

void	ft_skip_word(char const *s, size_t *i)
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
