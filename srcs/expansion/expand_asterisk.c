/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:34:04 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/16 19:09:30 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Assumptions:
old_args is NULL-terminated.

new_items is NULL-terminated.

Frees old_args[index] and inserts all of new_items in its place. */

static int	ft_strs_count(char **arr)
{
	int count = 0;
	while (arr && arr[count])
		count++;
	return count;
}

// char **ft_replace_args(char **old_args, char **new_items, int index)
// {
// 	int old_len;
// 	int new_len;
// 	int new_total;
//     char **new_args;

//     old_len = ft_strs_count(old_args);
// 	new_len = ft_strs_count(new_items);
// 	new_total = old_len - 1 + new_len;

// 	new_args = malloc(sizeof(char *) * (new_total + 1));
// 	if (!new_args)
// 		return NULL;

// 	int i = 0, j = 0;

// 	// Copy up to index
// 	for (; i < index; i++)
// 		new_args[j++] = old_args[i];

// 	// Free the old arg at index
// 	free(old_args[i]);

// 	// Insert new items
// 	for (int k = 0; k < new_len; k++)
// 		new_args[j++] = ft_strdup(new_items[k]);

// 	// Copy remaining args after index
// 	for (i = index + 1; i < old_len; i++)
// 		new_args[j++] = old_args[i];

// 	new_args[j] = NULL;

// 	free(old_args); // Only if all elements are handled appropriately
// 	// new_items not freed here, depends on ownership

// 	return (new_args);
// }

char **ft_replace_args(char **old_args, char **new_items, int index)
{
	int old_len = ft_strs_count(old_args);
	int new_len = ft_strs_count(new_items);
	int new_total = old_len - 1 + new_len;
	char **new_args = malloc(sizeof(char *) * (new_total + 1));
	char **temp_items;
	int i, j = 0;

	if (!new_args)
		return NULL;

	// Step 1: Duplicate all new_items safely
	temp_items = malloc(sizeof(char *) * new_len);
	if (!temp_items)
		return (free(new_args), NULL);

	for (i = 0; i < new_len; i++) {
		temp_items[i] = ft_strdup(new_items[i]);
		if (!temp_items[i]) {
			while (i--)
				free(temp_items[i]);
			free(temp_items);
			free(new_args);
			return NULL;
		}
	}

	// Step 2: Build the new argument list
	for (i = 0; i < index; i++)
		new_args[j++] = old_args[i];

	free(old_args[index]); // Safe to free now

	for (i = 0; i < new_len; i++)
		new_args[j++] = temp_items[i];

	free(temp_items); // temp_items array is not needed anymore

	for (i = index + 1; i < old_len; i++)
		new_args[j++] = old_args[i];

	new_args[j] = NULL;

	free(old_args);
	return new_args;
}

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
