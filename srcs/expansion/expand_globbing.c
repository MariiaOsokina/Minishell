/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_globbing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 23:40:03 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/26 02:41:55 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_match_pattern(const char *pattern, const char *filename)
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

static void	ft_sort_alphabetical(char **arr, int size)
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

// void ft_fill_filenames_arr(const char *pattern, char **filenames)
// {
// 	DIR *dir;
// 	struct dirent *entry;
// 	int count = 0;

// 	if (!filenames)
// 		return;

// 	dir = opendir(".");
// 	if (!dir)
// 		return;

// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		if (entry->d_name[0] != '.' && ft_match_pattern(pattern, entry->d_name))
// 			filenames[count++] = ft_strdup(entry->d_name);
// 	}
// 	filenames[count] = NULL;
// 	closedir(dir);
// 	ft_sort_alphabetical(filenames, ft_arr_size(filenames));
// }

void ft_fill_filenames_arr(const char *pattern, char **filenames)
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;
    int pattern_starts_with_dot;
	
	pattern_starts_with_dot= (pattern[0] == '.');
    if (!filenames)
        return;
    dir = opendir(".");
    if (!dir)
        return;
    while ((entry = readdir(dir)) != NULL)
    {
        if (!pattern_starts_with_dot && entry->d_name[0] == '.')
            continue;
        if (ft_match_pattern(pattern, entry->d_name))
            filenames[count++] = ft_strdup(entry->d_name);
    }
    filenames[count] = NULL;
    closedir(dir);
    ft_sort_alphabetical(filenames, ft_arr_size(filenames));
}

void	ft_globbing_in_arg(t_exec *exec_node, int i)
{
	char	*tmp_quoted_removed;
	int		match_count;
	char	**filenames;

	tmp_quoted_removed = ft_quote_removal(exec_node->av[i]);
	match_count = ft_match_count(tmp_quoted_removed);
	if (match_count > 0)
	{
		filenames = ft_calloc(match_count + 1, sizeof(char *));
		if (filenames)
		{
			ft_fill_filenames_arr(tmp_quoted_removed, filenames);
			if (filenames)
			{
				exec_node->av = ft_replace_args(exec_node->av, filenames, i);
				ft_free_str_arr(filenames, ft_arr_size(filenames));
			}			
		}
	}
	free(tmp_quoted_removed);
}
