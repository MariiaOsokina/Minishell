/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:34:04 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/17 20:24:29 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_scan_for_asterisk(char *word)
{
    bool in_squote;
    bool in_dquote;
    size_t i = 0;

    in_squote = false;
    in_dquote = false;
    i = 0;

    while (word[i])
    {
        if (word[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        else if (word[i] == '"' && !in_squote)
            in_dquote = !in_dquote;
        else if (word[i] == '*' && !in_squote && !in_dquote)
            return (true);
        i++;
    }
    return (false);
}

bool ft_match_pattern(const char *pattern, const char *filename)
{
    if (!pattern || !filename)
        return false;
    while (*pattern)
    {
        if (*pattern == '*')
        {
            pattern++;
            if (!*pattern)
                return true;
            while (*filename)
            {
                if (ft_match_pattern(pattern, filename))
                    return true;
                filename++;
            }
            return false;
        }
        else if (*pattern != *filename)
        {
            return false;
        }
        pattern++;
        filename++;
    }
    return *pattern == '\0' && *filename == '\0';
}

//TO SPLIT

char **ft_get_filenames_arr(const char *pattern)
{
	DIR *dir;
	struct dirent *entry;
	char **filenames = NULL;
	size_t count = 0;
	size_t match_count;

	if (!pattern || !*pattern)
        return NULL;
	match_count = 0;
	dir = opendir(".");
	if (!dir)
		return NULL;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.')
			continue;
		if (ft_match_pattern(pattern, entry->d_name))
			match_count++;
	}
	closedir(dir);
	filenames = malloc(sizeof(char *) * (match_count + 1));
	if (!filenames)
		return NULL;
	count = 0;
	dir = opendir(".");
	if (!dir)
		return NULL;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.')
			continue;

		if (ft_match_pattern(pattern, entry->d_name)) {
			filenames[count] = ft_strdup(entry->d_name);
			if (!filenames[count]) {
				for (size_t i = 0; i < count; i++)
					free(filenames[i]);
				free(filenames);
				closedir(dir);
				return NULL;
			}
			count++;
		}
	}
	filenames[count] = NULL;
	closedir(dir);
	return filenames;
}
