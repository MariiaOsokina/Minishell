/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections_start.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:57:02 by mosokina          #+#    #+#             */
/*   Updated: 2025/04/29 11:41:56 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
//CORRECT
// static char	*ft_get_first_filename(const char *pattern)
// {
// 	DIR				*dir;
// 	struct dirent	*entry;
// 	char			*filename;

// 	dir = opendir(".");
// 	if (!dir)
// 		return (NULL);
// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		if (entry->d_name[0] != '.' && ft_match_pattern(pattern, entry->d_name))
// 		{
// 			filename = ft_strdup(entry->d_name);
// 			break ;
// 		}
// 	}
// 	closedir(dir);
// 	return (filename);
// }
//NEED TO BE TESTED!

static char	*ft_get_first_filename(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*filename;

	filename = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.' && ft_match_pattern(pattern, entry->d_name))
		{
			filename = ft_strdup(entry->d_name);
			break ;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (filename);
}

// int	ft_expand_redir_name(t_shell *shell, t_in_out *io_node)
// {
// 	char	*expanded;
// 	char	*filename;
// 	int		match_count;

// 	expanded = ft_var_expansion(shell, io_node->name);
// 	if (ft_check_expanded(expanded, io_node->name) != ENO_SUCCESS)
// 		return (ENO_GENERAL);
// 	if (expanded && ft_scan_for_asterisk(expanded))
// 	{
// 		match_count = ft_match_count(expanded);
// 		if (match_count == 1)
// 		{
// 			filename = ft_get_first_filename(expanded);
// 			free(expanded);
// 			expanded = filename;
// 		}
// 		else if (match_count > 1)
// 		{
// 			free(expanded);
// 			ft_err_msg(io_node->name, "ambiguous redirect", NULL);
// 			return (ENO_GENERAL);
// 		}
// 	}
// 	ft_remove_quotes_in_redir(io_node, expanded);
// 	if (expanded)
// 		free(expanded);
// 	return (ENO_SUCCESS);
// }

//NEED TO BE TESTED AFTER REARRANGEMENT

static int	ft_handle_asterisk(char **expanded, char *original_name)
{
	int		match_count;
	char	*filename;

	if (!ft_scan_for_asterisk(*expanded))
		return (ENO_SUCCESS);
	match_count = ft_match_count(*expanded);
	if (match_count == 1)
	{
		filename = ft_get_first_filename(*expanded);
		free(*expanded);
		*expanded = filename;
	}
	else if (match_count > 1)
	{
		free(*expanded);
		ft_err_msg(original_name, "ambiguous redirect", NULL);
		return (ENO_GENERAL);
	}
	return (ENO_SUCCESS);
}

int	ft_expand_redir_name(t_shell *shell, t_in_out *io_node)
{
	char	*expanded;

	expanded = ft_var_expansion(shell, io_node->name);
	if (ft_check_expanded(expanded, io_node->name) != ENO_SUCCESS)
		return (ENO_GENERAL);
	if (expanded && ft_handle_asterisk(&expanded, io_node->name) != ENO_SUCCESS)
		return (ENO_GENERAL);
	ft_remove_quotes_in_redir(io_node, expanded);
	if (expanded)
		free(expanded);
	return (ENO_SUCCESS);
}
