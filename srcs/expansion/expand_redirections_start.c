/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections_start.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:57:02 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/26 02:12:49 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Expand and validate a file name in redirection (like <, >, >>) by:

1 - Performing variable expansion (e.g., $VAR → value)

2 - Handling globbing/asterisk expansion (e.g., * → list of matching files)

3 - Checking for ambiguities in redirection

4 - Performing quote removal on the final string
*/

static int	ft_check_expanded(char *expanded, char *original)
{
	if (!expanded || expanded[0] == '\0' || ft_count_words(expanded) > 1)
	{
		if (expanded)
			free(expanded);
		ft_err_msg(original, "ambiguous redirect", NULL);
		return (ENO_GENERAL);
	}
	return (ENO_SUCCESS);
}

static void	ft_remove_quotes_in_redir(t_in_out *io_n, char *str)
{
	char	*quoted_removed;

	if (io_n->name)
		free(io_n->name);
	quoted_removed = ft_quote_removal(str);
	if (quoted_removed)
		io_n->name = quoted_removed;
	else
		io_n->name = ft_strdup("");
}

static char	*ft_get_first_filename(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*filename = NULL;

	dir = opendir(".");
	if (!dir)
		return (NULL);

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.' && ft_match_pattern(pattern, entry->d_name))
		{
			filename = ft_strdup(entry->d_name);
			break;
		}
	}
	closedir(dir);
	return filename;
}

int	ft_expand_redir_name(t_shell *shell, t_in_out *io_node)
{
	char	*expanded;
	char	*filename;
	// int		status;
	int		match_count;

	expanded = ft_var_expansion(shell, io_node->name);
	// status = ft_check_expanded(expanded, io_node->name);
	if (ft_check_expanded(expanded, io_node->name) != ENO_SUCCESS)
		return (ENO_GENERAL);
	if (expanded && ft_scan_for_asterisk(expanded))
	{
		match_count = ft_match_count(expanded);
		if (match_count == 1)
		{
			filename = ft_get_first_filename(expanded);
			free(expanded);
			expanded = filename; // already strdup'ed inside ft_get_first_filename
		}
		else if (match_count > 1)
		{
			free(expanded);
			ft_err_msg(io_node->name, "ambiguous redirect", NULL);
			return (ENO_GENERAL);
		}
	}
	ft_remove_quotes_in_redir(io_node, expanded);
	if (expanded)
		free(expanded);
	return (ENO_SUCCESS);
}

// static int	ft_check_globbing(t_in_out *io_n, char **exp, char **arr)
// {
// 	int	size;

// 	if (!arr || arr[0] == NULL)
// 	{
// 		if (arr)
// 			ft_free_str_arr(arr, ft_arr_size(arr));
// 		else
// 			ft_free_str_arr(NULL, 0);
// 		free(*exp);
// 		*exp = NULL;
// 		return (ENO_SUCCESS);
// 	}
// 	size = ft_arr_size(arr);
// 	if (size > 1)
// 	{
// 		free(*exp);
// 		ft_free_str_arr(arr, size);
// 		ft_err_msg(io_n->name, "ambiguous redirect", NULL);
// 		return (ENO_GENERAL);
// 	}
// 	free(*exp);
// 	*exp = ft_strdup(arr[0]);
// 	ft_free_str_arr(arr, size);
// 	return (ENO_SUCCESS);
// }
