/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 23:34:04 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/22 23:48:39 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*ft_scan_for_asterisk():
Ignores * inside single or double quotes.
Only allows wildcard expansion if the * is unquoted.
*/

bool ft_scan_for_asterisk(const char *word)
{
    size_t i;
    char quote;

    i = 0;
    quote = 0;
    while (word[i])
    {
        if (!quote && (word[i] == '\'' || word[i] == '"'))
        {
            quote = word[i]; // enter quote mode
            i++;
        }
        else if (quote && word[i] == quote)
        {
            quote = 0; // exit quote mode
            i++;
        }
        else if (word[i] == '*' && quote == 0)
            return (true); // found unquoted *
        else
            i++;
    }
    return (false);
}

static bool ft_match_pattern(const char *pattern, const char *filename)
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

/*
The  opendir()  function  opens  a directory stream 
corresponding to the directory name, 
and returns a pointer to the directory stream.  
The stream is positioned at the first entry in the directory.

The readdir() function returns a pointer to a dirent structure representing 
the next directory entry in the directory stream pointed to by dirp.  
It returns NULL on reaching the end of the directory stream 
or if an error occurred.
*/

int  ft_match_count(const char *pattern)
{
    int match_count;
	DIR *dir;
    struct dirent *entry;

    match_count = 0;
    dir = opendir(".");
    if (!dir)
        return (-1);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue ;
        if (ft_match_pattern(pattern, entry->d_name))
            match_count ++;
    }
    closedir(dir);
    return (match_count);
}

char **ft_get_filenames_arr(const char *pattern, int match_count)
{
	DIR     *dir;
	struct  dirent *entry;
	char    **filenames;
	int     count;
    
    count = 0;
    filenames = malloc(sizeof(char *) * (match_count + 1));
	if (!filenames)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)) != NULL)
    {
		if (entry->d_name[0] != '.' && ft_match_pattern(pattern, entry->d_name))
        {
			filenames[count] = ft_strdup(entry->d_name);
			count ++;
		}
	}
	filenames[count] = NULL;
	closedir(dir);
	return (filenames);
}
