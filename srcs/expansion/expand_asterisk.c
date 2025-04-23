/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:34:04 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/23 14:13:17 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_scan_for_asterisk(const char *word)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (word[i])
	{
		if (!quote && (word[i] == '\'' || word[i] == '"'))
		{
			quote = word[i];
			i++;
		}
		else if (quote && word[i] == quote)
		{
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

static bool	ft_match_pattern(const char *pattern, const char *filename)
{
	if (!pattern || !filename)
		return (false);
	while (*pattern)
	{
		if (*pattern == '*')
		{
			pattern ++;
			if (!*pattern)
				return (true);
			while (*filename)
			{
				if (ft_match_pattern(pattern, filename))
					return (true);
				filename ++;
			}
			return (false);
		}
		else if (*pattern != *filename)
			return (false);
		pattern ++;
		filename ++;
	}
	return (*pattern == '\0' && *filename == '\0');
}

int	ft_match_count(const char *pattern)
{
	int				match_count;
	DIR				*dir;
	struct dirent	*entry;

	match_count = 0;
	dir = opendir(".");
	if (!dir)
		return (-1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.' && ft_match_pattern(pattern, entry->d_name))
			match_count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (match_count);
}


void	ft_sort_alphabetical(char **arr, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**ft_get_filenames_arr(const char *pattern, int match_count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**filenames;
	int				count;

	count = 0;
	filenames = malloc(sizeof(char *) * (match_count + 1));
	if (!filenames)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.' && ft_match_pattern(pattern, entry->d_name))
		{
			filenames[count] = ft_strdup(entry->d_name);
			count ++;
		}
		entry = readdir(dir);
	}
	filenames[count] = NULL;
	closedir(dir);
	for (int i = 0; i < count; i++)
		printf("Before sort: %s\n", filenames[i]);	
	ft_sort_alphabetical(filenames, ft_arr_size(filenames));
	for (int i = 0; i < count; i++)
		printf("After sort: %s\n", filenames[i]);
	return (filenames);
}
