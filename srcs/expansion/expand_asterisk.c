/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:34:04 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/17 12:02:19 by mosokina         ###   ########.fr       */
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


// bool ft_scan_for_asterisk(char *word)
// {
//     bool in_squote = false;
//     bool in_dquote = false;
//     size_t i = 0;

//     while (word[i])
//     {
//         if (word[i] == '\'' && !in_dquote)
//             in_squote = !in_squote;
//         else if (word[i] == '"' && !in_squote)
//             in_dquote = !in_dquote;
//         else if (word[i] == '*' && !in_squote && !in_dquote)
//             return true;
//         i++;
//     }
// 	printf("false\n");
//     return false;
// }

bool ft_match_pattern(const char *pattern, const char *filename)
{
    if (!pattern || !filename)
        return false;

    // Handle '*' as "any sequence of characters"
    while (*pattern)
    {
        if (*pattern == '*')
        {
            pattern++;
            if (!*pattern)
                return true; // '*' at end filenames everything

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

// char **ft_get_filenames_arr(const char *pattern)
// {
//     DIR *dir;
//     struct dirent *entry;
//     char **filenames;
//     size_t count;
//     char *tmp_file;

//     filenames = NULL;
//     count = 0;

//     dir = opendir(".");
//     if (!dir)
//         return NULL;
//     while ((entry = readdir(dir)) != NULL)
//     {
//         if (entry->d_name[0] == '.')
//             continue; // skip hidden files

//         if (ft_match_pattern(pattern, entry->d_name))
//         {
//             tmp_file = realloc(filenames, sizeof(char *) * (count + 2)); //realloc??
//             if (!tmp_file)
//             {
//                 // cleanup
//                 while (count--)
//                     free(filenames[count]);
//                 free(filenames);
//                 closedir(dir);
//                 return NULL;
//             }
//             filenames = tmp_file;
//             filenames[count] = strdup(entry->d_name);
//             count++;
//         }
//     }
//     if (filenames)
//         filenames[count] = NULL;
//     closedir(dir);
//     return (filenames);
// }

char **ft_get_filenames_arr(const char *pattern)
{
	DIR *dir;
	struct dirent *entry;
	char **filenames = NULL;
	size_t count = 0;

	if (!pattern || !*pattern)
        return NULL;
    dir = opendir(".");
	if (!dir)
		return NULL;

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.')
			continue;

		if (ft_match_pattern(pattern, entry->d_name)) {
			char **tmp = realloc(filenames, sizeof(char *) * (count + 2)); //check
			if (!tmp) {
				// Cleanup
				for (size_t i = 0; i < count; i++)
					free(filenames[i]);
				free(filenames);
				closedir(dir);
				return NULL;
			}
			filenames = tmp;
			filenames[count] = ft_strdup(entry->d_name);
			if (!filenames[count]) {
				// Cleanup
				for (size_t i = 0; i < count; i++)
					free(filenames[i]);
				free(filenames);
				closedir(dir);
				return NULL;
			}
			count++;
		}
	}
	if (filenames)
		filenames[count] = NULL;
	closedir(dir);
	return filenames;
}
